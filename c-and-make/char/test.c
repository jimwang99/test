
#include <stdio.h>

void print_to_buf (char **p_buf, char c) {
    *p_buf[0] = c;
    ++(*p_buf);
}


int main(void) {
    printf("===========\n");
    printf("Hello world\n");

    char buf [100] = "01234567";

    char *p_buf = buf;

    print_to_buf(&p_buf, 'a');
    print_to_buf(&p_buf, 'b');

    printf("%s\n", buf);

    printf("===========\n");
    return 0;
}
