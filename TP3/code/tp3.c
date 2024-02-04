#include <stdio.h>
#include <stdlib.h>

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

__attribute__((noinline))
void secret_function(void)
{
    printf("You are now in the secret function.\n");
    printf("Congratulations, you have solved this question!\n");
    exit(0);
}

__attribute__((noinline))
int horribly_vulnerable(void) {
    char array[400];
    printf("Enter some wonderful text:\n");
    gets(array);
    printf("FYI, your input was: '%s'\n", array);
    return 0;
}

int main(void) {
    horribly_vulnerable();
    return 0;
}