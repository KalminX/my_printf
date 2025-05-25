// tests.c

#include <stdio.h>
#include "custom_printf.h"

int main() {
    int ret_std, ret_custom;

    printf("\n=== Testing %%u, %%x, %%o with precision/width ===\n");

    printf("printf   : [%8.4u]\n", 123);
    my_printf("my_printf: [%8.4u]\n", 123);

    printf("printf   : [%10.6x]\n", 3735928559u);
    my_printf("my_printf: [%10.6x]\n", 3735928559u);

    printf("printf   : [%6.4o]\n", 77);
    my_printf("my_printf: [%6.4o]\n", 77);


    my_printf("int: [%8.4d]\n", 42);
    my_printf("str: [%10.3s]\n", "KalminX");
    my_printf("octal: [%6.4o]\n", 25);
    my_printf("percent: [%%]\n");


    printf("\n===== Testing %%c (character) =====\n");
    ret_std = printf("printf: [%c]\n", 'A');
    ret_custom = my_printf("my_printf: [%c]\n", 'A');
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing %%s (string) =====\n");
    ret_std = printf("printf: [%s]\n", "Hello, World!");
    ret_custom = my_printf("my_printf: [%s]\n", "Hello, World!");
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing %%d and %%i (integers) =====\n");
    ret_std = printf("printf: [%d] [%i]\n", -123, 456);
    ret_custom = my_printf("my_printf: [%d] [%i]\n", -123, 456);
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing %%u (unsigned int) =====\n");
    ret_std = printf("printf: [%u]\n", 3000000000U);
    ret_custom = my_printf("my_printf: [%u]\n", 3000000000U);
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing %%x and %%X (hexadecimal) =====\n");
    ret_std = printf("printf: [%x] [%X]\n", 3735928559U, 3735928559U);
    ret_custom = my_printf("my_printf: [%x] [%X]\n", 3735928559U, 3735928559U);
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing %%p (pointer) =====\n");
    ret_std = printf("printf: [%p]\n", main);
    ret_custom = my_printf("my_printf: [%p]\n", main);
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing %%%% (literal percent) =====\n");
    ret_std = printf("printf: [%%]\n");
    ret_custom = my_printf("my_printf: [%%]\n");
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing NULL string (%%s) =====\n");
    ret_std = printf("printf: [%s]\n", (char *)NULL);
    ret_custom = my_printf("my_printf: [%s]\n", (char *)NULL);
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing unknown format %%q =====\n");
    ret_std = printf("printf: [%q]\n", 'X'); // May warn
    ret_custom = my_printf("my_printf: [%q]\n", 'X');
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    printf("\n===== Testing %%o (octal) =====\n");
    ret_std = printf("printf: [%o]\n", 255);
    ret_custom = my_printf("my_printf: [%o]\n", 255);
    printf("Lengths: printf = %d, my_printf = %d\n", ret_std, ret_custom);

    return 0;
}

