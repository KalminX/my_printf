#include "custom_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>


int write_str(const char *s) {
    int len = 0;
    while (s[len]) len++;
    return write(1, s, len);
}

int print_percent(va_list *args) {
    (void)args;
    return write(1, "%", 1);
}

int print_char(va_list *args) {
    char c = (char)va_arg(*args, int);
    return write(1, &c, 1);
}

int print_string(va_list *args, format_spec *spec) {
    char *str = va_arg(*args, char *);
    if (!str) str = "(null)";
    int len = strlen(str);

    // Truncate if precision is specified and shorter
    if (spec->precision_specified && spec->precision < len) {
        len = spec->precision;
    }

    // Apply width: pad with spaces to the left
    int padding = (spec->width > len) ? spec->width - len : 0;
    for (int i = 0; i < padding; i++) write(1, " ", 1);

    write(1, str, len);
    return len + padding;
}

int print_int(va_list *args, format_spec *spec) {
    int num = va_arg(*args, int);
    char buf[20]; // enough for int + sign + null
    int i = 19;
    buf[i--] = '\0';

    int is_negative = 0;
    if (num == 0) {
        buf[i--] = '0';
    } else {
        if (num < 0) {
            is_negative = 1;
            num = -num;
        }

        while (num > 0) {
            buf[i--] = '0' + (num % 10);
            num /= 10;
        }
    }

    int num_digits = 19 - i - 1;

    // Apply precision: add leading zeros
    while (spec->precision_specified && num_digits < spec->precision) {
        buf[i--] = '0';
        num_digits++;
    }

    if (is_negative) {
        buf[i--] = '-';
    }

    char *final_str = &buf[i + 1];
    int final_len = strlen(final_str);

    // Apply width: pad with spaces to the left
    int padding = (spec->width > final_len) ? spec->width - final_len : 0;
    for (int j = 0; j < padding; j++) write(1, " ", 1);

    write(1, final_str, final_len);
    return final_len + padding;
}

int print_unsigned(va_list *args, format_spec *spec) {
    unsigned int num = va_arg(*args, unsigned int);
    char buf[20];
    int i = 19;
    buf[i--] = '\0';

    if (num == 0) {
        buf[i--] = '0';
    } else {
        while (num > 0) {
            buf[i--] = '0' + (num % 10);
            num /= 10;
        }
    }

    int digits = 19 - i - 1;

    while (spec->precision_specified && digits < spec->precision) {
        buf[i--] = '0';
        digits++;
    }

    char *final_str = &buf[i + 1];
    int len = strlen(final_str);

    int padding = (spec->width > len) ? spec->width - len : 0;
    for (int j = 0; j < padding; j++) write(1, " ", 1);

    write(1, final_str, len);
    return len + padding;
}

int print_octal(va_list *args, format_spec *spec) {
    unsigned int num = va_arg(*args, unsigned int);
    char buf[22];
    int i = 21;
    buf[i--] = '\0';

    if (num == 0) {
        buf[i--] = '0';
    } else {
        while (num > 0) {
            buf[i--] = '0' + (num % 8);
            num /= 8;
        }
    }

    int digits = 21 - i - 1;
    while (spec->precision_specified && digits < spec->precision) {
        buf[i--] = '0';
        digits++;
    }

    char *final_str = &buf[i + 1];
    int len = strlen(final_str);

    int padding = (spec->width > len) ? spec->width - len : 0;
    for (int j = 0; j < padding; j++) write(1, " ", 1);

    write(1, final_str, len);
    return len + padding;
}

int print_hex(va_list *args, format_spec *spec) {
    unsigned int num = va_arg(*args, unsigned int);
    char buf[20];
    int i = 19;
    buf[i--] = '\0';

    if (num == 0) {
        buf[i--] = '0';
    } else {
        while (num > 0) {
            int digit = num % 16;
            buf[i--] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
            num /= 16;
        }
    }

    int digits = 19 - i - 1;
    while (spec->precision_specified && digits < spec->precision) {
        buf[i--] = '0';
        digits++;
    }

    char *final_str = &buf[i + 1];
    int len = strlen(final_str);

    int padding = (spec->width > len) ? spec->width - len : 0;
    for (int j = 0; j < padding; j++) write(1, " ", 1);

    write(1, final_str, len);
    return len + padding;
}

int print_hex_lower(va_list *args) {
    return print_hex(args, 0);
}

int print_hex_upper(va_list *args) {
    return print_hex(args, 1);
}

int print_pointer(va_list *args, format_spec *spec) {
    void *ptr = va_arg(*args, void *);
    unsigned long addr = (unsigned long)ptr;

    char buf[20];
    int i = 19;
    buf[i--] = '\0';

    if (addr == 0) {
        buf[i--] = '0';
    } else {
        while (addr > 0) {
            int digit = addr % 16;
            buf[i--] = (digit < 10) ? '0' + digit : 'a' + (digit - 10);
            addr /= 16;
        }
    }

    // Add "0x" prefix
    buf[i--] = 'x';
    buf[i--] = '0';

    char *final_str = &buf[i + 1];
    int len = strlen(final_str);

    // Width padding (right-align default)
    int padding = (spec->width > len) ? spec->width - len : 0;
    for (int j = 0; j < padding; j++) write(1, " ", 1);

    write(1, final_str, len);
    return len + padding;
}

int my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;

    while (*format) {
        if (*format == '%') {
            format++;

            // Initialize format specification
            format_spec spec = {0, 0, 0};

            // Step 1: Parse width (numbers before dot)
            while (*format >= '0' && *format <= '9') {
                spec.width = spec.width * 10 + (*format - '0');
                format++;
            }

            // Step 2: Parse precision if present
            if (*format == '.') {
                format++;
                spec.precision_specified = 1;
                spec.precision = 0;
                while (*format >= '0' && *format <= '9') {
                    spec.precision = spec.precision * 10 + (*format - '0');
                    format++;
                }
            }

            // Step 3: Determine format specifier
            specifier_func handler = NULL;

            switch (*format) {
                case 'd':
                case 'i':
                    handler = print_int;
                    break;
                case 'u':
                    handler = print_unsigned;
                    break;
                case 'x':
                    handler = print_hex;
                    break;
                case 'o':
                    handler = print_octal;
                    break;
                case 's':
                    handler = print_string;
                    break;
                case 'c':
                    handler = print_char;
                    break;
                case 'p':
                    handler = print_pointer;
                    break;
                case '%':
                    handler = print_percent;
                    break;
                default:
                    // Unknown specifier, print as-is
                    write(1, "%", 1);
                    write(1, format, 1);
                    count += 2;
                    format++;
                    continue;
            }

            // Call the handler if found
            if (handler) {
                count += handler(&args, &spec);
            }

            format++; // Move past the format specifier
        } else {
            // Print regular character
            write(1, format, 1);
            count++;
            format++;
        }
    }

    va_end(args);
    return count;
}