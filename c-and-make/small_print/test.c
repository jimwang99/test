#include "magic_print.h"

#define PAD_LEFT_WITH_SPACE     0
#define PAD_LEFT_WITH_ZERO      1
#define PAD_RIGHT_WITH_SPACE    2

#include <stdio.h>


int main(void) {
    //==========================================================
    printf("== printchar\n");
    char buf[100] = "        ";
    char *ptr_buf = buf;

    magic_printchar(0, 'a');
    magic_printchar(0, '\n');

    magic_printchar(&ptr_buf, 'b');
    printf("%s\n", buf);

    //==========================================================
    printf("== prints\n");
    magic_prints(0, "default: no padding\n", 0, 0);
    magic_prints(0, "pad-left-with-space-to-total-width-100\n", 100, PAD_LEFT_WITH_SPACE);
    magic_prints(0, "pad-left-with-zero-to-total-width-100\n", 100, PAD_LEFT_WITH_ZERO);
    magic_prints(0, "pad-right-with-space-to-total-width-100", 100, PAD_RIGHT_WITH_SPACE);
    magic_prints(0, "default: no padding\n", 0, 0);

    magic_prints(&ptr_buf, "prints-to-buffer\n", 0, 0);
    printf("%s", buf);

    //==========================================================
    printf("== printi\n");
    int ii;
    ii = 12;
    magic_printi(0, ii, 10, 1, 0, PAD_LEFT_WITH_SPACE, 'a');
    printf(" == %d (ref)\n", ii);
    magic_printi(0, ii, 16, 0, 0, PAD_LEFT_WITH_SPACE, 'a');
    printf(" == %x (ref)\n", ii);

    //==========================================================
    printf("== printf\n");

    magic_printf("pure-string\n");
    magic_printf("integer: %d.\n", 12);
    magic_printf("integer: %d.\n", -12);
    magic_printf("integer-unsigned: %u.\n", -12);
    magic_printf("string: %s.\n", "static-string");
    str_cpy(buf, "dynamic-string");
    magic_printf("string: %s.\n", buf);
    magic_printf("hex-lower: 0x%x.\n", 12);
    magic_printf("hex-upper: 0x%X.\n", 12);
    magic_printf("char: %c.\n", 'a');

    //==========================================================
    printf("== sprintf\n");

    magic_sprintf(buf, "hello world!\n");
    printf("%s", buf);
    magic_sprintf(buf, "integer: %d\n", 1);
    printf("%s", buf);
    magic_sprintf(buf, "integer: %d\n", 12);
    printf("%s", buf);
    magic_sprintf(buf, "integer: %d\n", -12);
    printf("%s", buf);
    magic_sprintf(buf, "integer: %d\n", 32);
    printf("%s", buf);

    /* magic_printf("hello world!\n"); */
    return 0;
}
