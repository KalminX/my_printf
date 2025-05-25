// custom_printf.h

#ifndef CUSTOM_PRINTF_H
#define CUSTOM_PRINTF_H

#include <stdarg.h>

typedef struct {
    int width;
    int precision;
    int precision_specified;
} format_spec;

typedef int (*specifier_func)(va_list *, format_spec *);

int my_printf(const char *format, ...);

#endif

