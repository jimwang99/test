#include <stdio.h>
#include <stdlib.h>

struct node {
    char c;
    struct node * pNext;
};

typedef struct node node_t;

struct ll {
    node_t * pFirst;
    node_t * pLast;
    size_t sz;
};

typedef struct ll ll_t;

void add_history(ll_t * pll, char c) {
    node_t * p = malloc(sizeof(node_t));
    p->c = c;
    p->pNext = NULL;

    if (pll->sz == 0) {
        pll->pFirst = p;
    } else {
        pll->pLast->pNext = p;
    }
    pll->pLast = p;
    pll->sz += 1;
    // printf("DBG: add_history %c\n", c);
}

void print_history(ll_t * pll) {
    printf("history: ");

    node_t * pCurr = pll->pFirst;
    while (pCurr != NULL) {
        printf("%c ", pCurr->c);
        pCurr = pCurr->pNext;
    }
    printf("\n");
}

int main(void) {
    char c;
    int ii;
    int next;

    ll_t ll;
    ll.pFirst = NULL;
    ll.pLast = NULL;
    ll.sz = 0;

    for (;;) {
        printf("Waiting for input (available choices: h/g/x/e):");

        next = 0;
        while ((c = getchar()) != '\n') {
            switch(c) {
                case 'e':
                    print_history(&ll);
                    return 0;
                case 'h':
                    printf("Hello World!\n");
                    break;
                case 'g':
                    printf("Goodbye!\n");
                    break;
                case 'x':
                    for (ii=0; ii<10; ++ii) {
                        printf("%d Hello World!\n", ii+1);
                    }
                    break;
                case 13:
                    next = 1;
                    break;
                default:
                    continue;
            }
            add_history(&ll, c);
            if (next) {
                break;
            }
        }
    }
    return 0;
}