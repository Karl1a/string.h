#include "s21_string.h"

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  _Bool is_find = 0;
  char *result = S21_NULL;
  s21_size_t needle_len = s21_strlen(needle);
  if (haystack != S21_NULL && needle != S21_NULL && needle_len) {
    while (*haystack && *needle && !is_find) {
      if (*haystack == *needle && !s21_strncmp(haystack, needle, needle_len)) {
        result = (char *)haystack;
        is_find = 1;
      }
      haystack++;
    }
    if (!is_find) {
      is_find = 1;
    }
  }
  if (result == S21_NULL) {
    if (!is_find) {
      result = (char *)haystack;  // если длина второго - 0
    }
  }
  return result;
}