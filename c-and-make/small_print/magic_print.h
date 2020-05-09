#ifndef __MAGIC_PRINT_H__
#define __MAGIC_PRINT_H__

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define MEM32(addr) (*((volatile uint32_t *) addr))
#define MEM16(addr) (*((volatile uint16_t *) addr))
#define MEM8(addr)  (*((volatile uint8_t  *) addr))

#define str_cpy(s,v) {strncpy(s,v,sizeof(s));}

void magic_printchar(char **str, int c);

// print string
//      width = max width (if width < len(string), then no padding)
//      pad = 0: padding left with space, 1: padding left with zero, 2: padding right with space
//  return:
//      pc = total length of
int magic_prints(char **out, const char *string, int width, int pad);

// print number
//      i = number
//      b = base, 10: decimal, 16: hex, 2: bin
//      sg = signed, 1: signed, 0: unsigned, only valid for decimal
//      width = max width (as in magic_prints)
//      pad = padding (as in magic_printi)
//      letbase = base character (for upper case)
int magic_printi(char **out, int i, int b, int sg, int width, int pad, int letbase);

// print : common part of printf and sprintf
//      NOT for external usage
int _magic_print(char **out, const char *fmt, va_list arg);

// top-level printf
int magic_printf(const char *fmt, ...);

// top-level sprintf
int magic_sprintf(char *out, const char *fmt, ...);

#endif // __MAGIC_PRINT_H__
