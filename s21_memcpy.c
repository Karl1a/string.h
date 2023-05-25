#include "s21_string.h"
//Копирует n символов из src в dest. Возвращает указатель на измененную строку
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n) {
    *((char *)dest + i) = *((char *)src + i);
    i++;
  }

  return dest;
}
