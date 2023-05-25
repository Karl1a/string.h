#include "s21_string.h"

//Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
//байтах строки, на которую указывает аргумент str. выводит УКАЗАТЕЛЬ на первое
//вхождение
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *temp = (const char *)str;
  void *result = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t i = 0;
    while (i < n) {
      if (*(unsigned char *)(temp + i) == (unsigned char)c) {
        result = (void *)(temp + i);
        break;
      }
      i++;
    }
  }
  return result;
}