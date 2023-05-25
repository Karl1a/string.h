#include "s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов str2.

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    char *start_ptr = s21_strpbrk(
        str1, str2);  // то есть str1 должен НАЧИНАТЬСЯ с элементов str2
    if (start_ptr == str1) {
      _Bool is_break_seq = 0;
      while (*start_ptr && !is_break_seq) {
        if (s21_strchr(str2, *start_ptr) != S21_NULL) {
          len++;
          start_ptr++;
        } else {
          is_break_seq = 1;
        }
      }
    }
  }
  return len;
}