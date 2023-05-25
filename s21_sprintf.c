#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  flags flag_printf_printf = {0};
  int j = 0;
  va_list args;
  va_start(args, format);
  for (int i = 0; i < (int)s21_strlen(format) && format[i] != '\0'; i++) {
    if (format[i] != '%') {
      str[j++] = format[i];
    } else {
      i++;
      if (format[i] == '%') {
        str[j++] = format[i];
      } else {
        if (format[i] == '.' && format[i + 1] == '-') i++;
        init_flags(&flag_printf_printf);
        i = parser_flags(i, &flag_printf_printf, format);
        i = search(i, format, &flag_printf_printf, &args);
        i = parser_lenght(i, &flag_printf_printf, format);
        parser_specifiers(str, format, &j, &i, args, &flag_printf_printf);
      }
    }
  }
  str[j] = '\0';
  va_end(args);
  return j;
}

void init_flags(flags *flag_printf) {
  flag_printf->width = 0;
  flag_printf->precision = -1;
  flag_printf->minus = 0;
  flag_printf->plus = 0;
  flag_printf->space = 0;
  flag_printf->length_l = 0;
  flag_printf->length_h = 0;
  flag_printf->length_L = 0;
  flag_printf->zero = 0;
  flag_printf->hashtag = 0;
  flag_printf->dot = 0;
  flag_printf->g_flag = 0;
  flag_printf->e_flag = 0;
  flag_printf->g_case = 0;
  flag_printf->like_e_flag = 0;
}

int parser_flags(int i, flags *flag_printf, const char *format) {
  while (format[i] == '-' || format[i] == '+' || format[i] == ' ' ||
         format[i] == '0' || format[i] == '#' || format[i] == '.') {
    switch (format[i]) {
      case '0':
        flag_printf->zero = 1;
        break;
      case '-':
        flag_printf->minus = 1;
        break;
      case '+':
        flag_printf->plus = 1;
        break;
      case ' ':
        flag_printf->space = 1;
        break;
      case '#':
        flag_printf->hashtag = 1;
        break;
      case '.':
        flag_printf->dot = 1;
        break;
    }
    i++;
  }
  return i;
}

int parser_lenght(int i, flags *flag_printf, const char *format) {
  while (format[i] == 'l' || format[i] == 'h' || format[i] == 'L') {
    switch (format[i]) {
      case 'l':
        flag_printf->length_l = 1;
        break;
      case 'h':
        flag_printf->length_h = 1;
        break;
      case 'L':
        flag_printf->length_L = 1;
        break;
    }
    i++;
  }
  return i;
}

int search(int i, const char *format, flags *flag_printf, va_list *args) {
  if (!flag_printf->dot) {
    for (; s21_strchr("0123456789", format[i]); i++) {
      flag_printf->width = (flag_printf->width * 10) + (format[i] - 48);
    }
    for (; format[i] == '*'; i++) flag_printf->width = va_arg(*args, int);
  }
  if (format[i] == '.') {
    flag_printf->precision = 0;
    if (flag_printf->minus) {
    }
    for (i++; s21_strchr("0123456789", format[i]); i++) {
      flag_printf->precision = (flag_printf->precision * 10) + (format[i] - 48);
    }
    for (; format[i] == '*'; i++) flag_printf->precision = va_arg(*args, int);
  }
  if (flag_printf->dot) {
    flag_printf->precision = 0;
    for (; s21_strchr("0123456789", format[i]); i++) {
      flag_printf->precision = (flag_printf->precision * 10) + (format[i] - 48);
    }
    for (; format[i] == '*'; i++) flag_printf->precision = va_arg(*args, int);
  }
  return i;
}

void parser_specifiers(char *str, const char *format, int *j, const int *i,
                       va_list args, flags *flag_printf) {
  char c = format[*i];
  switch (c) {
    case 'u':
      get_int(str, j, args, flag_printf, &c);
      break;
    case 'd':
    case 'i':
      get_int(str, j, args, flag_printf, &c);
      break;
    case 'c':
      get_char(str, j, args, flag_printf);
      break;
    case 'f':
      get_float(str, j, args, flag_printf);
      break;
    case 's':
      get_string(str, j, args, flag_printf);
      break;
    case 'n':
      get_strlen_before_percent(j, args);
      break;
    case 'p':
      get_pointer(str, j, args, flag_printf, &c);
      break;
    case 'o':
      get_octal(str, j, args, flag_printf, &c);
      break;
    case 'X':
    case 'x':
      get_hex(str, j, args, flag_printf, &c);
      break;
    case 'E':
    case 'e':
      get_mantissa(str, j, args, flag_printf, &c);
      break;
    case 'G':
    case 'g':
      get_mantissa(str, j, args, flag_printf, &c);
      break;
  }
}

void get_int(char *str, int *j, va_list args, flags *flag_printf,
             const char *c) {
  long long int res = 0;
  char *buf = S21_NULL;
  int get_sign = 0, width_of_int = 0, accuracy = 0;
  int base = 10;
  vaargs_of_int(c, &res, flag_printf, args);
  if ((*c) == 'u' && flag_printf->space) flag_printf->space = 0;
  if (flag_printf->precision || (res && !flag_printf->precision)) {
    if (res < 0) {
      get_sign = 1;
      res = labs(res);
      flag_printf->space = 0;
      flag_printf->plus = 0;
    }
    if (flag_printf->space && flag_printf->plus) flag_printf->plus = 0;
    char *d = int_to_char(&res, buf, &base);
    work_with_int(str, j, d, &res, &get_sign, &width_of_int, &accuracy,
                  flag_printf, c);
    free(buf);
    free(d);
  }
}

void vaargs_of_int(const char *c, long long int *res, flags *flag_printf,
                   va_list args) {
  if ((*c) == 'd' || (*c) == 'i') {
    if (flag_printf->length_l == 1) {
      (*res) = va_arg(args, long int);
    } else if (flag_printf->length_h == 1) {
      (*res) = (short)va_arg(args, int);
    } else {
      (*res) = va_arg(args, int);
    }
  } else if ((*c) == 'u') {
    flag_printf->plus = 0;
    if (flag_printf->length_l == 1) {
      (*res) = va_arg(args, unsigned long int);
    } else if (flag_printf->length_h == 1) {
      (*res) = (unsigned short int)va_arg(args, unsigned int);
    } else {
      (*res) = va_arg(args, unsigned int);
    }
  }
}

char *int_to_char(long long int *number, char *buffer, const int *radix) {
  int count = 0;
  int check = (*radix) - 1;
  buffer = (char *)calloc(50, sizeof(char));
  while ((*number) > check) {
    buffer[count++] = ((*number) % (*radix)) + '0';
    (*number) = (*number) / (*radix);
  }
  buffer[count++] = (*number) + '0';
  buffer[count] = '\0';

  for (int i = 0; i < count / 2; i++) {
    char tmp = buffer[i];
    buffer[i] = buffer[count - 1 - i];
    buffer[count - 1 - i] = tmp;
  }
  return buffer;
}

void work_with_int(char *str, int *j, char *d, long long int *res,
                   int *get_sign, int *width_of_int, int *accuracy,
                   flags *flag_printf, const char *c) {
  width_and_precision(flag_printf, d, accuracy, width_of_int, get_sign, c);
  flag_to_zero(flag_printf, accuracy, res, c);
  spaces_from_start_of_int(str, j, flag_printf, c, width_of_int);
  sign_of_number(str, j, get_sign, flag_printf);
  octal_and_hex_with_hash(str, j, flag_printf, c);
  write_zero(str, j, flag_printf, c, width_of_int, accuracy);
  if ((*c) == 'p') {
    str[(*j)++] = '0';
    str[(*j)++] = 'x';
  }
  for (int i = 0; i < (int)s21_strlen(d); i++) {
    str[(*j)++] = d[i];
  }
  spaces_in_the_end_of_int(str, j, flag_printf, c, width_of_int);
}

void sign_of_number(char *str, int *j, int *get_sign, flags *flag_printf) {
  if ((*get_sign)) {
    str[(*j)++] = '-';
  } else if (flag_printf->plus) {
    str[(*j)++] = '+';
  }
}

void octal_and_hex_with_hash(char *str, int *j, flags *flag_printf,
                             const char *c) {
  if (flag_printf->hashtag && ((*c) == 'x' || (*c) == 'X') &&
      !flag_printf->zero) {
    str[(*j)++] = '0';
    str[(*j)++] = (*c) == 'x' ? 'x' : 'X';
  } else if (flag_printf->hashtag && (*c) == 'o' && !flag_printf->zero) {
    str[(*j)++] = '0';
  }
}

void width_and_precision(flags *flag_printf, char *d, int *accuracy,
                         int *width_of_int, int *get_sign, const char *c) {
  if (flag_printf->precision > 0)
    (*accuracy) = (flag_printf->precision > (int)s21_strlen(d))
                      ? flag_printf->precision - (int)s21_strlen(d)
                      : 0;
  if (flag_printf->width) {
    if ((*c) != 'p') {
      (*width_of_int) = (*get_sign)
                            ? flag_printf->width - (int)s21_strlen(d) -
                                  (*get_sign) - (*accuracy) - flag_printf->space
                            : flag_printf->width - (int)s21_strlen(d) -
                                  (*accuracy) - flag_printf->plus;
    } else {
      (*width_of_int) = flag_printf->width - (int)s21_strlen(d) - 2;
    }
  }
}

void flag_to_zero(flags *flag_printf, const int *accuracy,
                  const long long int *res, const char *c) {
  if ((*c) == 'o' && flag_printf->precision) {
    if ((*accuracy) > 0) flag_printf->hashtag = 0;
  }
  if (flag_printf->space && (*res) < 0) flag_printf->space = 0;

  if (flag_printf->minus && flag_printf->zero) flag_printf->minus = 0;

  if (((*c) == 'x' || (*c) == 'X') && flag_printf->space)
    flag_printf->space = 0;
}

void spaces_from_start_of_int(char *str, int *j, flags *flag_printf,
                              const char *c, const int *width_of_int) {
  if (flag_printf->space && flag_printf->width) {
    if ((*width_of_int) <= 0) {
      str[(*j)++] = ' ';
    } else if (flag_printf->minus) {
      str[(*j)++] = ' ';
    }
  } else if (flag_printf->space && !flag_printf->width) {
    str[(*j)++] = ' ';
  }
  if (flag_printf->width) {
    if ((*width_of_int) > 0 && !flag_printf->minus && !flag_printf->zero) {
      if ((*c) == 'x' || (*c) == 'X') {
        if (!flag_printf->hashtag) {
          for (int i = 0; i < (*width_of_int); i++) {
            str[(*j)++] = ' ';
          }
        } else {
          for (int i = 0; i < (*width_of_int) - 2; i++) {
            str[(*j)++] = ' ';
          }
        }
      } else if ((*c) == 'o') {
        if (!flag_printf->hashtag) {
          for (int i = 0; i < (*width_of_int); i++) {
            str[(*j)++] = ' ';
          }
        } else {
          for (int i = 0; i < (*width_of_int) - 1; i++) {
            str[(*j)++] = ' ';
          }
        }
      } else {
        for (int i = 0; i < (*width_of_int); i++) {
          str[(*j)++] = ' ';
        }
      }
    }
  }
}

void spaces_in_the_end_of_int(char *str, int *j, flags *flag_printf,
                              const char *c, const int *width_of_int) {
  if (flag_printf->width && flag_printf->minus) {
    if ((*width_of_int) > 0) {
      if (flag_printf->space) {
        for (int i = 0; i < ((*width_of_int) - flag_printf->space); i++) {
          str[(*j)++] = ' ';
        }
      } else {
        if (((*c) == 'x' || (*c) == 'X') && flag_printf->hashtag) {
          for (int i = 0; i < (*width_of_int) - 2; i++) {
            str[(*j)++] = ' ';
          }
        } else if ((*c) == 'o' && flag_printf->hashtag) {
          for (int i = 0; i < (*width_of_int) - 1; i++) {
            str[(*j)++] = ' ';
          }
        } else {
          for (int i = 0; i < (*width_of_int); i++) {
            str[(*j)++] = ' ';
          }
        }
      }
    }
  }
}

void write_zero(char *str, int *j, flags *flag_printf, const char *c,
                const int *width_of_int, const int *accuracy) {
  if (flag_printf->precision != -1) {
    for (int i = 0; i < (*accuracy); i++) str[(*j)++] = '0';
  } else if ((*width_of_int) > 0 && !flag_printf->minus && flag_printf->zero) {
    if (!flag_printf->space) {
      if (flag_printf->hashtag) {
        if ((*c) == 'x' || (*c) == 'X') {
          str[(*j)++] = '0';
          str[(*j)++] = (*c) == 'x' ? 'x' : 'X';
          for (int i = 0; i < (*width_of_int) - 2; i++) str[(*j)++] = '0';
        }
      } else {
        for (int i = 0; i < (*width_of_int); i++) str[(*j)++] = '0';
      }
    } else {
      str[(*j)++] = ' ';
      for (int i = 0; i < (*width_of_int) - 1; i++) str[(*j)++] = '0';
    }
  }
}

void get_char(char *str, int *j, va_list args, flags *flag_printf) {
  char c = va_arg(args, int);
  work_with_char(str, j, flag_printf, &c);
}

void work_with_char(char *str, int *j, flags *flag_printf, const char *c) {
  if (!flag_printf->width) {
    str[(*j)++] = *c;
  } else {
    int w = flag_printf->width - 1;
    if (!flag_printf->minus) {
      for (int s = 0; s < w; s++) str[(*j)++] = ' ';
      str[(*j)++] = *c;
    } else {
      str[(*j)++] = *c;
      for (int s = 0; s < w; s++) str[(*j)++] = ' ';
    }
  }
}

void get_float(char *str, int *j, va_list args, flags *flag_printf) {
  long double f = 0;
  int get_sign = 0;
  char *res = S21_NULL;
  if (flag_printf->length_L) {
    f = va_arg(args, long double);
  } else
    f = va_arg(args, double);
  if (f < 0) {
    get_sign = 1;
    f *= -1;
    flag_printf->space = 0;
    flag_printf->plus = 0;
  }
  char *string_of_float = float_to_char(res, f, flag_printf);
  work_with_float(str, j, &get_sign, string_of_float, flag_printf);
  free(res);
  free(string_of_float);
}

char *float_to_char(char *res, long double f, flags *flag_printf) {
  char *buf_f = S21_NULL;
  char *buf_f2 = S21_NULL;
  res = (char *)calloc(50, sizeof(char));
  int j = 0;
  int base = 10;
  if (flag_printf->precision == 0) {
    long long int round_f = round(f);
    char *reverse_round_f = int_to_char(&round_f, buf_f, &base);
    for (int i = 0; i < (int)s21_strlen(reverse_round_f); i++) {
      res[j++] = reverse_round_f[i];
    }
    if (flag_printf->hashtag) res[j++] = '.';
    free(reverse_round_f);
    free(buf_f);
  } else {
    if (flag_printf->precision == -1) flag_printf->precision = 6;
    long double num_float = f, after_dot;
    after_dot = num_float - (long long int)num_float;
    prepare_float(&num_float, &f, flag_printf);
    long long int x = (long long int)f;
    char *reverse = int_to_char(&x, buf_f, &base);
    for (int i = 0; i < (int)s21_strlen(reverse); i++) {
      res[j++] = reverse[i];
    }
    for (int accuracy = 0; accuracy < flag_printf->precision + 1; accuracy++) {
      after_dot *= 10;
    }
    long long int y = after_dot != after_dot ? 0 : round(after_dot);
    if (!flag_printf->g_flag ||
        (((y / (int)pow(10.0, (double)flag_printf->precision)) == 0) ||
         ((y / (int)pow(10.0, (double)flag_printf->precision)) % 10))) {
      if (!flag_printf->g_flag || y > 0) {
        round_float(&y, flag_printf);
        int g_counter = 0;
        if (flag_printf->g_flag && flag_printf->precision > 1) {
          while (!(y % 10)) {
            y /= 10;
            g_counter++;
          }
        }
        res[j++] = '.';
        char *reverse2 = int_to_char(&y, buf_f2, &base);
        if (flag_printf->precision == (int)s21_strlen(reverse2)) {
          for (int ind = 0; ind < (int)s21_strlen(reverse2); ind++) {
            res[j++] = reverse2[ind];
          }
        } else if (flag_printf->precision > (int)s21_strlen(reverse2)) {
          if (!flag_printf->g_flag || !g_counter) {
            for (int i = 0;
                 i < (flag_printf->precision - (int)s21_strlen(reverse2));
                 i++) {
              res[j++] = '0';
            }
          } else {
            for (int k = 0; k < (flag_printf->precision -
                                 (int)s21_strlen(reverse2) - g_counter);
                 k++) {
              res[j++] = '0';
            }
          }
          for (int ind = 0; ind < (int)s21_strlen(reverse2); ind++) {
            res[j++] = reverse2[ind];
          }
          if (flag_printf->g_case > 1 && flag_printf->hashtag) {
            for (int z = 0; z < g_counter; z++) {
              res[j++] = '0';
            }
          }
        }
        free(buf_f2);
        free(reverse2);
      }
    }
    free(reverse);
    free(buf_f);
  }
  return res;
}

void round_float(long long int *num, flags *flag_printf) {
  if (((*num) % 10) > 4) {
    (*num) = (*num) / 10 + 1;
    if (flag_printf->precision == 1 && (*num) == 10) {
      (*num) = 0;
    }
  } else {
    (*num) = (*num) / 10;
  }
}

void prepare_float(long double *check_float, long double *f,
                   flags *flag_printf) {
  int check_f = 0;
  while (check_f < (flag_printf->precision + 1)) {
    (*check_float) *= 10;
    check_f++;
  }
  long long int temp = (long long int)(*check_float);
  int check_temp = temp % (int)pow(10.0, (double)check_f);
  if (check_temp % 10 > 4) {
    check_temp = check_temp / 10 + 1;
    if (!(check_temp % 10)) {
      temp = (temp / 10 + 1) * 10;
      (*check_float) = (long double)temp;
    }
  }
  while (check_f) {
    (*check_float) /= 10;
    check_f--;
  }
  (*f) = (*check_float);
}

void work_with_float(char *str, int *j, int *get_sign, char *string_of_float,
                     flags *flag_printf) {
  int width_of_float = 0;
  width_for_mantissa_and_float(flag_printf, &width_of_float, get_sign,
                               string_of_float);
  if (flag_printf->space && (*get_sign)) {
    flag_printf->space = 0;
  }
  if (flag_printf->space && !flag_printf->width) {
    str[(*j)++] = ' ';
  } else if (flag_printf->space && flag_printf->width && !flag_printf->zero) {
    if (width_of_float <= flag_printf->space) {
      str[(*j)++] = ' ';
    } else if (!flag_printf->minus) {
      for (int w = 0; w < width_of_float; w++) {
        str[(*j)++] = ' ';
      }
    } else {
      str[(*j)++] = ' ';
    }
  } else if (!flag_printf->space && flag_printf->width && !flag_printf->minus) {
    if (!flag_printf->zero) {
      for (int w = 0; w < width_of_float; w++) {
        str[(*j)++] = ' ';
      }
    }
  }
  sign_of_number(str, j, get_sign, flag_printf);
  if (flag_printf->width && flag_printf->zero) {
    if (flag_printf->space) {
      str[(*j)++] = ' ';
      for (int w = 0; w < width_of_float - 1; w++) {
        str[(*j)++] = '0';
      }
    } else {
      for (int w = 0; w < width_of_float; w++) {
        str[(*j)++] = '0';
      }
    }
  }
  for (int i = 0; i < (int)s21_strlen(string_of_float); i++) {
    str[(*j)++] = string_of_float[i];
  }
  if (flag_printf->width && flag_printf->minus) {
    if (flag_printf->space) {
      for (int i = 0; i < width_of_float - 1; i++) {
        str[(*j)++] = ' ';
      }
    } else {
      for (int i = 0; i < width_of_float; i++) {
        str[(*j)++] = ' ';
      }
    }
  }
}

void width_for_mantissa_and_float(flags *flag_printf, int *width,
                                  const int *sign, char *number_string) {
  if (flag_printf->width) {
    if (flag_printf->e_flag && !flag_printf->precision && flag_printf->hashtag)
      (*width) =
          (*sign) == 1
              ? flag_printf->width - (int)s21_strlen(number_string) - (*sign)
              : flag_printf->width - (int)s21_strlen(number_string) -
                    flag_printf->plus - flag_printf->hashtag;
    else
      (*width) =
          (*sign) == 1
              ? flag_printf->width - (int)s21_strlen(number_string) - (*sign)
              : flag_printf->width - (int)s21_strlen(number_string) -
                    flag_printf->plus;
  }
}

void get_string(char *str, int *j, va_list args, flags *flag_printf) {
  char *tmp = va_arg(args, char *);
  char buffer_string[BUFSIZ] = {'\0'};
  s21_strcpy(buffer_string, tmp);
  work_with_string(str, j, flag_printf, buffer_string);
}

void work_with_string(char *str, int *j, flags *flag_printf,
                      char *buffer_string) {
  if (flag_printf->precision) {
    int len_of_string = 0;
    if (flag_printf->precision == -1)
      len_of_string = (int)s21_strlen(buffer_string);
    else if (flag_printf->precision > 0)
      len_of_string = flag_printf->precision <= (int)s21_strlen(buffer_string)
                          ? flag_printf->precision
                          : (int)s21_strlen(buffer_string);
    int width_of_string = flag_printf->width > len_of_string
                              ? flag_printf->width - len_of_string
                              : 0;
    if (flag_printf->width && !flag_printf->minus) {
      for (int w = 0; w < width_of_string; w++) {
        str[(*j)++] = ' ';
      }
      for (int i = 0; i < len_of_string; i++) {
        str[(*j)++] = buffer_string[i];
      }
    } else if (flag_printf->width && flag_printf->minus) {
      for (int i = 0; i < len_of_string; i++) {
        str[(*j)++] = buffer_string[i];
      }
      for (int w = 0; w < width_of_string; w++) {
        str[(*j)++] = ' ';
      }
    } else if (!flag_printf->width) {
      for (int i = 0; i < len_of_string; i++) {
        str[(*j)++] = buffer_string[i];
      }
    }
  } else if (flag_printf->width && flag_printf->precision == 0) {
    for (int w = 0; w < flag_printf->width; w++) {
      str[(*j)++] = ' ';
    }
  }
}

void get_strlen_before_percent(const int *j, va_list args) {
  int *strlen_before = S21_NULL;
  strlen_before = va_arg(args, int *);
  *strlen_before = (*j);
}

void get_pointer(char *str, int *j, va_list args, flags *flag_printf,
                 const char *c) {
  int *p = va_arg(args, int *);
  long long int pointer_number = 0;
  if (p != S21_NULL) {
    pointer_number = (unsigned long long)p;
  }
  char *pointer_string = S21_NULL;
  int base = 16, accuracy = 0, width_of_pointer = 0, get_sign = 0;
  char *pointer_res = hex_to_char(&pointer_number, pointer_string, &base, c);
  work_with_int(str, j, pointer_res, &pointer_number, &get_sign,
                &width_of_pointer, &accuracy, flag_printf, c);
  free(pointer_string);
  free(pointer_res);
}

void get_octal(char *str, int *j, va_list args, flags *flag_printf,
               const char *c) {
  long long int oct = 0;
  char *octal = S21_NULL;
  int base = 8;
  int get_sign = 0, width_of_int = 0, accuracy = 0;
  if (flag_printf->length_l == 1) {
    oct = va_arg(args, unsigned long int);
  } else if (flag_printf->length_h == 1) {
    oct = (unsigned short)va_arg(args, unsigned int);
  } else {
    oct = va_arg(args, unsigned int);
  }
  char *res = int_to_char(&oct, octal, &base);
  work_with_int(str, j, res, &oct, &get_sign, &width_of_int, &accuracy,
                flag_printf, c);
  free(octal);
  free(res);
}

void get_hex(char *str, int *j, va_list args, flags *flag_printf,
             const char *c) {
  long long int hex = 0;
  char *hex_string = S21_NULL;
  int base = 16;
  int get_sign = 0, width_of_int = 0, accuracy = 0;
  if (flag_printf->length_l == 1) {
    hex = va_arg(args, unsigned long int);
  } else if (flag_printf->length_h == 1) {
    hex = (unsigned short)va_arg(args, unsigned int);
  } else {
    hex = va_arg(args, unsigned int);
  }
  if (!hex) flag_printf->hashtag = 0;
  char *hex_res = hex_to_char(&hex, hex_string, &base, c);
  work_with_int(str, j, hex_res, &hex, &get_sign, &width_of_int, &accuracy,
                flag_printf, c);
  free(hex_string);
  free(hex_res);
}

char *hex_to_char(long long int *hex, char *hex_string, int *base,
                  const char *c) {
  int count = 0;
  int check = (*base) - 1;
  hex_string = (char *)calloc(50, sizeof(char));
  while ((*hex) > check) {
    hex_string[count++] = (((*hex) % (*base)) < 10) ? ((*hex) % (*base) + '0')
                                                    : x_char(hex, base, c);
    (*hex) /= (*base);
  }

  hex_string[count++] = (((*hex) % (*base)) < 10) ? ((*hex) % (*base) + '0')
                                                  : x_char(hex, base, c);
  hex_string[count] = '\0';

  for (int i = 0; i < count / 2; i++) {
    char tmp = hex_string[i];
    hex_string[i] = hex_string[count - 1 - i];
    hex_string[count - 1 - i] = tmp;
  }
  return hex_string;
}

char x_char(const long long int *hex, const int *base, const char *c) {
  char res;
  char x_hex = (*hex) % (*base);
  switch (x_hex) {
    case 10:
      res = ((*c) == 'X') ? 'A' : 'a';
      break;
    case 11:
      res = ((*c) == 'X') ? 'B' : 'b';
      break;
    case 12:
      res = ((*c) == 'X') ? 'C' : 'c';
      break;
    case 13:
      res = ((*c) == 'X') ? 'D' : 'd';
      break;
    case 14:
      res = ((*c) == 'X') ? 'E' : 'e';
      break;
    case 15:
      res = ((*c) == 'X') ? 'F' : 'f';
      break;
  }
  return res;
}

void get_mantissa(char *str, int *j, va_list args, flags *flag_printf,
                  const char *c) {
  long double mantissa = 0;
  char *exp = S21_NULL;
  int base = 10;
  int get_sign = 0, width_of_mantissa = 0;
  if (flag_printf->length_L) {
    mantissa = va_arg(args, long double);
  } else if (flag_printf->length_l) {
    mantissa = va_arg(args, double);
  } else {
    mantissa = va_arg(args, double);
  }
  if (mantissa < 0) {
    get_sign = 1;
    mantissa *= -1;
    flag_printf->plus = 0;
    flag_printf->space = 0;
  }
  if ((*c) == 'g' || (*c) == 'G') {
    flag_printf->g_flag = 1;
  } else
    flag_printf->e_flag = 1;
  long double copy_mantissa = mantissa;
  int res = 0, g_specificier = 0;

  if (flag_printf->g_flag && flag_printf->precision == 1)
    flag_printf->precision = 0;
  if (flag_printf->g_flag && flag_printf->plus) flag_printf->space = 0;

  char e_sign = 0;
  if ((int)mantissa != 0) {
    e_sign = '+';
  } else {
    e_sign = '-';
  }
  if (mantissa == 0) {
    e_sign = '+';
  }

  if (flag_printf->precision == 0) {
    long long int round_mantissa = 0;
    char *reverse_round_mantissa = S21_NULL;
    prepare_mantissa_with_zero_precision(&mantissa, &round_mantissa, &res,
                                         copy_mantissa, &g_specificier,
                                         flag_printf);
    if (!res) {
      e_sign = '+';
    }

    if (flag_printf->g_flag && copy_mantissa < 1)
      reverse_round_mantissa = g_mantissa_with_zero_precision_to_char(
          &res, &round_mantissa, exp, &g_specificier);
    else if (flag_printf->e_flag ||
             (flag_printf->g_flag && copy_mantissa >= 1 && res >= 0)) {
      reverse_round_mantissa = int_to_char(&round_mantissa, exp, &base);
    }
    width_for_mantissa_and_float(flag_printf, &width_of_mantissa, &get_sign,
                                 reverse_round_mantissa);
    flags_before_sign_for_mantissa(str, j, flag_printf, &width_of_mantissa, res,
                                   copy_mantissa, g_specificier);
    sign_of_number(str, j, &get_sign, flag_printf);
    flags_after_sign_for_mantissa(str, j, flag_printf, &width_of_mantissa,
                                  &get_sign, res, copy_mantissa, g_specificier);
    for (int i = 0; i < (int)s21_strlen(reverse_round_mantissa); i++) {
      str[(*j)++] = reverse_round_mantissa[i];
    }
    if (flag_printf->hashtag && flag_printf->e_flag) str[(*j)++] = '.';
    final_mantissa_number(str, j, flag_printf, c, &e_sign, &res, copy_mantissa,
                          g_specificier);
    if (flag_printf->width && width_of_mantissa > 0 && flag_printf->minus) {
      for (int i = 0; i < width_of_mantissa - 4; i++) str[(*j)++] = ' ';
    }
    free(exp);
    free(reverse_round_mantissa);

  } else {
    if (flag_printf->precision == -1) flag_printf->precision = 6;
    if (flag_printf->g_flag && mantissa >= 1) flag_printf->g_case = 1;

    prepare_mantissa(&mantissa, &res, flag_printf, copy_mantissa);
    char *mantissa_string = S21_NULL;
    if (flag_printf->g_flag && mantissa == 0) {
      long long int zero_mantissa = 0;
      mantissa_string = int_to_char(&zero_mantissa, exp, &base);
    } else if (flag_printf->e_flag ||
               (flag_printf->g_flag && res > 4 && flag_printf->precision) ||
               (flag_printf->g_flag && flag_printf->precision &&
                flag_printf->g_case > 1)) {
      mantissa_string = float_to_char(exp, mantissa, flag_printf);
    } else if (flag_printf->g_flag && res <= 4 && flag_printf->precision) {
      mantissa_string =
          g_mantissa_to_char(exp, &res, flag_printf, mantissa, copy_mantissa);
    } else if (!flag_printf->precision && flag_printf->g_case == 1) {
      long long int round_mantissa = roundl(mantissa);
      mantissa_string = g_mantissa_with_zero_precision_to_char(
          &res, &round_mantissa, exp, &g_specificier);
    } else if ((!flag_printf->precision && flag_printf->g_case > 1) ||
               (flag_printf->g_flag && mantissa == 0) ||
               (flag_printf->g_flag && res > 4 && !flag_printf->precision)) {
      long long int round_mantissa = mantissa > 0 ? roundl(mantissa) : 0;
      mantissa_string = int_to_char(&round_mantissa, exp, &base);
    }
    width_for_mantissa_and_float(flag_printf, &width_of_mantissa, &get_sign,
                                 mantissa_string);
    flags_before_sign_for_mantissa(str, j, flag_printf, &width_of_mantissa, res,
                                   copy_mantissa, g_specificier);
    sign_of_number(str, j, &get_sign, flag_printf);
    flags_after_sign_for_mantissa(str, j, flag_printf, &width_of_mantissa,
                                  &get_sign, res, copy_mantissa, g_specificier);
    for (int i = 0; i < (int)s21_strlen(mantissa_string); i++) {
      str[(*j)++] = mantissa_string[i];
    }
    final_mantissa_number(str, j, flag_printf, c, &e_sign, &res, copy_mantissa,
                          g_specificier);
    if (flag_printf->width && width_of_mantissa > 0 && flag_printf->minus) {
      if (((*c) == 'e' || (*c) == 'E') ||
          (flag_printf->g_flag && res > 0 && copy_mantissa >= 10 &&
           !flag_printf->precision && !g_specificier && !flag_printf->g_case) ||
          (flag_printf->g_flag && res > 4 && !flag_printf->g_case) ||
          flag_printf->like_e_flag) {
        for (int i = 0; i < width_of_mantissa - 4; i++) str[(*j)++] = ' ';
      } else {
        for (int i = 0; i < width_of_mantissa; i++) str[(*j)++] = ' ';
      }
    }
    free(exp);
    free(mantissa_string);
  }
}

void prepare_mantissa(long double *mantissa, int *res, flags *flag_printf,
                      long double copy_mantissa) {
  if (flag_printf->g_flag && (*mantissa) >= 1) {
    long long int g_mantissa = (long long int)(*mantissa);
    if (g_mantissa < 10) {
      flag_printf->precision--;
      flag_printf->g_case++;
    } else {
      while (g_mantissa >= 10) {
        g_mantissa /= 10;
        flag_printf->g_case++;
        (*res)++;
      }
      if (flag_printf->precision > (*res))
        flag_printf->precision = flag_printf->precision - (*res) - 1;
      else {
        if ((*res) != flag_printf->precision) {
          flag_printf->precision--;
          if ((*mantissa >= 10)) {
            while ((*mantissa) >= 10) {
              (*mantissa) /= 10;
              flag_printf->like_e_flag = 1;
            }
          }
        } else {
          long long int mantissa_num = (long long int)(*mantissa);
          while (mantissa_num >= 10) {
            mantissa_num /= 10;
          }
          (*mantissa) = (long double)mantissa_num;
          flag_printf->precision = 0;
          flag_printf->like_e_flag = 1;
        }
      }
    }
  } else {
    long double f = (int)(*mantissa) - (*mantissa);
    if (f && flag_printf->precision) {
      while ((int)(*mantissa) == 0) {
        (*mantissa) *= 10;
        (*res)++;
      }
      long double temp = (*mantissa);
      long double temp_check =
          temp * (int)pow(10.0, (double)(flag_printf->precision + 1));
      long long int x = (long long int)temp_check;
      if (!(x % 9) && (*res)) {
        x++;
        if (flag_printf->e_flag || (flag_printf->g_flag && (*res) > 4)) {
          if (!(x % (int)pow(10.0, (double)(flag_printf->precision + 1)))) {
            (*mantissa) = roundl((*mantissa) / 10);
            (*res)--;
          }
        } else if (flag_printf->g_flag && (*res) < 4) {
          if (!(x % (int)pow(10.0, (double)(flag_printf->precision + 2)))) {
            x = x / (int)pow(10.0, (double)(flag_printf->precision + 2));
          } else {
            x /= 100;
          }
          (*mantissa) = (double)x;
        }
      } else if (!(x % 9) && !(*res)) {
        x = x % (int)pow(10.0, (double)(flag_printf->precision + 1)) + 1;
        if (!(x / (int)pow(10.0, (double)(flag_printf->precision + 1)))) {
          (*mantissa) = temp;
        } else {
          (*mantissa) = roundl((*mantissa));
        }
      } else if (flag_printf->g_flag && (*res) <= 4 && !flag_printf->g_case) {
        x /= 10;
        if (x % 10 > 4) {
          x++;
          x /= 10;
        } else {
          x /= 10;
        }
        (*mantissa) = (double)x;
      }
    }
    if (flag_printf->e_flag ||
        (flag_printf->g_flag && (*res) > 4 && copy_mantissa < 1)) {
      while ((int)(*mantissa) / 10 != 0) {
        (*mantissa) /= 10;
        (*res)++;
      }
    }
  }
}

void prepare_mantissa_with_zero_precision(long double *mantissa,
                                          long long int *round_mantissa,
                                          int *res, long double copy_mantissa,
                                          int *g_specificier,
                                          flags *flag_printf) {
  if ((*mantissa) > 0 && (*mantissa) < 1) {
    while (!(int)(*mantissa)) {
      (*mantissa) *= 10;
      (*res)++;
    }
    if ((int)(*mantissa) != 9) {
      (*round_mantissa) = roundl((*mantissa));
      (*g_specificier) = 1;
    } else {
      if (flag_printf->g_flag) {
        (*mantissa) *= 10;
        if ((int)(*mantissa) % 10 > 4 && (*res) > 1 && (*res) <= 4) {
          (*round_mantissa) = (int)(*mantissa) / 10 + 1;
          (*res)--;
        } else if ((int)(*mantissa) % 10 > 4 && (*res) == 1) {
          (*round_mantissa) = roundl(*mantissa / 10);
        } else if ((int)(*mantissa) % 10 <= 4 && (*res) <= 4) {
          (*round_mantissa) = (int)(*mantissa) / 10;
          (*g_specificier) = 1;
        } else if ((int)(*mantissa) % 10 > 4 && (*res) > 4) {
          (*round_mantissa) = roundl((*mantissa / 10));
          (*res)--;
        } else if ((int)(*mantissa) % 10 <= 4 && (*res) > 4) {
          (*round_mantissa) = (int)(*mantissa) / 10;
        }
      } else if (!((int)roundl((*mantissa)) % 10)) {
        (*round_mantissa) = roundl((*mantissa) / 10);
        (*res)--;
      } else {
        (*round_mantissa) = roundl((*mantissa));
      }
    }
  } else {
    while ((int)(*mantissa) / 10 != 0) {
      (*mantissa) /= 10;
      (*res)++;
    }
    (*round_mantissa) = roundl((*mantissa));
  }
  if (!((int)(*round_mantissa) % 10) &&
      (flag_printf->e_flag || (flag_printf->g_flag && copy_mantissa >= 1))) {
    (*round_mantissa) = roundl((*mantissa / 10));
    (*res)++;
  }
}

char *g_mantissa_with_zero_precision_to_char(const int *res,
                                             long long int *round_mantissa,
                                             char *exp,
                                             const int *g_specificier) {
  int j = 0;
  exp = (char *)calloc(50, sizeof(char));
  if (!(*g_specificier)) {
    if ((*res) <= 4 && (*res) > 1) {
      if (!((*round_mantissa) % 10)) {
        (*round_mantissa) /= 10;
        exp[j++] = '0';
        exp[j++] = '.';
        for (int i = 0; i < (*res) - 1; i++) {
          exp[j++] = '0';
        }
        exp[j++] = (*round_mantissa) + '0';
      }
    } else if ((*res) == 1) {
      if ((*round_mantissa) < 10)
        exp[j++] = (*round_mantissa) + '0';
      else if ((*round_mantissa) == 10) {
        (*round_mantissa) /= 10;
        exp[j++] = (*round_mantissa) + '0';
      }
    } else {
      if ((*round_mantissa) == 10) {
        (*round_mantissa) /= 10;
        exp[j++] = (*round_mantissa) + '0';
      } else {
        exp[j++] = (*round_mantissa) + '0';
      }
    }
  } else {
    if ((*res) <= 4) {
      exp[j++] = '0';
      exp[j++] = '.';
      for (int i = 0; i < (*res) - 1; i++) {
        exp[j++] = '0';
      }
      exp[j++] = (*round_mantissa) + '0';
    } else {
      exp[j++] = (*round_mantissa) + '0';
    }
  }
  return exp;
}

char *g_mantissa_to_char(char *exp, const int *res, flags *flag_printf,
                         long double mantissa, long double copy_mantissa) {
  char *g_buf = S21_NULL;
  int base = 10;
  exp = (char *)calloc(50, sizeof(char));
  if (copy_mantissa > 0 && copy_mantissa < 1) {
    long long int g = (long long int)mantissa;
    if (flag_printf->g_flag == 1 && !flag_printf->g_case) {
      if (!flag_printf->hashtag) {
        while (!(g % 10)) {
          g /= 10;
        }
      }
      int j = 0;
      char *g_number = int_to_char(&g, g_buf, &base);
      exp[j++] = '0';
      exp[j++] = '.';
      for (int i = 0; i < (*res) - 1; i++) {
        exp[j++] = '0';
      }
      for (int i = 0; i < (int)s21_strlen(g_number); i++) {
        exp[j++] = g_number[i];
      }
      free(g_number);
    }
  }
  free(g_buf);
  return exp;
}

void final_mantissa_number(char *str, int *j, flags *flag_printf, const char *c,
                           const char *e_sign, const int *res,
                           long double copy_mantissa, int g_specificier) {
  if (flag_printf->e_flag ||
      (flag_printf->g_flag && (*res) > 0 && copy_mantissa >= 10 &&
       !flag_printf->precision && !g_specificier && !flag_printf->g_case) ||
      (flag_printf->g_flag && (*res) > 4 && !flag_printf->g_case) ||
      flag_printf->like_e_flag) {
    str[(*j)++] = ((*c) == 'e' || (*c) == 'g') ? 'e' : 'E';
    str[(*j)++] = (*e_sign);
    str[(*j)++] = (*res) < 10 ? (*res) % 10 / 10 + '0' : (*res) / 10 + '0';
    str[(*j)++] =
        (flag_printf->e_flag && copy_mantissa == 0) ? '0' : (*res) % 10 + '0';
  }
}

void flags_before_sign_for_mantissa(char *str, int *j, flags *flag_printf,
                                    const int *width_of_mantissa, int res,
                                    long double copy_mantissa,
                                    int g_specificier) {
  if (flag_printf->space && !flag_printf->width) {
    str[(*j)++] = ' ';
  } else if (flag_printf->space && flag_printf->width && !flag_printf->zero) {
    if ((*width_of_mantissa) - 4 <= flag_printf->space) {
      str[(*j)++] = ' ';
    } else if (!flag_printf->minus) {
      for (int w = 0; w < (*width_of_mantissa) - 4; w++) {
        str[(*j)++] = ' ';
      }
    } else {
      str[(*j)++] = ' ';
    }
  } else if (!flag_printf->space && flag_printf->width && !flag_printf->minus &&
             !flag_printf->zero) {
    if (flag_printf->e_flag ||
        (flag_printf->g_flag && res > 0 && copy_mantissa >= 10 &&
         !flag_printf->precision && !g_specificier && !flag_printf->g_case) ||
        (flag_printf->g_flag && res > 4 && !flag_printf->g_case) ||
        flag_printf->like_e_flag) {
      for (int w = 0; w < (*width_of_mantissa) - 4; w++) {
        str[(*j)++] = ' ';
      }
    } else {
      for (int w = 0; w < (*width_of_mantissa); w++) {
        str[(*j)++] = ' ';
      }
    }
  }
}

void flags_after_sign_for_mantissa(char *str, int *j, flags *flag_printf,
                                   const int *width_of_mantissa,
                                   const int *get_sign, int res,
                                   long double copy_mantissa,
                                   int g_specificier) {
  if (flag_printf->width && (*width_of_mantissa) > 0 && !flag_printf->minus &&
      flag_printf->zero) {
    if (flag_printf->e_flag ||
        (flag_printf->g_flag && res > 0 && copy_mantissa >= 10 &&
         !flag_printf->precision && !g_specificier && !flag_printf->g_case) ||
        (flag_printf->g_flag && res > 4 && !flag_printf->g_case) ||
        flag_printf->like_e_flag) {
      if (!flag_printf->space || (*get_sign)) {
        for (int i = 0; i < (*width_of_mantissa) - 4; i++) str[(*j)++] = '0';
      } else if (flag_printf->space && !(*get_sign)) {
        str[(*j)++] = ' ';
        for (int i = 0; i < (*width_of_mantissa) - 5; i++) str[(*j)++] = '0';
      }
    } else {
      if (!flag_printf->space || (*get_sign)) {
        for (int i = 0; i < (*width_of_mantissa); i++) str[(*j)++] = '0';
      } else if (flag_printf->space && !(*get_sign)) {
        str[(*j)++] = ' ';
        for (int i = 0; i < (*width_of_mantissa) - 1; i++) str[(*j)++] = '0';
      }
    }
  }
}
