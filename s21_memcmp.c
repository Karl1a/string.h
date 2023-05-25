#include "s21_string.h"
//Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  s21_size_t i = 0;
  const unsigned char *temp_str1 = (const unsigned char *)str1;
  const unsigned char *temp_str2 = (const unsigned char *)str2;

  int result = 0;
  while (i < n) {
    if (*(temp_str1 + i) != *(temp_str2 + i)) {
      result = *(temp_str1 + i) - *(temp_str2 + i);
      break;
    }
    i++;
  }

  return result;
}
