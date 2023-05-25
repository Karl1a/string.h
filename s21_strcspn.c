#include "s21_string.h"

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2. Возвращает инт значение
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    char *start_ptr = s21_strpbrk(
        str1, str2);  // то есть str1 НЕ должен НАЧИНАТЬСЯ с элементов str2
    if (start_ptr == S21_NULL) {  // если в str1 нет ни одного элемента из str2,
                                  // возвращается длина str1
      len = s21_strlen(str1);
    } else if (start_ptr != str1) {
      len = start_ptr - str1;
    }
  }
  return len;
}