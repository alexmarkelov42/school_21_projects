#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>

typedef long unsigned s21_size_t;

#ifndef s21_NULL
#define s21_NULL ((void*)0)
#endif

void specifier(char* buffer, int* buffer_index, int flags[], va_list va);
void specifier_c(char* buffer, int* index, const int flags[], va_list va);
void specifier_s(char* buffer, int* index, int flags[], va_list va);
char output_sign(long double *value, int* count);
long double specifier_G(long double value, int flags[], int* count, char* plusOrMinus);
void output_float(char *buffer, long double fraction, int *index, int flags[]);
void put_e_E(char* temp_buffer, int* temp_buffer_index, const int flags[], char sign, int count);
void put_d_f(char* temp_buffer, int* temp_index, int flags[], long double value);
void specifier_f_e_E_g_G(char* buffer, int* index, int flags[], va_list va);
void specifier_d_i(char* buffer, int* index, int flags[], va_list va);
void zapolneniTempBufferaInt(char* buffer, int* index, int flags[], long long int value);
void specifier_u(char* buffer, int* index, int flags[], va_list va);
void put_u(char* buffer, int* index, int flags[], long long unsigned int value);
void zapolnenie(char* buffer, int* index, int flags[], const char* tempBuff, const int *tempIndex);
void specifier_p(char* buffer, int* index, int flags[], void *value);
void specifier_o(char* buffer, int* index, int flags[], va_list va);
void specifier_x_X(char* buffer, int* index, int flags[], va_list va);
void specifier_n(int *value, const int *index);
int amount_number(unsigned long long int n);
void put_space(char* buffer, int* index, int indexSpace, char c);
char* put_precision(char* format_pointer, int flags[], va_list va);
char* put_flags(int flags[], int* buffer_index, char* format_pointer, va_list va);
int parser(char* buffer, char* format, va_list va);
int s21_sprintf(char* buffer, char* format, ...);
long double s21_powl(long double a, int n);
void* s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void* s21_memcpy(void *dest, const void *src, s21_size_t n);
void* s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char  *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char* s21_strcpy(char *dest, const char *src);
char* s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char* s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *src, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char* haystack, const char* needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
#endif  // SRC_S21_STRING_H_
