#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  if (src != S21_NULL) {
    if (trim_chars == S21_NULL || trim_chars[0] == '\0') {
      trim_chars = " ";
    }
    int size = (int)s21_strlen(src);
    if (size != 0) {
      int start = -1, end = -1;
      int flag_i = 1, flag_j = 1;
      for (int i = 0, j = size - 1; i < size; i++, j--) {
        if (s21_strchr(trim_chars, src[i]) == S21_NULL && flag_i) {
          start = i;
          flag_i = 0;
        }
        if (s21_strchr(trim_chars, src[j]) == S21_NULL && flag_j) {
          end = j;
          flag_j = 0;
        }
        if (!flag_i && !flag_j) {
          break;
        }
      }
      result = calloc(end - start + 2, sizeof(char));
      if (result != S21_NULL) {
        for (int i = start, j = 0; i <= end; i++, j++) {
          result[j] = src[i];
        }
      }
    } else {
      result = calloc(2, sizeof(char));
      result[0] = '\0';
    }
  }
  return result;
}