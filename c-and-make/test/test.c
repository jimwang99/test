
#define LIB_DEFINE "use LIB_DEFINE in test.c\n"

#ifdef TEST_DEF
    #define TMP_STRING "TEST_DEF is defined\n"
#else
    #define TMP_STRING "TEST_DEF is NOT defined\n"
#endif


#include "lib.h"
#include <stdio.h>


void retarget_init() {
}

void SystemInit() {
    retarget_init();
}

int _write (int fd, char * ptr, int len) {
    int ii;
    for (ii=0; ii<len; ii++) {
        // putc(*ptr);
        ptr++;
    }
    return ii;
}

void weak_func(void) {
    printf("override weak_func\n");
}

int main(void) {
    printf("Hello world\n");
    printf(LIB_DEFINE);
    printf(TMP_STRING);

    weak_func();

    test_lib();

    return 0;
}
