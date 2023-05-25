#include "s21_string.h"

//Выполняет поиск первого вхождения символа d (беззнаковый тип) в строке, на
//которую указывает аргумент str. Возвращает указатель на позицию в строке
// не рассматривает последний \0 символ

char *s21_strchr(const char *str, int d) {
  char *chr = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t i = 0;
    while (str[i] && str[i] != d) {
      i++;
    }
    if (d == str[i]) {
      chr = (char *)str + i;
    }
  }
  return chr;
}
