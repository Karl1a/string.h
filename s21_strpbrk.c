#include "s21_string.h"

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2
char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    _Bool is_find = 0;
    while (*str1 && !is_find) {
      result = s21_strchr(str2, *str1);
      if (result != S21_NULL) {
        is_find = 1;
        result = (char *)str1;
      } else {
        str1++;
      }
    }
  }
  return result;
}