#include <stdio.h>
#include <string.h>
#include <iostream>

// to exploit this, use "%#x" to dump the stack
// the variables x and y are in the stack

int main(int argc, char * argv[]) {
    long int x = 0xAABBCCDD;
    volatile long int y = 0x12345678;
    std::string input;
    while(1) {
        printf("IN STR: ");
        std::cin >> input;
        printf(input.c_str());
        printf("\n");
    }
}
