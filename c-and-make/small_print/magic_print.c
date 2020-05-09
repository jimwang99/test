#include "magic_print.h"

#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"

void magic_printchar(char **str, int c) { // {{{
    extern int putchar (int c);
    if (str) {
        **str = c;
        ++(*str);
    } else {
        putchar(c);
    }
} // }}}

#define PAD_LEFT_WITH_SPACE     0
#define PAD_LEFT_WITH_ZERO      1
#define PAD_RIGHT_WITH_SPACE    2
int magic_prints(char **out, const char *string, int width, int pad) { // {{{
    register int pc = 0, padchar = ' ';

    if (width > 0) {
        register int len = 0;
        register const char *ptr;
        // calculate the length of string
        for (ptr = string; *ptr; ++ptr) {
            ++len;
        }
        // calculate pad width
        if (len >= width) {
            width = 0;
        } else {
            width -= len;
        }
        if (pad & PAD_LEFT_WITH_ZERO) {
            padchar = '0';
        }
    }
    // pad left with padchar
    if (!(pad & PAD_RIGHT_WITH_SPACE)) {
        for ( ; width > 0; --width) {
            magic_printchar (out, padchar);
            ++pc;
        }
    }
    // print the string itself
    for ( ; *string ; ++string) {
        magic_printchar (out, *string);
        ++pc;
    }
    // pad right with padchar
    if (pad & PAD_RIGHT_WITH_SPACE) {
        for ( ; width > 0; --width) {
            magic_printchar (out, padchar);
            ++pc;
        }
    }

    return pc;
} // }}}

// print number
//      i = number
//      b = base, 10: decimal, 16: hex, 2: bin
//      sg = signed, 1: signed, 0: unsigned, only valid for decimal
//      width = max width (as in magic_prints)
//      pad = padding (as in magic_printi)
//      letbase = base character (for upper case)
#define PRINT_BUF_LEN 12 // it should be enough for 32 bit int
int magic_printi(char **out, int i, int b, int sg, int width, int pad, int letbase) { // {{{
    char print_buf[PRINT_BUF_LEN];
    register char *s;
    register int t, neg = 0, pc = 0;
    register unsigned int u = i;

    if (i == 0) {
        print_buf[0] = '0';
        print_buf[1] = '\0';
        return magic_prints (out, print_buf, width, pad);
    }

    if (sg && b == 10 && i < 0) {
        neg = 1;
        u = -i;
    }

    s = print_buf + PRINT_BUF_LEN-1;
    *s = '\0';

    while (u) {
        t = u % b;
        if( t >= 10 )
            t += letbase - '0' - 10;
        *--s = t + '0';
        u /= b;
    }

    if (neg) {
        if( width && (pad & PAD_LEFT_WITH_ZERO) ) {
            magic_printchar (out, '-');
            ++pc;
            --width;
        }
        else {
            *--s = '-';
        }
    }

    return pc + magic_prints (out, s, width, pad);
} // }}}

// print : common part of printf and sprintf
int _magic_print(char **out, const char *fmt, va_list arg) { // {{{
    register int width, pad;
    register int pc = 0;
    register char *p_fmt = fmt;
    char scr[2];

    for (; *p_fmt != 0; ++p_fmt) {
        if (*p_fmt == '%') {
            ++p_fmt; // move to next char
            width = 0;
            pad = 0;
            if (*p_fmt == '\0') break;
            if (*p_fmt == '%') goto out; // escape %
            if (*p_fmt == '-') {
                ++p_fmt;
                pad = PAD_RIGHT_WITH_SPACE;
            }
            while (*p_fmt == '0') {
                ++p_fmt;
                pad |= PAD_LEFT_WITH_ZERO;
            }
            for ( ; *p_fmt >= '0' && *p_fmt <= '9'; ++p_fmt) {
                width *= 10;
                width += *p_fmt - '0';
            }
            if( *p_fmt == 'd' ) {
                register int d = va_arg(arg, int);
                pc += magic_printi (out, d, 10, 1, width, pad, 'a');
                continue;
            }
            if( *p_fmt == 'u' ) {
                register int d = va_arg(arg, int);
                pc += magic_printi (out, d, 10, 0, width, pad, 'a');
                continue;
            }
            if( *p_fmt == 's' ) {
                register char *s = va_arg(arg, char *);
                pc += magic_prints (out, s?s:"(null)", width, pad);
                continue;
            }
            if( *p_fmt == 'x' ) {
                register int d = va_arg(arg, int);
                pc += magic_printi (out, d, 16, 0, width, pad, 'a');
                continue;
            }
            if( *p_fmt == 'X' ) {
                register int d = va_arg(arg, int);
                pc += magic_printi (out, d, 16, 0, width, pad, 'A');
                continue;
            }
            if( *p_fmt == 'c' ) {
                // char are converted to int then pushed on the stack
                scr[0] = va_arg(arg, int);
                scr[1] = '\0';
                pc += magic_prints (out, scr, width, pad);
                continue;
            }
        } else {
        out:
            magic_printchar (out, *p_fmt);
            ++pc;
        }
    }
    if (out) { // add end char to string target
        **out = '\0';
    }
    return pc;
} // }}}

int magic_printf(const char *fmt, ...) {
    va_list arg;
    int pc;

    va_start(arg, fmt);
    pc = _magic_print(0, fmt, arg);
    va_end(arg);

    return pc;
}

int magic_sprintf(char *out, const char *fmt, ...) {
    va_list arg;
    int pc;

    va_start(arg, fmt);
    pc = _magic_print(&out, fmt, arg);
    va_end(arg);

    return pc;
}
#undef PAD_LEFT_WITH_SPACE
#undef PAD_LEFT_WITH_ZERO
#undef PAD_RIGHT_WITH_SPACE
#undef PRINT_BUF_LEN
