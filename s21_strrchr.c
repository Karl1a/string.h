#include "s21_string.h"

// выполняет поиск последнего вхождения символа d (беззнаковый тип) в строке, на
// которую указывает аргумент str
// может рассматривать последний \0 символ

char *s21_strrchr(const char *str, int d) {
  s21_size_t len = s21_strlen(str) + 1;
  char *chr = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t last_meeting = -1;
    s21_size_t i = 0;
    while (i < len) {
      if (str[i] == d) {
        last_meeting = i;
      }
      i++;
    }
    if (last_meeting != (s21_size_t)-1) {
      chr = (char *)str + last_meeting;
    }
  }
  return chr;
}