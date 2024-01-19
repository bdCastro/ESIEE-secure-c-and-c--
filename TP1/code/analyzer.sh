#!/bin/bash
# Author: bdCastro

NAME=$1
TAG="${NAME%.*}"
EXTENSION="${NAME#*.}"
ITS_C=true

if [ "$EXTENSION" = "c" ]; then
    ITS_C=true
elif [ "$EXTENSION" = "cpp" ]; then
    ITS_C=false
else
    printf "file extension must be c or cpp"
    exit 1
fi

# gcc Warnings

printf "\n================ gcc Warnings ================\n\n"

if $ITS_C; then
    gcc -std=gnu2x -O2 -Wall -Wextra "$NAME" -o "/tmp/$TAG" -g
else
    g++ -std=gnu++20 -O2 -Wall -Wextra "$NAME" -o "/tmp/$TAG" -g
fi

# clang warnings

printf "\n================ clang Warnings ================\n\n"

if $ITS_C; then
    clang -std=gnu2x -O2 -Wall -Wextra "$NAME"
else
    clang++ -std=gnu++20 -O2 -Wall -Wextra "$NAME"
fi

# cppcheck

printf "\n================ cppcheck ================\n\n"

cppcheck --enable=all --inconclusive "$NAME"

# gcc analyser

printf "\n================ gcc analyzer ================\n\n"

if $ITS_C; then
    gcc -std=gnu2x -O2 -fanalyzer "$NAME"
else
    g++ -std=gnu++20 -O2 -fanalyzer "$NAME"
fi

# clang analyzer

printf "\n================ clang analyzer ================\n\n"

if $ITS_C; then
    scan-build clang -std=c2x -O2 -c -w "$NAME"
else
    scan-build clang++ -std=gnu++20 -O2 -c -w "$NAME"
fi

printf "\n================ gcc Sanitizers ================\n\n"

if $ITS_C; then
    gcc -std=gnu2x -O2 -w -fsanitize=leak,address,undefined "$NAME" -g -o "/tmp/$TAG-gcc-sanitizer"
else
    g++ -std=gnu++20 -O2 -w -fsanitize=leak,address,undefined "$NAME" -g -o "/tmp/$TAG-gcc-sanitizer"
fi

"/tmp/$TAG-gcc-sanitizer"

printf "\n================ clang Sanitizers ================\n\n"

if $ITS_C; then
    clang -std=gnu2x -O2 -w -fsanitize=leak,address,undefined "$NAME" -g -o "/tmp/$TAG-clang-sanitizer"
else
    clang++ -std=gnu++20 -O2 -w -fsanitize=leak,address,undefined "$NAME" -g -o "/tmp/$TAG-clang-sanitizer"
fi

"/tmp/$TAG-clang-sanitizer"

printf "\n================ valgrind ================\n\n"

valgrind "/tmp/$TAG"