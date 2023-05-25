#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (src != S21_NULL) {
    s21_size_t size_str = s21_strlen(str);
    s21_size_t size_src = s21_strlen(src);
    s21_size_t size_result = size_src + size_str + 1;
    if (start_index < size_src) {
      result = calloc(size_result, sizeof(char));
      if (result != S21_NULL) {
        for (s21_size_t i = 0, j = 0; j < size_result; j++, i++) {
          if (j == start_index) {
            s21_strcpy(result + j, str);
            j = size_str + j - 1;
            i--;
          } else {
            result[j] = src[i];
          }
        }
      }
    }
    if (!size_str && !size_src) {
      result = calloc(1, sizeof(char));
    }
  }
  return result;
}