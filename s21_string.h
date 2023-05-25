#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

typedef unsigned long long s21_size_t;

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>

#include "s21_string.h"

#define S21_NULL (void *)0

typedef struct flag {
  int width;
  int n;
  int minus;
  int lonely_char;
  int length_2l;
  int length_l;
  int length_h;
  int length_L;
  int probel;
  int str_probel;
  int astra;
  int pointer;
  int result;
  int error;
  int eof;
  int format_string;
  int procent;       // флаг  знака процент
  int format_count;  // курсор по форматной строке
  char ch;           // для get_symbol
  int str_count;     // курсор по символьной строке
  int zero;          //пустая символьная строка
  int string_func;   // флаг числовых операций
} sscanf_flags;

typedef struct flag_printf {
  int width;
  int precision;
  int minus;
  int plus;
  int space;
  int length_l;
  int length_h;
  int length_L;
  int zero;
  int hashtag;
  int dot;
  int g_flag;
  int e_flag;
  int like_e_flag;
  int g_case;
} flags;

int s21_sprintf(char *s, const char *format, ...);
void init_flags(flags *flag_printf);
int parser_flags(int i, flags *flag_printf, const char *format);
int parser_lenght(int i, flags *flag_printf, const char *format);
int search(int i, const char *format, flags *flag_printf, va_list *args);
void parser_specifiers(char *str, const char *format, int *j, const int *i,
                       va_list args, flags *flag_printf);
void get_int(char *str, int *j, va_list args, flags *flag_printf,
             const char *c);
void get_char(char *str, int *j, va_list args, flags *flag_printf);
void get_float(char *str, int *j, va_list args, flags *flag_printf);
void get_string(char *str, int *j, va_list args, flags *flag_printf);
void get_strlen_before_percent(const int *j, va_list args);
void get_pointer(char *str, int *j, va_list args, flags *flag_printf,
                 const char *c);
void get_octal(char *str, int *j, va_list args, flags *flag_printf,
               const char *c);
void get_hex(char *str, int *j, va_list args, flags *flag_printf,
             const char *c);
void get_mantissa(char *str, int *j, va_list args, flags *flag_printf,
                  const char *c);

void vaargs_of_int(const char *c, long long int *res, flags *flag_printf,
                   va_list args);
void work_with_int(char *str, int *j, char *d, long long int *res,
                   int *get_sign, int *width_of_int, int *accuracy,
                   flags *flag_printf, const char *c);
void sign_of_number(char *str, int *j, int *get_sign, flags *flag_printf);
void octal_and_hex_with_hash(char *str, int *j, flags *flag_printf,
                             const char *c);
void width_and_precision(flags *flag_printf, char *d, int *accuracy,
                         int *width_of_int, int *get_sign, const char *c);
void flag_to_zero(flags *flag_printf, const int *accuracy,
                  const long long int *res, const char *c);
void spaces_from_start_of_int(char *str, int *j, flags *flag_printf,
                              const char *c, const int *width_of_int);
void spaces_in_the_end_of_int(char *str, int *j, flags *flag_printf,
                              const char *c, const int *width_of_int);
void write_zero(char *str, int *j, flags *flag_printf, const char *c,
                const int *width_of_int, const int *accuracy);
char *int_to_char(long long int *number, char *buffer, const int *radix);
void work_with_char(char *str, int *j, flags *flag_printf, const char *c);
char *float_to_char(char *res, long double f, flags *flag_printf);
void round_float(long long int *num, flags *flag_printf);
void prepare_float(long double *check_float, long double *f,
                   flags *flag_printf);
void work_with_float(char *str, int *j, int *get_sign, char *string_of_float,
                     flags *flag_printf);
void width_for_mantissa_and_float(flags *flag_printf, int *width,
                                  const int *sign, char *number_string);
void work_with_string(char *str, int *j, flags *flag_printf,
                      char *buffer_string);
char *hex_to_char(long long int *hex, char *hex_string, int *base,
                  const char *c);
char x_char(const long long int *hex, const int *base, const char *c);
void prepare_mantissa(long double *mantissa, int *res, flags *flag_printf,
                      long double copy_mantissa);
void prepare_mantissa_with_zero_precision(long double *mantissa,
                                          long long int *round_mantissa,
                                          int *res, long double copy_mantissa,
                                          int *g_specificier,
                                          flags *flag_printf);
void final_mantissa_number(char *str, int *j, flags *flag_printf, const char *c,
                           const char *e_sign, const int *res,
                           long double copy_mantissa, int g_specificier);
void flags_before_sign_for_mantissa(char *str, int *j, flags *flag_printf,
                                    const int *width_of_mantissa, int res,
                                    long double copy_mantissa,
                                    int g_specificier);
void flags_after_sign_for_mantissa(char *str, int *j, flags *flag_printf,
                                   const int *width_of_mantissa,
                                   const int *get_sign, int res,
                                   long double copy_mantissa,
                                   int g_specificier);
char *g_mantissa_with_zero_precision_to_char(const int *res,
                                             long long int *round_mantissa,
                                             char *exp,
                                             const int *g_specificier);
char *g_mantissa_to_char(char *exp, const int *res, flags *flag_printf,
                         long double mantissa, long double copy_mantissa);

int s21_sscanf(const char *str, const char *format, ...);

void spec_d(char *temp, va_list ap, sscanf_flags *flag);

void spec_f(char *temp, va_list ap, sscanf_flags *flag);

void spec_x(char *temp, va_list ap, sscanf_flags *flag);

void spec_u(char *temp, va_list ap, sscanf_flags *flag);

void spec_i(char *temp, va_list ap, sscanf_flags *flag);

void spec_o(char *temp, va_list ap, sscanf_flags *flag);

void spec_s(char *temp, va_list ap, sscanf_flags *flag);

void spec_n(va_list ap, sscanf_flags *flag);

void spec_p(char *temp, va_list ap, sscanf_flags *flag);

int char_to_int(char *temp, sscanf_flags *flag);

int char_to_hex(char *temp, sscanf_flags *flag);

int char_to_oct(char *temp, sscanf_flags *flag);

float char_to_float(char *str, sscanf_flags *flag);

long double char_to_long_double(char *str, sscanf_flags *flag);

double char_to_double(char *str, sscanf_flags *flag);

char *get_pattern(char *temp, const char *str, sscanf_flags *flag);

char *get_pattern_int(char *temp, const char *str, sscanf_flags *flag);

char *get_pattern_x(const char *format, char *temp, const char *str,
                    sscanf_flags *flag);

char *get_pattern_f(char *temp, const char *str, sscanf_flags *flag);

void get_format_pattern(const char *str, const char *format,
                        sscanf_flags *flag);

void get_symbol(const char *str, const char *format, sscanf_flags *flag);

void check_spec_symbol(const char *str, const char *format, sscanf_flags *flag);

void check_width(const char *format, sscanf_flags *flag);

void check_modificators(const char *format, sscanf_flags *flag);

void pars_specificators(const char *str, char *temp, const char *format,
                        va_list ap, sscanf_flags *flag);

void spec_c(va_list ap, sscanf_flags *flag);

void skeep_space(const char *str, sscanf_flags *flag);

void *s21_memchr(const void *str, int c, s21_size_t n);

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

void *s21_memcpy(void *dest, const void *src, s21_size_t n);

void *s21_memmove(void *dest, const void *src, s21_size_t n);

void *s21_memset(void *str, int c, s21_size_t n);

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

char *s21_strcpy(char *dest, const char *src);

char *s21_strncpy(char *dest, const char *src, s21_size_t n);

char *s21_strcat(char *dest, const char *src);

char *s21_strncat(char *dest, const char *src, s21_size_t n);

char *s21_strchr(const char *str, int c);

int s21_strcmp(const char *str1, const char *str2);

s21_size_t s21_strlen(const char *str);

char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strrchr(const char *str, int c);

s21_size_t s21_strspn(const char *str1, const char *str2);

char *s21_strstr(const char *haystack, const char *needle);

char *s21_strtok(char *str, const char *delim);

s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strerror(int errnum);

// Special string processing functions
void *s21_to_upper(const char *str);

void *s21_to_lower(const char *str);

void *s21_insert(const char *src, const char *str, s21_size_t start_index);

void *s21_trim(const char *src, const char *trim_chars);

// int s21_sprintf(char *s, const char *format, ...);

#endif  // SRC_S21_STRING_H_
