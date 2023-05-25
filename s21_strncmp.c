#include "s21_string.h"

// сравнивает не более первых n байтов str1 и str2
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  int diff = 0;
  s21_size_t step = 0;
  while (*s1 && *s2 && *s1 == *s2 && step < n) {
    s1++;
    s2++;
    step++;
  }
  if (step == n)
    ;
  else if ((*s1 - *s2) > 0)
    diff = 1;
  else if ((*s1 - *s2) < 0)
    diff = -1;
  return diff;
}
