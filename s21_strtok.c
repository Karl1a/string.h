#include "s21_string.h"

// разбивает строку str на ряд токенов, разделенных delim
char *s21_strtok(char *str, const char *delim) {
  static char *lasts = S21_NULL;  // static означает, что переменная будет
  // уничтожена при завершении программы
  if (!str) {
    str = lasts;
  }
  if (*str != '\0') {
    s21_size_t len_word = s21_strcspn(str, delim);
    while (len_word == 0 &&
           *(str + 1) !=
               '\0') {  // на случай нескольких делиметров в str подряд
      str++;
      len_word = s21_strcspn(str, delim);
    }
    if (!len_word) {  //если последний знак в str - из делиметров
      str = S21_NULL;
    } else {
      lasts = str + len_word;
      if (*lasts) {
        *(lasts++) = '\0';
      }
    }
  } else {
    str = S21_NULL;
  }
  return str;
}
