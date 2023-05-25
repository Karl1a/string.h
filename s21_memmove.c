#include "s21_string.h"
////Копирует n символов из src в dest. Возвращает указатель на измененную
///строку, но безопасно(???)
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *temp_dest = (char *)dest;
  char *temp_src = (char *)src;
  char *tmp = (char *)malloc(sizeof(char) * n);

  if (dest != S21_NULL && src != S21_NULL && tmp != S21_NULL) {
    s21_size_t i;
    i = n;
    while (i--) {
      *(temp_dest + i) = *(temp_src + i);
    }
    free(tmp);
  }

  return temp_dest;
}
