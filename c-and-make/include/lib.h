#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>

__attribute__((weak)) void weak_func(void);
void test_lib(void);

#ifndef LIB_DEFINE
#define LIB_DEFINE "use LIB_DEFINE in lib.h\n"
#endif

#endif
