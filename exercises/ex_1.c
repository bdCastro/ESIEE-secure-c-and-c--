#include <stdio.h>
#include <stdlib.h>

int gets_s_s(char *s, int size) {
    int r = 0;
    char c = getchar();

    while(c != '\0' && c != EOF && r < size) {
        s[r++] = c;
        c = getchar();
    }

    s[r] = '\0';

    return 0;
}

int main() {
    char *s = malloc(25 * sizeof(char));

    gets_s_s(s, 5);
    puts(s);
}

