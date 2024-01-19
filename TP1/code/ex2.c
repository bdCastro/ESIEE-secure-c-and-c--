#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define MAXARGS 10
#define MAXALLOC 128
#define MAXARGLEN 256

typedef struct arglist {
    char *arg[MAXARGS];
} arglist;


int fillbuf(char *target) {
    short i = 0;
    arglist *aList = NULL;
    if (target) *target = '\0';
    while (getarg(&aList, i) && (i < MAXARGS)) {
        if (target != NULL) {
            strcpy(target, aList->arg[i++]);
            printf("%s\n", target);
        }
    }

    return 0;
}

int getarg(arglist **al, short index) {
    char *inputbuf;
    inputbuf = (char *)malloc(MAXARGLEN);
    fgets(inputbuf, MAXARGLEN, stdin);
    (*al)->arg[index] = inputbuf;
    return strcasecmp("END", inputbuf) ? 0 : 1;
}

int main() {
    char *buf;
    buf = (char *)malloc(MAXALLOC);
    return fillbuf(buf);
}
