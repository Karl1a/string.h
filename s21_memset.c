#include "s21_string.h"
//Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
//указывает аргумент str. Возвращает указатель на изм строку
void *s21_memset(void *str, int d, s21_size_t n) {
  if (str == S21_NULL) return S21_NULL;
  s21_size_t i = 0;
  while (i < n) {
    *((char *)str + i) = d;
    i++;
  }
  return str;
}