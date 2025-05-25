// test.c

#include <stdio.h>
#include "custom_printf.h"

int main() {
    int my_len, std_len;
 
    // Test 1: Literal percent %%
    printf("\n--- Test 1: Literal %% ---\n");
    std_len = printf("Standard printf: Hello %% World!\n");
    my_len = my_printf("Custom  my_printf: Hello %% World!\n");
    printf("Lengths - printf: %d, my_printf: %d\n", std_len, my_len);

    // Test 2: Single char
    printf("\n--- Test 2: Character %c ---\n", 'A');
    std_len = printf("Standard printf: Char is: %c\n", 'A');
    my_len = my_printf("Custom  my_printf: Char is: %c\n", 'A');
    printf("Lengths - printf: %d, my_printf: %d\n", std_len, my_len);

    /*Test 3: Unknown specifier
    printf("\n--- Test 3: Unknown q ---\n");
    std_len = printf("Standard printf: Unknown: %q\n", 'X'); // May warn
    my_len = my_printf("Custom  my_printf: Unknown: %q\n", 'X');
    printf("Lengths - printf: %d, my_printf: %d\n", std_len, my_len);*/

    // Test 4: No formatting
    printf("\n--- Test 4: Plain text ---\n");
    std_len = printf("Standard printf: Just a string.\n");
    my_len = my_printf("Custom  my_printf: Just a string.\n");
    printf("Lengths - printf: %d, my_printf: %d\n", std_len, my_len);

    // Test 5: Multiple mixed
    printf("\n--- Test 5: Mixed %% and %%c ---\n");
    std_len = printf("Standard printf: %% %c %% %c\n", 'X', 'Y');
    my_len = my_printf("Custom  my_printf: %% %c %% %c\n", 'X', 'Y');
    printf("Lengths - printf: %d, my_printf: %d\n", std_len, my_len);

    return 0;
}

