#include "s21_string.h"

void specifier_c(char *buffer, int *index, const int flags[], va_list va) {
    if (flags[0] || flags[1] > 1 || flags[2] || flags[4] != -1) {
        *index = -1;
    } else if ((flags[5] > 0 && flags[5] < 3) || flags[5] == 4) {
        *index = -1;
    } else if (*index != -1) {
        buffer[*index] = (char) va_arg(va, long int);
        *index += 1;
    }
}
// i = 0 ' ' = 32 и '+' = 43
// i = 1 '-' = 1 и '0' = 2
// i = 2 '#'
// i = 3 'число and *'
// i = 4 '.число and .*'
// i = 5 'h = 1 AND L = 2 and l = 3 and ll = 4'
// i = 6 'Спецификатор'
void specifier_s(char *buffer, int *index, int flags[], va_list va) {
    if (flags[0] || flags[1] > 1 || flags[2]) {
        *index = -1;
    } else if ((flags[5] > 0 && flags[5] < 3) || flags[5] == 4) {
        *index = -1;
    } else if (*index != -1) {
        if (flags[5] == 3) {
            wchar_t *value = 0;
            value = va_arg(va, wchar_t*);
            int len = 0;
            for (; value[len] != '\0'; len++) { ; }
            flags[4] = (flags[4] == -1) ? len : flags[4];
            for (int i = 0; i < flags[4] && value[i] != '\0'; i++, *index += 1) {
                buffer[*index] = value[i];
            }
        } else {
            char *value = 0;
            value = va_arg(va, char*);
            flags[4] = (flags[4] == -1) ? (int) s21_strlen(value) : flags[4];
            for (int i = 0; i < flags[4] && value[i] != '\0'; i++, *index += 1) {
                buffer[*index] = value[i];
            }
        }
    }
}

void zapolnenie(char *buffer, int *index, int flags[], const char *tempBuff, const int *tempIndex) {
    if (flags[1] == 2 && flags[3] > *tempIndex) {
        put_space(buffer, index, flags[3] - *index, '0');
    } else if (flags[4] > *tempIndex) {
        put_space(buffer, index, flags[4], '0');
    }
    if (*tempIndex < *index) {
        *index -= *tempIndex;
    }
    for (int i = 0; i < *tempIndex; i++) {
        buffer[*index] = tempBuff[i];
        *index += 1;
    }
    buffer[*index] = '\0';
}

void zapolneniTempBufferaInt(char *buffer, int *index, int flags[], long long int value) {
    if (value == LLONG_MIN) {
        const char min[] = "-9223372036854775808";
        for (int i = 0; min[i] != '\0'; i++) {
            buffer[i] = min[i];
            *index += 1;
        }
    } else {
        if (value < 0) {
            buffer[*index] = '-';
            *index += 1;
            value *= -1;
        } else if (flags[0]) {
            buffer[*index] = flags[0];
            *index += 1;
        }
        char tempBuff[42] = "";
        int tempIndex = 0;
        for (long long int i = s21_powl(10, amount_number(value) - 1); i > 0; i /= 10) {
            tempBuff[tempIndex] = '0' + (value / i % 10);
            tempIndex++;
        }
        zapolnenie(buffer, index, flags, tempBuff, &tempIndex);
    }
}

void put_u(char *buffer, int *index, int flags[], long long unsigned int value) {
    char tempBuff[42] = "";
    int tempIndex = 0;
    if (flags[0]) {
        buffer[*index] = flags[0];
        *index += 1;
    }
    for (long long unsigned int i = s21_powl(10, amount_number(value) - 1); i > 0; i /= 10) {
        tempBuff[tempIndex] = '0' + (value / i % 10);
        tempIndex++;
    }
    zapolnenie(buffer, index, flags, tempBuff, &tempIndex);
}

void specifier_d_i(char *buffer, int *index, int flags[], va_list va) {
    flags[2] ? *index = -1 : 0;
    if ((flags[6] == 'd' || flags[6] == 'i') && *index != -1) {
        long long int value = 0;
        if (flags[5] == 3) {
            value = va_arg(va, long int);
        } else if (flags[5] == 4 || (flags[5] == 2 && flags[6] != 'i')) {
            value = va_arg(va, long long int);
        } else if (flags[5] == 1) {
            value = (short) va_arg(va, int);
        } else {
            value = va_arg(va, int);
        }
        zapolneniTempBufferaInt(buffer, index, flags, value);
    }
}

void specifier_u(char *buffer, int *index, int flags[], va_list va) {
    flags[2] ? *index = -1 : 0;
    if (flags[6] == 'u' && *index != -1) {
        long long unsigned int value1 = 0;
        if (flags[5] == 1) {
            value1 = (unsigned short) va_arg(va, unsigned int);
        } else if (flags[5] == 2 || flags[5] == 4) {
            value1 = va_arg(va, long long unsigned int);
        } else if (flags[5] == 3) {
            value1 = va_arg(va, long unsigned int);
        } else {
            value1 = va_arg(va, unsigned int);
        }
        put_u(buffer, index, flags, value1);
    }
}

char output_sign(long double *value, int *count) {
    char sign;
    if (*value == 0) {
        *value = 0;
        sign = '+';
    } else if (*value < 1.0) {
        do {
            *value *= 10;
            *count += 1;
        } while (*value < 0.9);
        sign = '-';
    } else {
        while (*value >= 10.0) {
            *value /= (double) 10;
            *count += 1;
        }
        sign = '+';
    }
    return sign;
}

long double specifier_G(long double value, int flags[], int *count, char *plusOrMinus) {
    long double start_value = value;
    *plusOrMinus = output_sign(&value, count);
    if (flags[4] == 0)
        flags[4] = 1;
    if ((*count > 4 && *plusOrMinus == '-') ||
        (*count > 5 && *plusOrMinus == '+' && *count >= flags[4]) ||
        (amount_number((int) start_value) > flags[4])) {
        if ((int) value != 0) {
            flags[4] -= amount_number((int) value);
        }
    } else {
        long long int int_part = (long long int) start_value;
        long double fraction = start_value - (long double) int_part;
        if (int_part == 0) {
            for (int i = 0; i < 3; ++i) {
                if ((int) (fraction * 10) == 0) {
                    flags[4]++;
                    fraction *= 10;
                } else {
                    break;
                }
            }
        } else {
            flags[4] -= amount_number(int_part);
        }
        flags[6] = 'F';
        value = start_value;
    }
    return value;
}

void output_float(char *buffer, long double fraction, int *index, int flags[]) {
    int whole_part = fraction * 10;
    flags[4] += 1;
    fraction = (fraction * 10) - whole_part;
    int inFlag = 0;
    for (int i = 0; (fraction > 0 && i < flags[4]) || i < flags[4];
         whole_part = fraction * 10,
             fraction = (fraction * 10) - whole_part, i++, *index += 1) {
        buffer[*index] = '0' + whole_part;
        if (buffer[*index] > '4' && i == flags[4] - 1) {
            int temp = *index - 1;
            while (buffer[temp] == '9') {
                buffer[temp] = '0';
                temp--;
            }
            if (buffer[temp] == '.') {
                temp--;
                while (buffer[temp] == '9') {
                    buffer[temp] = '0';
                    temp--;
                }
            }
            buffer[temp] = buffer[temp] + 1;
        }
        if (i == 1) inFlag = 1;
    }
    *index -= 1;
    if (inFlag && (flags[6] == 'g' || flags[6] == 'G' || flags[6] == 'F') && !flags[2]) {
        int i = *index - 1;
        for (; buffer[i] == '0' || buffer[i] == '.'; i--) {
            if (buffer[i] == '.') {
                buffer[i] = '\0';
                i--;
                break;
            }
            buffer[i] = '\0';
        }
        *index = i + 1;
    }
}

void put_e_E(char *temp_buffer, int *temp_buffer_index, const int flags[], char sign, int count) {
    temp_buffer[*temp_buffer_index] = flags[6];
    *temp_buffer_index += 1;
    temp_buffer[*temp_buffer_index] = sign;
    *temp_buffer_index += 1;
    if (count < 10) {
        temp_buffer[*temp_buffer_index] = '0';
        *temp_buffer_index += 1;
    }
    for (int i = s21_powl(10, amount_number(count) - 1); i > 0; i /= 10) {
        temp_buffer[*temp_buffer_index] = '0' + (count / i % 10);
        *temp_buffer_index += 1;
    }
}

void put_d_f(char *temp_buffer, int *temp_index, int flags[], long double value) {
    int count = 0;
    char sign;
    if (flags[4] == -1) flags[4] = 6;
    if (flags[6] == 'g' || flags[6] == 'G') {
        value = specifier_G(value, flags, &count, &sign);
    } else if (flags[6] == 'e' || flags[6] == 'E') {
        sign = output_sign(&value, &count);
    }
    long long unsigned int whole_part = (long long unsigned int) value;
    long double fraction = value - (long double) whole_part;
    for (long long unsigned int i = s21_powl(10, amount_number(whole_part) - 1); i > 0; i /= 10) {
        temp_buffer[*temp_index] = '0' + (whole_part / i % 10);
        *temp_index += 1;
    }
    if (flags[4] > 0 || flags[2]) {
        temp_buffer[*temp_index] = '.';
        *temp_index += 1;
    }
    output_float(temp_buffer, fraction, temp_index, flags);
    flags[6] == 'g' || flags[6] == 'G' ? flags[6] -= 2 : 0;
    if (flags[6] == 'e' || flags[6] == 'E') {
        put_e_E(temp_buffer, temp_index, flags, sign, count);
    }
}

void put_nan(char *buffer, int *index) {
    buffer[*index] = 'n';
    *index += 1;
    buffer[*index] = 'a';
    *index += 1;
    buffer[*index] = 'n';
    *index += 1;
}

void put_inf(char *buffer, int *index) {
    buffer[*index] = 'i';
    *index += 1;
    buffer[*index] = 'n';
    *index += 1;
    buffer[*index] = 'f';
    *index += 1;
}

void specifier_f_e_E_g_G(char *buffer, int *index, int flags[], va_list va) {
    long double value = 0;
    char tempBuff[1024];
    int tempIndex = 0;
    if (flags[5] == 2)
        value = va_arg(va, long double);
    else if (flags[5] == 1 || flags[5] == 4)
        *index = -1;
    else
        value = va_arg(va, double);
    int flag = isnan(value) ? 1 : isinf(value) ? 2 : 0;
    flag == 1 ? put_nan(buffer, index) : 0;
    flag == 2 ? put_inf(buffer, index) : 0;
    if (*index != -1 && flag == 0) {
        if (value < 0) {
            buffer[*index] = '-';
            *index += 1;
            value *= -1;
        } else if (flags[0]) {
            buffer[*index] = flags[0];
            *index += 1;
        }
        put_d_f(tempBuff, &tempIndex, flags, value);
        if (flags[1] == 2 && flags[3] > tempIndex) {
            put_space(buffer, index, flags[3] - *index, '0');
            tempIndex < *index ? *index -= tempIndex : 0;
        }
        for (int i = 0; i < tempIndex; i++) {
            buffer[*index] = tempBuff[i];
            *index += 1;
        }
        buffer[*index] = '\0';
    }
}

void specifier_p(char *buffer, int *index, int flags[], void *value) {
    if (flags[0]) {
        *index = -1;
    } else if (flags[1] > 1 || flags[2]) {
        *index = -1;
    } else if (flags[4] != -1) {
        *index = -1;
    } else if ((flags[5] > 0 && flags[5] < 3) || flags[5] == 4) {
        *index = -1;
    } else if (*index != -1) {
        unsigned long adress = (unsigned long) value;
        char little_buff[12];
        int i = 0;
        buffer[*index] = '0';
        *index += 1;
        buffer[*index] = 'x';
        *index += 1;
        do {
            unsigned long uno = (int) (adress % 16);
            adress /= 16;
            little_buff[i] = uno > 9 ? (int) ('W' + uno) : (int) ('0' + uno);
            i++;
        } while (adress != 0);
        i--;
        for (; i >= 0; buffer[*index] = little_buff[i], *index += 1, i--) { ; }
    }
}

void spcae_8_16(char *buffer, const char *temp_buffer, int i, int *index, const int flags[]) {
    int width = flags[1] == 2 && flags[3] > i ? flags[3] - i - *index : flags[4] > i ? flags[4] - i : i;
    if (width > 0 && (flags[1] == 2 || flags[4] - i > 0)) {
        put_space(buffer, index, width - 1, '0');
    }
    if (width > 0 || flags[4] != 0) {
        for (; i >= 0; buffer[*index] = temp_buffer[i], *index += 1, i--) { ; }
    }
}

unsigned long int get_lengh(const int flags[], va_list va) {
    unsigned long int temp = flags[5] == 1 ? (unsigned short int) va_arg(va, int) :
                             flags[5] == 3 || flags[5] == 4 ? va_arg(va, unsigned long int) :
                             (unsigned long int) va_arg(va, unsigned int);
    return temp;
}

void specifier_o(char *buffer, int *index, int flags[], va_list va) {
    char rBuffer[25] = "";
    int i = 0;
    unsigned long int n = get_lengh(flags, va);
    for (; n >= 8; i++, n /= 8) {
        int temp = n % 8;
        n -= temp;
        rBuffer[i] = temp + '0';
    }
    n < 8 ? rBuffer[i] = n + '0' : 0;
    flags[2] && n > 0 ? i++, rBuffer[i] = '0' : 0;
    spcae_8_16(buffer, rBuffer, i, index, flags);
}

void specifier_x_X(char *buffer, int *index, int flags[], va_list va) {
    unsigned long int value = get_lengh(flags, va);
    char maxChr = flags[6] == 'x' ? 'W' : '7';
    char little_buff[254] = "";
    int i = 0;
    *index = flags[0] == 43 ? -1 : *index;
    for (; value >= 16 && *index != -1; i++) {
        unsigned uno = value % 16;
        value /= 16;
        little_buff[i] = uno > 9 ? maxChr + uno : '0' + uno;
    }
    if (value < 16 && *index != -1) {
        little_buff[i] = value > 9 ? maxChr + value : '0' + value;
    }
    if (flags[2] && value > 0 && *index != -1) {
        buffer[*index] = '0';
        *index += 1;
        buffer[*index] = flags[6] == 'x' ? 'x' : 'X';
        *index += 1;
    }
    *index != -1 ? spcae_8_16(buffer, little_buff, i, index, flags) : 0;
}

void specifier_n(int *value, const int *index) {
    *value = *index;
}

long double s21_powl(long double a, int n) {
    long double result = 1.;
    while (n > 0) {
        if ((n & 1) != 0)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}

int amount_number(unsigned long long int n) {
    int count = 0;
    do {
        n /= 10;
        count++;
    } while (n != 0);
    return count;
}

void put_space(char *buffer, int *index, int indexSpace, char c) {
    int sumIndex = indexSpace + *index;
    while (*index < sumIndex) {
        buffer[*index] = c;
        *index += 1;
    }
}

char *put_precision(char *format_pointer, int flags[], va_list va) {
    int temp_index = 0;
    int result = 0;
    if (*format_pointer == '0') {
        flags[1] = 2;
        format_pointer++;
    }
    if ((*format_pointer >= '0' && *format_pointer <= '9') || *format_pointer == '*') {
        temp_index = 3;
    } else if (*format_pointer == '.') {
        temp_index = 4;
        format_pointer++;
        flags[temp_index] = 0;
    }
    if (*format_pointer == '*') {
        format_pointer++;
        flags[temp_index] = va_arg(va, int);
        if (flags[temp_index] < 0) {
            flags[1] = 1;
            flags[temp_index] *= -1;
        }
    } else if (*format_pointer >= '0' && *format_pointer <= '9') {
        while (*format_pointer >= '0' && *format_pointer <= '9') {
            result = result * 10 + (*format_pointer - 48);
            format_pointer++;
        }
        flags[temp_index] = result;
    }
    return format_pointer;
}

char *put_flags(int flags[], int *buffer_index, char *format_pointer, va_list va) {  // До этой нужны
    while (*format_pointer && *buffer_index != -1) {
        if ((*format_pointer == ' ' || *format_pointer == '+') && !flags[0]) {
            flags[0] = *format_pointer;
            format_pointer++;
        } else if (*format_pointer == '-' && !flags[1]) {
            flags[1] = 1;
            format_pointer++;
        } else if (*format_pointer == '#') {
            flags[2] = 1;
            format_pointer++;
        } else if (*format_pointer == 'h' && !flags[5]) {
            flags[5] = 1;
            format_pointer++;
        } else if (*format_pointer == 'L' && !flags[5]) {
            flags[5] = 2;
            format_pointer++;
        } else if (*format_pointer == 'l') {
            if (flags[5] == 3) {
                flags[5] = 4;
            } else if (flags[5] == 0) {
                flags[5] = 3;
            } else {
                *buffer_index = -1;
            }
            format_pointer++;
        } else if ((*format_pointer >= '0' && *format_pointer <= '9')
            || (*format_pointer == '*' || *format_pointer == '.')) {
            format_pointer = put_precision(format_pointer, flags, va);
        } else if (s21_strchr("difcsueEgGxXonp%", *format_pointer) != s21_NULL) {
            flags[6] = *format_pointer++;
            break;
        } else {
            *buffer_index = -1;
        }
    }
    return format_pointer;
}

void specifier(char *buffer, int *buffer_index, int flags[], va_list va) {
    if (flags[6] == 'd' || flags[6] == 'i') {
        specifier_d_i(buffer, buffer_index, flags, va);
    } else if (flags[6] == 'u') {
        specifier_u(buffer, buffer_index, flags, va);
    } else if (flags[6] == 'f' || flags[6] == 'e' || flags[6] == 'E' || flags[6] == 'g' || flags[6] == 'G') {
        specifier_f_e_E_g_G(buffer, buffer_index, flags, va);
    } else if (flags[6] == 'c') {
        specifier_c(buffer, buffer_index, flags, va);
    } else if (flags[6] == 's') {
        specifier_s(buffer, buffer_index, flags, va);
    } else if (flags[6] == 'o') {
        specifier_o(buffer, buffer_index, flags, va);
    } else if (flags[6] == 'p') {
        specifier_p(buffer, buffer_index, flags, va_arg(va, void*));
    } else if (flags[6] == '%') {
        for (int i = 0; i < 6; i++) {
            flags[i] > 0 ? *buffer_index = -1 : 0;
        }
        buffer[*buffer_index] = '%';
        *buffer_index += 1;
    } else if (flags[6] == 'x' || flags[6] == 'X') {
        specifier_x_X(buffer, buffer_index, flags, va);
    } else {
        *buffer_index = -1;
    }
}

int parser(char *buffer, char *format, va_list va) {
    int buffer_index = 0;
    char *format_pointer = format;
    while (*format_pointer && buffer_index != -1) {
        char temp_buffer[1024] = {0};
        int temp_index_buffer = 0;
        if (*format_pointer != '%') {
            buffer[buffer_index++] = *format_pointer++;
            continue;
        }
        int flags[] = {0, 0, 0, 0, -1, 0, 0};
        format_pointer++;
        format_pointer = put_flags(flags, &temp_index_buffer, format_pointer, va);
        // i = 0 ' ' = 32 и '+' = 43
        // i = 1 '-' = 1 и '0' = 2
        // i = 2 '#'
        // i = 3 'число and *'
        // i = 4 '.число and .*'
        // i = 5 'h = 1 AND L = 2 and l = 3 and ll = 4'
        // i = 6 'Спецификатор'
        if (flags[6] == 'n') {
            specifier_n(va_arg(va, int *), &buffer_index);
            continue;
        }
        specifier(temp_buffer, &temp_index_buffer, flags, va);
        if (!flags[1] && flags[3] > temp_index_buffer && temp_index_buffer != -1) {
            put_space(buffer, &buffer_index, flags[3], ' ');
            buffer_index -= temp_index_buffer;
        }
        for (int i = 0; i < temp_index_buffer; i++) {
            buffer[buffer_index] = temp_buffer[i];
            buffer_index++;
        }
        if (flags[1] == 1 && flags[3] > temp_index_buffer) {
            put_space(buffer, &buffer_index, flags[3] - temp_index_buffer, ' ');
        }
        if (temp_index_buffer == -1) {
            buffer_index = temp_index_buffer;
            buffer[0] = '\0';
        }
    }
    if (buffer_index > 0) {
        buffer[buffer_index] = '\0';
    }
    return buffer_index;
}

int s21_sprintf(char *buffer, char *format, ...) {
    va_list va;
    va_start(va, format);
    const int ret = parser(buffer, format, va);
    va_end(va);
    return ret;
}
