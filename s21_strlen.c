#include "s21_string.h"

// Вычисляет длину строки str, не включая завершающий нулевой символ
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str != S21_NULL) {
    while (*str != '\0') {
      str++;
      len++;
    }
  }
  return len;
}
