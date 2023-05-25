#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  char *temp = malloc((s21_strlen(str) + 2) * sizeof(char));
  sscanf_flags flag = {0};
  va_list ap;
  va_start(ap, format);
  if (temp) {
    if (str[0] == '\0')
      flag.zero = 1;
    else {
      while (flag.format_count < (int)s21_strlen(format)) {
        char ch = format[flag.format_count];
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\x0B' ||
            ch == '\t') {
          flag.probel++;
          skeep_space(str, &flag);
          flag.format_count++;
        }
        if (ch == '%') { /* если текущий символ процент, то после него могут
           быть только % / * / RESULT_VALGRIND.txt / l / srec-rs / aboba */
          flag.procent++;
          flag.format_count++;  //сдвигаемся на следующий символ
          check_spec_symbol(str, format, &flag);
          check_width(format, &flag);         // поиск ширины
          check_modificators(format, &flag);  // поиск модификаторов
          pars_specificators(str, temp, format, ap, &flag);
        }
        if (ch != ' ' && ch != '%') {
          flag.format_string++;  // ???
          get_format_pattern(str, format, &flag);
        }
        flag.astra = 0;  // может переместить??
      }
    }
  }
  if (flag.eof || flag.zero) flag.result = -1;
  va_end(ap);
  free(temp);
  return flag.result;
}

void skeep_space(const char *str, sscanf_flags *flag) {
  int i = 0, j = 0;
  if (flag->str_count > 0) i = flag->str_count;
  while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' ||
         str[i] == '\x0B' || str[i] == '\f') {
    i++;
    j++;  // количество итераций
    flag->str_probel++;
  }
  if (flag->str_probel == (int)s21_strlen(str)) flag->eof = 1;
  flag->str_count += j;  // добавляем пробелы к счетчику
}

void get_format_pattern(const char *str, const char *format,
                        sscanf_flags *flag) {
  if (!flag->error) {
    if (format[flag->format_count] == str[flag->str_count]) {
      flag->str_count++;
      flag->format_count++;
    } else {
      flag->error++;
    }
  } else
    flag->format_count++;
}

void check_spec_symbol(const char *str, const char *format,
                       sscanf_flags *flag) {
  if (format[flag->format_count] == '%') {
    flag->procent++;
    get_symbol(str, format,
               flag);  //просто проверяем в симв строке на соответ и
    flag->format_count++;  // сдвигаемся дальше в форм строке
    flag->procent = 0;
  }
  if (format[flag->format_count] == '*') {  //если знак подавления,
    flag->astra++;
    flag->format_count++;
  }
}

/* сделать чтобы выходила сумма (может быть двузначное число) */
void check_width(const char *format, sscanf_flags *flag) {
  for (; isdigit(format[flag->format_count]); flag->format_count++)
    flag->width = (flag->width * 10) + (format[flag->format_count] - 48);
}

void check_modificators(const char *format, sscanf_flags *flag) {
  switch (format[flag->format_count]) {
    case 'l':
      flag->length_l = 1;
      flag->format_count++;
      break;
    case 'h':
      flag->length_h = 1;
      flag->format_count++;
      break;
    case 'L':
      flag->length_L = 1;
      flag->format_count++;
      break;
  }
}

void pars_specificators(const char *str, char *temp, const char *format,
                        va_list ap, sscanf_flags *flag) {
  int pars_count = 0;
  char c = format[flag->format_count];
  switch (c) {
    case 'u':
      get_pattern_int(temp, str, flag);
      spec_u(temp, ap, flag);
      pars_count++;
      break;
    case 'd':
      get_pattern_int(temp, str, flag);
      spec_d(temp, ap, flag);
      pars_count++;
      break;
    case 'i':
      get_pattern_x(format, temp, str, flag);
      spec_i(temp, ap, flag);
      pars_count++;
      break;
    case 'c':
      flag->lonely_char++;
      get_symbol(str, format, flag);
      spec_c(ap, flag);
      pars_count++;
      break;
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'f':
      get_pattern_f(temp, str, flag);
      spec_f(temp, ap, flag);
      pars_count++;
      break;
    case 's':
      flag->string_func++;
      get_pattern(temp, str, flag);
      spec_s(temp, ap, flag);
      pars_count++;
      break;
    case 'n':
      flag->n++;
      get_pattern(temp, str, flag);
      spec_n(ap, flag);
      pars_count++;
      break;
    case 'o':
      get_pattern_int(temp, str, flag);
      spec_o(temp, ap, flag);
      pars_count++;
      break;
    case 'X':
    case 'x':
      get_pattern_x(format, temp, str, flag);
      spec_x(temp, ap, flag);
      pars_count++;
      break;
    case 'p':
      get_pattern_x(format, temp, str, flag);
      spec_p(temp, ap, flag);
      pars_count++;
      break;
    default:  // !!!!! проверить в ориг вариант %*dAboba
      break;
  }
  flag->length_L = 0;
  flag->length_l = 0;
  flag->length_h = 0;
  flag->astra = 0;
  flag->width = 0;
  flag->procent = 0;
  flag->astra = 0;
  flag->n = 0;
  flag->format_count += pars_count;
}

void get_symbol(const char *str, const char *format, sscanf_flags *flag) {
  if (flag->lonely_char) {
    if (flag->astra == 0) {
      if (flag->probel) skeep_space(str, flag);
      flag->ch = str[flag->str_count];
    }
    flag->str_count++;
    flag->probel = 0;
  }
  if (flag->probel) skeep_space(str, flag);
  if (flag->procent > 1 && format[flag->format_count] == '%' &&
      str[flag->str_count] == '%') {
    flag->str_count++;
  }
}

char *get_pattern_int(char *temp, const char *str, sscanf_flags *flag) {
  int i = 0;
  skeep_space(str, flag);
  if (flag->n == 0) {
    if (flag->astra == 0) {  // если нет флага подавления
      /* пробегаем паттерн */
      if (flag->width > 0) {  // если есть ширина
        int j = 0;
        j = flag->str_count;  // стартовая точка при наличии ширины
        while (j < (flag->str_count + flag->width) &&
               s21_strchr("0123456789-+", str[j])) {
          temp[i] = str[j];
          j++;
          i++;
        }
      } else {  // если нет ширины
        while (str[flag->str_count + i] != ' ' &&
               str[flag->str_count + i] != '\0' &&
               str[flag->str_count + i] != '\n' &&
               str[flag->str_count + i] != '\r' &&
               str[flag->str_count + i] != '\x0B' &&
               str[flag->str_count + i] != '\t' &&
               s21_strchr("0123456789-+", str[flag->str_count + i])) {
          temp[i] = str[flag->str_count + i];
          i++;
        }
      }
      temp[i] = '\0';
    } else {  // если есть знак подавления просто пробегаемся дальше
      while (str[flag->str_count + i] != ' ' &&
             str[flag->str_count + i] != '\0' &&
             str[flag->str_count + i] != '\n' &&
             str[flag->str_count + i] != '\r' &&
             str[flag->str_count + i] != '\x0B' &&
             str[flag->str_count + i] != '\t') {  // добавить условия типа , % :
        i++;
      }
    }
  }
  flag->probel = 0;
  flag->str_count += i;
  return temp;
}

char *get_pattern_x(const char *format, char *temp, const char *str,
                    sscanf_flags *flag) {
  int i = 0;
  if (flag->n == 0) {
    skeep_space(str, flag);
    if (flag->astra == 0) {  // если нет флага подавления
      /* пробегаем паттерн */
      if (flag->width > 0 &&
          flag->width < (int)s21_strlen(format)) {  // если есть ширина
        int width_start =
            flag->str_count;  // стартовая точка при наличии ширины
        while (width_start < (flag->str_count + flag->width)) {
          if (s21_strchr("0123456789-+xABCDEFabcdef", str[flag->str_count + i]))
            temp[i] = str[width_start];
          width_start++;
          i++;
        }
      } else {  // если нет ширины
        while (
            str[flag->str_count + i] != ' ' &&
            str[flag->str_count + i] != '\0' &&
            str[flag->str_count + i] != '\n' &&
            str[flag->str_count + i] != '\r' &&
            str[flag->str_count + i] != '\x0B' &&
            str[flag->str_count + i] != '\t' &&
            s21_strchr("0123456789-+xABCDEFabcdef", str[flag->str_count + i])) {
          temp[i] = str[flag->str_count + i];
          i++;
        }
      }
      temp[i] = '\0';
    } else {  // если есть знак подавления просто пробегаемся дальше
      while (str[flag->str_count + i] != ' ' &&
             str[flag->str_count + i] != '\0' &&
             str[flag->str_count + i] != '\n' &&
             str[flag->str_count + i] != '\r' &&
             str[flag->str_count + i] != '\x0B' &&
             str[flag->str_count + i] != '\t') {  // добавить условия типа , % :
        i++;
      }
    }
  }
  flag->probel = 0;
  flag->str_count += i;
  return temp;
}

char *get_pattern_f(char *temp, const char *str, sscanf_flags *flag) {
  int i = 0;
  skeep_space(str, flag);
  if (flag->n == 0) {
    if (flag->astra == 0) {  // если нет флага подавления
      /* пробегаем паттерн */
      if (flag->width > 0) {  // если есть ширина
        int j = flag->str_count;  // стартовая точка при наличии ширины
        while (j < (flag->str_count + flag->width) &&
               s21_strchr("0123456789-+e.", str[j])) {
          temp[i] = str[j];
          j++;
          i++;
        }
      } else {  // если нет ширины
        while (
            str[flag->str_count + i] != ' ' &&
            str[flag->str_count + i] != '\0' &&
            str[flag->str_count + i] != '\n' &&
            str[flag->str_count + i] != '\r' &&
            str[flag->str_count + i] != '\x0B' &&
            str[flag->str_count + i] != '\t' &&
            s21_strchr("0123456789-+e.iInNfFnNaA", str[flag->str_count + i])) {
          temp[i] = str[flag->str_count + i];
          i++;
        }
      }
      temp[i] = '\0';
    } else {  // если есть знак подавления просто пробегаемся дальше
      while (str[flag->str_count + i] != ' ' &&
             str[flag->str_count + i] != '\0' &&
             str[flag->str_count + i] != '\n' &&
             str[flag->str_count + i] != '\r' &&
             str[flag->str_count + i] != '\x0B' &&
             str[flag->str_count + i] != '\t') {  // добавить условия типа , % :
        i++;
      }
    }
  }
  flag->probel = 0;
  flag->str_count += i;
  return temp;
}

char *get_pattern(char *temp, const char *str, sscanf_flags *flag) {
  int i = 0;
  skeep_space(str, flag);
  if (flag->n == 0) {
    if (flag->astra == 0) {  // если нет флага подавления
      /* пробегаем паттерн */
      if (flag->width > 0) {  // если есть ширина
        int j = flag->str_count;  // стартовая точка при наличии ширины
        while ((str[j] != ' ' && str[j] != '\0' && str[j] != '\n' &&
                str[j] != '\r' && str[j] != '\x0B' && str[j] != '\t') &&
               j < (flag->str_count + flag->width)) {
          temp[i] = str[j];
          j++;
          i++;
        }
      } else {  // если нет ширины

        while (str[flag->str_count + i] != ' ' &&
               str[flag->str_count + i] != '\0' &&
               str[flag->str_count + i] != '\n' &&
               str[flag->str_count + i] != '\r' &&
               str[flag->str_count + i] != '\x0B' &&
               str[flag->str_count + i] != '\t') {
          temp[i] = str[flag->str_count + i];
          i++;
        }
      }
      temp[i] = '\0';
    } else {  // если есть знак подавления просто пробегаемся дальше
      while (str[flag->str_count + i] != ' ' &&
             str[flag->str_count + i] != '\0' &&
             str[flag->str_count + i] != '\n' &&
             str[flag->str_count + i] != '\r' &&
             str[flag->str_count + i] != '\x0B' &&
             str[flag->str_count + i] != '\t') {  // добавить условия типа , % :
        i++;
      }
    }
  }
  flag->probel = 0;
  flag->str_count += i;
  return temp;
}

void spec_u(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error) {
    if (flag->length_l == 1) {
      *(long unsigned *)va_arg(ap, void *) = char_to_int(temp, flag);
    } else if (flag->length_h == 1) {
      *(short unsigned *)va_arg(ap, void *) = char_to_int(temp, flag);
    } else {
      *(unsigned *)va_arg(ap, void *) = char_to_int(temp, flag);
    }
  }
}

void spec_d(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error) {
    if (flag->length_l == 1) {
      *(long int *)va_arg(ap, void *) = char_to_int(temp, flag);
    } else if (flag->length_h == 1) {
      *(short int *)va_arg(ap, void *) = char_to_int(temp, flag);
    } else {
      *(int *)va_arg(ap, void *) = char_to_int(temp, flag);
    }
  }
}

void spec_i(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error) {
    int flag_8 = 0, flag_16 = 0;
    if (temp[0] == '0') {
      if (temp[1] == 'x' || temp[1] == 'X') {
        if (flag->length_l == 1) {
          *(long unsigned *)va_arg(ap, void *) = char_to_hex(temp, flag);
        } else if (flag->length_h == 1) {
          *(short unsigned *)va_arg(ap, void *) = char_to_hex(temp, flag);
        } else {
          *(unsigned *)va_arg(ap, void *) = char_to_hex(temp, flag);
        }
        flag_16 = 1;
      } else {
        if (flag->length_l == 1) {
          *(long unsigned *)va_arg(ap, void *) = char_to_oct(temp, flag);
        } else if (flag->length_h == 1) {
          *(short unsigned *)va_arg(ap, void *) = char_to_oct(temp, flag);
        } else {
          *(unsigned *)va_arg(ap, void *) = char_to_oct(temp, flag);
        }
        flag_8 = 1;
      }
    }
    if (!flag_16 && !flag_8) {
      if (flag->length_l == 1) {
        *(long int *)va_arg(ap, void *) = char_to_int(temp, flag);
      } else if (flag->length_h == 1) {
        *(short int *)va_arg(ap, void *) = char_to_int(temp, flag);
      } else {
        *(int *)va_arg(ap, void *) = char_to_int(temp, flag);
      }
    }
  }
}

void spec_c(va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error) {
    char *char_c = va_arg(ap, char *);
    *char_c = flag->ch;  //взятый с get_symbol
    flag->result++;
  }
}

void spec_f(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error) {
    if (flag->length_L == 1)
      *(long double *)va_arg(ap, void *) = char_to_long_double(temp, flag);
    else if (flag->length_l == 1)
      *(double *)va_arg(ap, void *) = char_to_double(temp, flag);
    else
      *(float *)va_arg(ap, float *) = char_to_float(temp, flag);
  }
}

void spec_s(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra) {
    char *ch = va_arg(ap, char *);
    int h = (int)s21_strlen(temp);
    for (int i = 0; i < h; i++) {
      ch[i] = temp[i];
    }
    flag->result++;
  }
}

void spec_n(va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error)
    *(int *)va_arg(ap, void *) = flag->str_count;
}

void spec_o(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra) {
    if (flag->length_l == 1) {
      *(long unsigned *)va_arg(ap, void *) = char_to_oct(temp, flag);
    } else if (flag->length_h == 1) {
      *(short unsigned *)va_arg(ap, void *) = char_to_oct(temp, flag);
    } else {
      *(unsigned *)va_arg(ap, void *) = char_to_oct(temp, flag);
    }
  }
}

void spec_x(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error) {
    if (flag->length_l == 1) {
      *(long unsigned *)va_arg(ap, void *) = char_to_hex(temp, flag);
    } else if (flag->length_h == 1) {
      *(short unsigned *)va_arg(ap, void *) = char_to_hex(temp, flag);
    } else {
      *(unsigned *)va_arg(ap, void *) = char_to_hex(temp, flag);
    }
  }
}

void spec_p(char *temp, va_list ap, sscanf_flags *flag) {
  if (!flag->astra && !flag->error) {
    long decimal = char_to_hex(temp, flag);
    void **p = va_arg(ap, void **);
    *p = (void *)(0x0 + decimal);
  }
}

int char_to_hex(char *temp, sscanf_flags *flag) {
  int i = 0, res = 0, digit, flag_m = 0, plus = 0, flag_hz = 0;
  int j = s21_strlen(temp);
  if (flag->width) j = flag->width;
  if ((temp[i] == '-' || temp[i] == '+') &&
      (flag->width == 1 || (temp[i + 1] == '+' || temp[i + 1] == '-')))
    flag->error++;
  if (temp[i] == '-') {
    i = 1;
    flag_m = 1;
  }
  if ((temp[0] == '0' && (temp[1] == 'x' || temp[1] == 'X'))) {
    plus = 2;
  }
  while (((temp[i + plus] >= 48 && temp[i + plus] <= 57) ||
          (temp[i + plus] >= 65 && temp[i + plus] <= 70) ||
          (temp[i + plus] >= 97 && temp[i + plus] <= 102)) &&
         i + plus < j) {
    if (temp[i + plus] >= 65 && temp[i + plus] <= 70) {
      digit = temp[i + plus] - 0x37;
    } else if (temp[i + plus] >= 97 && temp[i + plus] <= 102) {
      digit = temp[i + plus] - 0x57;
    } else {
      digit = temp[i + plus] - 0x30;
    }
    res = res * 16 + digit;
    i++;
  }
  if (flag_m) res *= -1;

  if (temp[0] == 48) {
    flag->result++;
    flag_hz++;
  }
  if (res && !flag_hz) flag->result++;

  return res;
}

int char_to_int(char *temp, sscanf_flags *flag) {
  int i = 0;
  int res = 0, flag_m = 0, yes = 0;
  int j = s21_strlen(temp);
  if ((temp[i] == '-' || temp[i] == '+') &&
      (flag->width == 1 || (temp[i + 1] == '+' || temp[i + 1] == '-')))
    flag->error++;
  if (temp[i] == '-') {
    i = 1;
    flag_m = 1;
  } else if (temp[i] == '+')
    i = 1;
  if (flag->width) j = flag->width;
  while (temp[i] >= 48 && temp[i] <= 57 && i < j) {
    long digit = temp[i] - 0x30;
    res = res * 10 + digit;
    i++;
    if (temp[0] != 0 && temp[1] != 'x') yes = 1;
  }
  if (yes) flag->result++;
  if (flag_m) res *= -1;
  return res;
}

int char_to_oct(char *temp, sscanf_flags *flag) {
  int i = 0, flag_m = 0, res = 0;
  int j = s21_strlen(temp);
  if (flag->width) {
    j = flag->width;
  }
  if ((temp[i] == '-' || temp[i] == '+') &&
      (flag->width == 1 || (temp[i + 1] == '+' || temp[i + 1] == '-')))
    flag->error++;
  if (temp[i] == '-') {
    i = 1;
    flag_m = 1;
  }
  while (temp[i] >= 48 && temp[i] <= 55 && i < j) {
    int digit = temp[i] - 0x30;
    res = res * 8 + digit;
    i++;
  }
  if (temp[0] == 48) flag->result++;
  if (flag_m || flag->minus) res *= -1;
  if (res && temp[0] != 48) flag->result++;
  return res;
}

long double char_to_long_double(char *temp, sscanf_flags *flag) {
  long double a, decplace, b;
  int sign = 1;

  if (*temp == '+') ++temp;
  if (*temp == '-') {
    sign = -1;
    ++temp;
  }
  for (a = 0; *temp && isdigit(*temp); ++temp) a = a * 10 + (*temp - '0');
  if (*temp == '.') ++temp;
  for (decplace = 1.; *temp && isdigit(*temp); ++temp, decplace *= 10.)
    a = a * 10. + (*temp - '0');
  if (*temp == 'e' || *temp == 'E') {
    int bsign = 1;
    if (a <= 1e-6) a = 1;
    ++temp;
    if (*temp == '-') {
      bsign = -1;
      ++temp;
    }
    if (*temp == '+') ++temp;
    for (b = 0; *temp && isdigit(*temp); ++temp) b = b * 10 + (*temp - '0');
    b *= bsign;
  } else {
    b = 0;
  }
  if ((*temp == 'n' || *temp == 'N') && (temp[1] == 'a' || temp[1] == 'A') &&
      (temp[2] == 'n' || temp[2] == 'N')) {
    temp += 3;
    a = NAN * sign;
  }
  if ((*temp == 'i' || *temp == 'I') && (temp[1] == 'n' || temp[1] == 'N') &&
      (temp[2] == 'f' || temp[2] == 'F')) {
    a = INFINITY * sign;
  }
  flag->result++;
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

double char_to_double(char *temp, sscanf_flags *flag) {
  long double a, decplace, b;
  int sign = 1;

  if (*temp == '+') ++temp;
  if (*temp == '-') {
    sign = -1;
    ++temp;
  }
  for (a = 0; *temp && isdigit(*temp); ++temp) a = a * 10 + (*temp - '0');
  if (*temp == '.') ++temp;
  for (decplace = 1.; *temp && isdigit(*temp); ++temp, decplace *= 10.)
    a = a * 10. + (*temp - '0');
  if (*temp == 'e' || *temp == 'E') {
    int bsign = 1;
    if (a <= 1e-6) a = 1;
    ++temp;
    if (*temp == '-') {
      bsign = -1;
      ++temp;
    }
    if (*temp == '+') ++temp;
    for (b = 0; *temp && isdigit(*temp); ++temp) b = b * 10 + (*temp - '0');
    b *= bsign;
  } else {
    b = 0;
  }
  if ((*temp == 'n' || *temp == 'N') && (temp[1] == 'a' || temp[1] == 'A') &&
      (temp[2] == 'n' || temp[2] == 'N')) {
    temp += 3;
    a = NAN * sign;
  }
  if ((*temp == 'i' || *temp == 'I') && (temp[1] == 'n' || temp[1] == 'N') &&
      (temp[2] == 'f' || temp[2] == 'F')) {
    a = INFINITY * sign;
  }
  flag->result++;
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

float char_to_float(char *temp, sscanf_flags *flag) {
  long double a, decplace, b;
  int sign = 1;

  if (*temp == '+') ++temp;
  if (*temp == '-') {
    sign = -1;
    ++temp;
  }
  for (a = 0; *temp && isdigit(*temp); ++temp) a = a * 10 + (*temp - '0');
  if (*temp == '.') ++temp;
  for (decplace = 1.; *temp && isdigit(*temp); ++temp, decplace *= 10.)
    a = a * 10. + (*temp - '0');
  if (*temp == 'e' || *temp == 'E') {
    int bsign = 1;
    if (a <= 1e-6) a = 1;
    ++temp;
    if (*temp == '-') {
      bsign = -1;
      ++temp;
    }
    if (*temp == '+') ++temp;
    for (b = 0; *temp && isdigit(*temp); ++temp) b = b * 10 + (*temp - '0');
    b *= bsign;
  } else {
    b = 0;
  }
  if ((*temp == 'n' || *temp == 'N') && (temp[1] == 'a' || temp[1] == 'A') &&
      (temp[2] == 'n' || temp[2] == 'N')) {
    temp += 3;
    a = NAN * sign;
  }
  if ((*temp == 'i' || *temp == 'I') && (temp[1] == 'n' || temp[1] == 'N') &&
      (temp[2] == 'f' || temp[2] == 'F')) {
    a = INFINITY * sign;
  }
  flag->result++;
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}
