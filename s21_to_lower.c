#include "s21_string.h"

// Возвращает копию строки (str), преобразованной в нижний регистр.
// В случае какой-либо ошибки следует вернуть значение NULL

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str != S21_NULL) {
    result = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    s21_strcpy(result, str);
    for (int i = 0; result[i] != '\0'; i++) {
      if (result[i] >= 65 && result[i] <= 90) {
        result[i] = result[i] + 32;
      }
    }
    result[s21_strlen(str)] = '\0';
  }
  return result;
}