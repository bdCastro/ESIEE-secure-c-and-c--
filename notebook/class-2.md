### strings

- strings are a sequence of characters (char)
- in C/C++, a string is a pointer to the first character of the string
- the program knows the end of the string when it finds a null character '\0'

### vunerabilities

#### gets()

- gets() reads a line from stdin and stores it in a buffer
- gets() does not check the length of the input
- this may cause an overflow of the buffer

```c
#include <stdio.h>
#include <string.h>

void continue_or_not(void) {
    char buffer[8];
    puts("Continue? (y/n)");
    gets(buffer);
    bool stop = buffer[0] == 'n';

    if (stop)
        exit(0);

int main() {
    int hello = 0;
    continue_or_not();
    return 0;
}
```

##### stack


| continue_or_not() | main() |
|-------------------|--------|
| buffer[8],stop(1) | hello  |

