#include <stdio.h>
#include <stddef.h>

constexpr size_t MAXARGS = 10;
constexpr size_t MAXALLOC = 128;
constexpr size_t MAXARGLEN = 256;

typedef struct arglist {
    char *arg[MAXARGS];
} arglist;

void main() {
    char *buf;
    buf = (char *)malloc(MAXALLOC);
    return fillbuf(buf);
}

int getarg(arglist **al, short index) {
    char *inputbuf;
    inputbuf = (char *)malloc(MAXARGLEN);
    fgets(inputbuf, MAXARGLEN, stdin);
    (*al)->arg[index] = inputbuf;
    return strcasecmp("END", inputbuf) ? 0 : 1;
}

int fillbuf(char *target) {
    short i = 0;
    arglist *aList = NULL;
    if (target) *target = '\0';
    while (getarg(&aList, i) && (i < MAXARGS)) {
        if (target != NULL)
            strcpy(target, aList->arg[i++]);
        /* ... */
        printf("%s\n", target);
        /* ... */
    }
}
