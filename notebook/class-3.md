## Class 3

### Copying strings in C/C++

In C/C++, strings are just arrays of characters.  So, to copy a string, you can just copy the array.  For example:

#### strcpy()

This is the most common way to copy a string in C/C++. But its not the safest. If the destination array is not large enough to hold the source string, then you will have a buffer overflow.  This is a security risk.  So, you should use strncpy() instead.

##### Signature

```c
char *strcpy(char *dest, const char *src);
```

#### strlcpy()

This is a safer way to copy a string in C/C++. It will only copy the number of characters that will fit in the destination array. It will also always null terminate the destination array.  This is a good way to copy a string in C/C++.

##### Signature

```c
size_t strlcpy(char *dest, const char *src, size_t size);
```

#### strdup()

This is also another safe way to copy a string in C/C++. It will allocate a new array to hold the string. As we are allocating memory, we don't need to worry about buffer overflows.  However, we do need to remember to free the memory when we are done with it.

##### Signature

```c
char *strdup(const char *s);
```

#### memcpy() / memmove()

These are the most common ways to copy a string in C/C++. They are also the most dangerous. If you are copying a string, you should use one of the above functions instead. These functions are used to copy arrays of bytes. They do not null terminate the destination array, that is, they do not make it a string.  So, if you are copying a string, you should use one of the above functions instead.

##### Signature

```c
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
```

The difference between memcpy() and memmove() is that memcpy() will not work if the source and destination arrays overlap.  memmove() will work if the source and destination arrays overlap.

### Strings in C++

In C++, strings are objects. So, to copy a string, you can just copy the object. For example:

#### str[pos] vs str.at(pos)

The [] operator is faster, but it does not do bounds checking. The .at() method is slower, but it does do bounds checking. So, if you are sure that you are not going to go out of bounds, then you should use the [] operator. If you are not sure, then you should use the .at() method.

### Buffer overflows and stack

A buffer overflow is when you write past the end of an array. This can cause a segmentation fault. It can also cause a security vulnerability, for example, if you overflow a buffer on the stack, you can overwrite the return address of a function. This can cause the program to jump to a different function. This can be used to exploit a program.

#### Security protections

##### ASLR

Address Space Layout Randomization (ASLR) is a security technique that randomizes the location of the stack and heap in memory. This makes it harder to exploit a program.

##### NX

No eXecute (NX) is a security technique that marks the stack as non-executable. This makes it harder to exploit a program.

##### Stack canaries

A stack canary is a security technique that puts a random value on the stack before the return address. When the function returns, it checks to make sure that the value is still there. If it is not, then it knows that the stack has been corrupted. This makes it harder to exploit a program.

### The problem with printf()

The printf() function is a very powerful function. It can be used to print many different types of data. However, it is also very dangerous. If you use it incorrectly, you can cause a buffer overflow. This can be used to exploit a program.

