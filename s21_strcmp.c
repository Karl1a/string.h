#include "s21_string.h"

//Сравнивает строку, на которую указывает str1, со строкой, на которую указывает
// str2. Возвращает инт значение 0, RESULT_VALGRIND.txt, -RESULT_VALGRIND.txt
// (как флаг)
int s21_strcmp(const char *str1, const char *str2) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  int diff = 0;
  while (*s1 && *s2 && *s1 == *s2) {
    s1++;
    s2++;
  }
  if ((*s1 - *s2) > 0) diff = 1;
  if ((*s1 - *s2) < 0) diff = -1;
  return diff;
}
