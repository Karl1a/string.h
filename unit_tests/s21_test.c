#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"
#define BUFF_SIZE 256

START_TEST(sscanf_EOF1) {
  char fstr[] = "%d";
  char str[] = "        ";
  int16_t x;

  int16_t res1 = s21_sscanf(str, fstr, &x);
  int16_t res2 = sscanf(str, fstr, &x);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_EOF2) {
  char fstr[] = "%d";
  char str[] = "";
  int a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_EOF3) {
  char fstr[] = "%d ";
  char str[] = "  ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_EOF4) {
  char fstr[] = "%d ";
  char str[] = "\r\x0B\t";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_only_ints1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char fstr[] = "%ld %ld %ld %ld";
  const char str[] = "555 666 777 888";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_only_ints2) {
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 3000";
  const char fstr[] = "%hd %hd %hd %hd";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_only_ints4) {
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1\r 21\x0B 8\t 3000";
  const char fstr[] = "%5hd %4hd %6hd %2hd";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_ints_nwidth1) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 300004";
  const char fstr[] = "%1d %1d %1d %4d";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_ints_nwidth2) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337";
  const char fstr[] = "%1d %2d %3d %4d";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_ints_nwidth4) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337";
  const char fstr[] = "%15d %1d %1d %1d";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_signed_ints1) {
  int a1 = 0, a2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  short int b1 = 0, b2 = 0;
  const char str[] = "11337 +3 -5 -4";
  const char fstr[] = "%d %hd %d %d";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_signed_ints2) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-1337 +1 -1 -1";
  const char fstr[] = "%15d %1d %1d %5d";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_signed_ints3) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-0 +0 +0 -0";
  const char fstr[] = "%2d %1d %1d %1d";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_signed_ints4) {
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1 01 10 0";
  const char fstr[] = "%d %d %d %d";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_i_int1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "300 500 -600 +700";
  const char fstr[] = "%li %li %li %li";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_i_int2) {
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "300500 -600 +700 111";
  const char fstr[] = "%hi %hd %hd %hi";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_i_int3) {
  int a1 = 0, a2 = 0, c1 = 0, c2 = 0, b1 = 0, b2 = 0, d1 = 0, d2 = 0;
  const char str[] = "300500 -600 +700 +400";
  const char fstr[] = "%i %i %i %i";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_i_hex1) {
  long b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int a1 = 0, a2 = 0;
  const char str[] = "0xFFF 0xA123123 --0x123123 0x0";
  const char fstr[] = "%i %ld %ld %li";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_i_hex2) {
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = " 0xFFFF 0xf 0xf 0xf";
  const char fstr[] = "%hi %hi %hi %hi";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_i_oct1) {
  int a1 = 0, a2 = 0;
  short int b1 = 0, b2 = 0;
  const char str[] = "  055555  0f5555555";
  const char fstr[] = "%i %hi ";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_spec_i_oct2) {
  long a1 = 0, a2 = 0;
  const char str[] = "06875";
  const char fstr[] = "%li";

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_only_chars1) {
  char fstr[] = "%c%c%c%c";
  char str[] = "ahjf";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_only_chars2) {
  char fstr[] = "%c %c%c%c";
  char str[] = "a bcd";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_only_chars3) {
  char fstr[] = "%c %c %c      %c";
  char str[] = "1 a 3   c           ";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_only_chars4) {
  char fstr[] = "%c %c %c %c";
  char str[] = "   000 0    ";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_only_chars5) {
  char fstr[] = "%c %c %c %c";
  char str[] = "tttt";
  int16_t a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);

  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_special_symbols_as_chars1) {
  char fstr[] = "%c%c%c%c";
  char str[] = "\\\n\t\t\t";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_special_symbols_as_chars2) {
  char fstr[] = "%c %c %c %c";
  char str[] = "z ' ' /";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_special_symbols_as_chars3) {
  char fstr[] = "%c%*c%c%c";
  char str[] = "ABCD";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);

  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_chars_flags1) {
  char fstr[] = "%c %c %c %c";
  char str[] = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_chars_flags2) {
  char fstr[] = "%1c %c %c %0c";
  char str[] = "z * 5 @";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_chars_flags3) {
  char fstr[] = "%c %c %c %c";
  char str[] = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_chars_flags4) {
  char fstr[] = "%c %c %c %c";
  char str[] = "z *'@";
  int16_t a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_chars_flags5) {
  char fstr[] = "%*c%*c%*c%c";
  char str[] = "abcde";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_chars_aster1) {
  char fstr[] = "%*c%*c%*c%*c";
  char str[] = "   c ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_chars_aster2) {
  char fstr[] = "%*c%*c%*c%c";
  char str[] = "abcd ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_strings1) {
  char s1[234] = {'\0'};
  char s2[234] = {'\0'};
  char s3[234] = {'\0'};
  char s4[234] = {'\0'};

  char s5[234] = {'\0'};
  char s6[234] = {'\0'};
  char s7[234] = {'\0'};
  char s8[234] = {'\0'};

  const char str[] = "Aboba Floppa Keppa Shleppa";
  const char fstr[] = "%s %s %s %s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_strings2) {
  char s1[234] = {'\0'};
  char s2[234] = {'\0'};
  char s3[234] = {'\0'};
  char s4[234] = {'\0'};

  char s5[234] = {'\0'};
  char s6[234] = {'\0'};
  char s7[234] = {'\0'};
  char s8[234] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%s%s%s%s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_strings3) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char str[] = "aboba\tkepaboba floppa shleppa koooppa ap p p p p";
  const char fstr[] = "%*s%*s%*s%*s";

  int16_t res1 = s21_sscanf(str, fstr);
  int16_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_strings4) {
  char s1[234] = {'\0'};
  char s2[234] = {'\0'};
  char s3[234] = {'\0'};
  char s4[234] = {'\0'};

  char s5[234] = {'\0'};
  char s6[234] = {'\0'};
  char s7[234] = {'\0'};
  char s8[234] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%1s%1s%1s%1s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_strings5) {
  char s1[234] = {'\0'};
  char s2[234] = {'\0'};
  char s3[234] = {'\0'};
  char s4[234] = {'\0'};

  char s5[234] = {'\0'};
  char s6[234] = {'\0'};
  char s7[234] = {'\0'};
  char s8[234] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%3s%3s%3s%3s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_strings6) {
  char s1[234] = {'\0'};
  char s2[234] = {'\0'};
  char s3[234] = {'\0'};
  char s4[234] = {'\0'};

  char s5[234] = {'\0'};
  char s6[234] = {'\0'};
  char s7[234] = {'\0'};
  char s8[234] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%150s%1s%1s\t%3s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_strings_mixed1) {
  int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0, v1, v2;

  const char str[] = "1 1 1 1 1 -1";
  const char fstr[] = "%1s %5d %1s %1s %d %d %d";

  char s1[234] = {'\0'};
  char s2[234] = {'\0'};
  char s3[234] = {'\0'};
  char s4[234] = {'\0'};
  char s5[234] = {'\0'};
  char s6[234] = {'\0'};

  int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, s3, &b1, &v1, &d1);
  int16_t res2 = sscanf(str, fstr, s4, &a2, s5, s6, &b2, &v2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_uint1) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char str[] = "-1337 +21 --5008";
  const char fstr[] = "%hu %hu %hu ";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_strings_mixed2) {
  int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0, v1, v2;

  const char str[] = "1 1 1 1 1 -1";
  const char fstr[] = "%1s %5d %1s %1s %d %d %d";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};

  int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, s3, &b1, &v1, &d1);
  int16_t res2 = sscanf(str, fstr, s4, &a2, s5, s6, &b2, &v2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_strings_mixed3) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "Aboba 123 Floppa -3 Keppa 4444Shleppa 333Anuroba 3";
  const char fstr[] = "%s%ld%s%d%s%d%s";

  int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, &b1, s3, &c1, s4, &d1);
  int16_t res2 = s21_sscanf(str, fstr, s5, &a2, s6, &b2, s7, &c2, s8, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(sscanf_uint2) {
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                    d2 = 0;
  const char str[] = "-1337 233333331 5008 3000";
  const char fstr[] = "%1lu %2lu %5lu %4lu";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_uint4) {
  unsigned b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long a1 = 0, a2 = 0;
  const char str[] = "-1337 +21 --5008";
  const char fstr[] = "%lu %3u %u ";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_uint5) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-1337 +21 --5008 3000";
  const char fstr[] = "%hu %hu %hu %hu ";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_upeer_hex_base_version) {
  uint32_t a1, a2;
  const char str[] = "F";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_n1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int32_t n1 = 0, n2 = 5;

  const char str[] = "50 160 70";
  const char fstr[] = "%ld %ld %n";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &n1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_n2) {
  int n1 = 0, n2 = 0;

  char s1[124] = {'\0'};
  char s2[124] = {'\0'};
  char s3[124] = {'\0'};
  char s5[124] = {'\0'};
  char s6[124] = {'\0'};
  char s7[124] = {'\0'};

  const char str[] = "Clean hello! 1234";
  const char fstr[] = "%s %s %n";

  int res1 = s21_sscanf(str, fstr, s1, s2, &n1);
  int res2 = sscanf(str, fstr, s5, s6, &n2);

  ck_assert_int_eq(res1, res2);

  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
}
END_TEST

START_TEST(sscanf_n3) {
  int n1 = 0, n2 = 5;

  const char str[] = "50 60 70";
  const char fstr[] = "%n";

  int res1 = s21_sscanf(str, fstr, &n1);
  int res2 = sscanf(str, fstr, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_n4) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int32_t n1 = 0, n2 = 5;

  const char str[] = "50 60 70";
  const char fstr[] = "%ld %ld %n";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &n1);
  int res2 = sscanf(str, fstr, &a2, &b2, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_n5) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int n1 = 0, n2 = 5;

  const char str[] = "50 60 70";
  const char fstr[] = "%ld %ld %n";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &n1);
  int res2 = sscanf(str, fstr, &a2, &b2, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_lower_hex_base_version) {
  uint32_t a1, a2;
  const char str[] = "f";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_overflow) {
  uint32_t a1, a2;
  const char str[] = "0xfffffffffffffffffff";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_0x) {
  uint32_t a1, a2;
  const char str[] = "0x";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_0X) {
  uint32_t a1, a2;
  const char str[] = "0X";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_empty) {
  uint32_t a1, a2;
  const char str[] = "";
  const char fstr[] = "%x";
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_fail) {
  uint32_t a1, a2;
  const char str[] = "qF";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char str[] = "          \n             \n     F";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_short) {
  uint16_t a1, a2;
  const char str[] = "ff";
  const char fstr[] = "%hx";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_long) {
  unsigned long int a1, a2;
  const char str[] = "ff";
  const char fstr[] = "%lx";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_longlong) {
  unsigned long int a1, a2;
  const char str[] = "faaaaf";
  const char fstr[] = "%lx";
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_2x) {
  uint32_t a1, a2;
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_star) {
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%*x";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_lower) {
  uint32_t a1, a2;
  const char str[] = "abcdef";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_sign) {
  uint32_t a1, a2;
  const char str[] = "-f";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upper_hex_len) {
  uint32_t a1, a2;
  const char str[] = "123531FFF";
  const char fstr[] = "%2X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_overflow) {
  uint32_t a1, a2;
  const char str[] = "0xFFFFFFFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_0x) {
  uint32_t a1, a2;
  const char str[] = "0x";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_0X) {
  uint32_t a1, a2;
  const char str[] = "0X";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_empty) {
  uint32_t a1, a2;
  const char str[] = "";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_upeer_hex_fail) {
  uint32_t a1, a2;
  const char str[] = "qF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_upeer_hex_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char str[] = "          \n             \n     F";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_short) {
  uint16_t a1, a2;
  const char str[] = "F";
  const char fstr[] = "%hX";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_long) {
  unsigned long int a1, a2;
  const char str[] = "F";
  const char fstr[] = "%lX";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_2x) {
  uint32_t a1, a2;
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_upeer_hex_lower) {
  uint32_t a1, a2;
  const char str[] = "abcdef";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_sign) {
  uint32_t a1, a2;
  const char str[] = "-f";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_len) {
  uint32_t a1, a2;
  const char str[] = "123531FFF";
  const char fstr[] = "%2x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_base_version) {
  uint32_t a1, a2;
  const char str[] = "777";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_overflow) {
  uint32_t a1, a2;
  const char str[] = "0x7777777777777777777777";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_0x) {
  uint32_t a1, a2;
  const char str[] = "0x";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_0X) {
  uint32_t a1, a2;
  const char str[] = "0X";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_empty) {
  uint32_t a1, a2;
  const char str[] = "";
  const char fstr[] = "%o";
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_octal_fail) {
  uint32_t a1, a2;
  const char str[] = "q1";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_octal_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char str[] = "          \n             \n     5";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_short) {
  uint16_t a1, a2;
  const char str[] = "12";
  const char fstr[] = "%ho";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_long) {
  unsigned long int a1, a2;
  const char str[] = "57234";
  const char fstr[] = "%lo";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_2x) {
  uint32_t a1, a2;
  const char str[] = "0x12320x213x123213";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_star) {
  const char str[] = "521561612";
  const char fstr[] = "%*o";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_octal_lower) {
  uint32_t a1, a2;
  const char str[] = "01234567";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_sign) {
  uint32_t a1, a2;
  const char str[] = "-66";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_len) {
  uint32_t a1, a2;
  const char str[] = "123531";
  const char fstr[] = "%2o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_buff1) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12 keppa 12";
  const char fstr[] = "%d keppa %d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_buff2) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12keppa12";
  const char fstr[] = "%dkeppa%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_pointer1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_pointer2) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_pointer3) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_pointer4) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_hard1) {
  int a1 = 0, a2 = 5, a3 = 3, a4 = 9;
  int32_t n1 = 500, n2 = 10000;

  const char str[] = "123123SkipMePlease!!!!123";
  const char fstr[] = "%dSkipMePlease!!!!%d %n";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &a3, &n1);
  int16_t res2 = sscanf(str, fstr, &a2, &a4, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a3, a4);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_buff3) {
  int32_t a1, a2;
  int32_t b1 = 0, b2 = 0;
  const char str[] = "12keppa12";
  const char fstr[] = "%dkeppapos%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_perc1) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12 % 13 % 14";
  const char fstr[] = "%d %% %d %% %d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_perc2) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12%13%14";
  const char fstr[] = "%d%%%d%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_perc3) {
  int32_t a1 = 1234, a2 = 33333;

  const char str[] = "%%%16";
  const char fstr[] = "%%%%%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1);
  int32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_perc5) {
  int32_t a1 = 1234, a2 = 33333;
  int32_t b1 = 1234, b2 = 33333;

  const char str[] = "%%123%888";
  const char fstr[] = "%%%%%d%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_hard3) {
  char a1, a2;
  char b1[256] = {'\0'};
  char b2[256] = {'\0'};
  float c1, c2;
  short int d1, d2;
  long int e1, e2;

  const char str[] = "$AmIIn%%sane? %\n\n\n \n \n \n\t   InF 0 %FIN9D-ME%";
  const char fstr[] = "%c%5s%%%*s %%  %G %hi %%FIN%ldDME%%";

  int32_t res1 = s21_sscanf(str, fstr, &a1, b1, &c1, &d1, &e1);
  int32_t res2 = sscanf(str, fstr, &a2, b2, &c2, &d2, &e2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_float_infinite(c1);
  ck_assert_float_infinite(c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(sscanf_hard4) {
  char a1, a2;
  char b1, b2;
  char c1, c2;
  char d1, d2;

  const char str[] = "%%$Char!StressssT%%estus!&&&";
  const char fstr[] = "%% %*c%*c%*c%*c%*c %c %c %c %c ### %*c";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_hard5) {
  char a1, a2;
  char b1, b2;
  char c1, c2;
  char d1, d2;
  const char str[] =
      "%%$Char!StressssVIm User Aboba %% %%% %%% %% % % %% % "
      "% % %% % % %% %T%%estus!%%&&&";
  const char fstr[] =
      "%% %*c%*c%*c%*c%*c %c %c %c %c %% %% %% %% %% %% %% "
      "%% %% %% %% %% %% %% %% %% ### %*c";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "0xFFFF 0xAAA 7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs2) {
  char *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "0x4 0x3 0x2 0x1";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs3) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "03033 0333 0123 0123 0x123 0xFFFFF 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs4) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "0xABCDEF 0xAAA 7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs5) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "NULL";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats1) {
  long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

  const char str[] = "inf -4.1135 1e-6 2.3e+2";
  const char fstr[] = "%Lf %Lf %Lf %Lf";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq_tol(c1, c2, 1e-6);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(sscanf_floats2) {
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "+0.00001 -4123123 4.3e+2 1e-6";
  const char fstr[] = "%lf %lf %lf %lf";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  // ck_assert_double_eq(d1, d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(sscanf_floats3) {
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "inf .3 5.2 5.000001";
  const char fstr[] = "%lf %lf %lf %lf";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats4) {
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "513.41 -4.14135 414.3333 +112.0001";
  const char fstr[] = "%Lf %Lf %Lf %Lf";

  int16_t res1 = 0;
  res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = 0;
  res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_ldouble_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats5) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1;

  const char str[] = "53.1 -4.1135 411231.333 +2.0001";
  const char fstr[] = "%*f %f %f %f";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_floats_sci1) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  double d1 = 0, d2 = 0;

  const char str[] = "1.4441 1.31e+4 -3.31e-4  0.444e-5";
  const char fstr[] = "%G %G %G %lf";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(sscanf_floats_sci2) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "inf 1.31e+4 NaN 0.444e-5";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  // Unfortunately, assertions for inf do not work correctly in libcheck
  // ck_assert_ldouble_infinite(a1);
  // ck_assert_ldouble_infinite(a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_float_nan(c1);
  ck_assert_float_nan(c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats_sci3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "inF InF inF INF";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats_sci4) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "Nan NAN 0.0000 0";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats_sci5) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] =
      "nAN           INF                   -0.1111         1e-10";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_ldouble_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(s21_memchr_test) {
  const char *res_creat_func;
  const char *res_origin_func;

  // TEST 1 COMMON - LETTER AFTER BOUNDARIES
  res_creat_func = s21_memchr("Hello world\0", 'w', 5);
  res_origin_func = memchr("Hello world\0", 'w', 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 2 COMMON - LETTER AT BOUNDARIES
  res_creat_func = s21_memchr("Hello world\n\0", 'w', 10);
  res_origin_func = memchr("Hello world\n\0", 'w', 10);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON - FIND NEW LINE SYMB
  res_creat_func = s21_memchr("a\n\0", '\n', 12);
  res_origin_func = memchr("a\n\0", '\n', 12);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 4 COMMON - FIND 0 SYMB
  res_creat_func = s21_memchr(" \n\0", '\0', 100);
  res_origin_func = memchr(" \n\0", '\0', 100);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 5 COMMON - FIND SPACE SYMB
  res_creat_func = s21_memchr(" \0", ' ', 0);
  res_origin_func = memchr(" \0", ' ', 0);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON - STRING NOT CONTAIN THIS SYMB
  res_creat_func = s21_memchr("\n\0", 'q', 5);
  res_origin_func = memchr("\n\0", 'q', 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 7  - COMMON - FIND 0 SYMB AT EMPTY STRING
  res_creat_func = s21_memchr("\0", '\0', 1);
  res_origin_func = memchr("\0", '\0', 1);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_memcmp_test) {
  int res_creat_func;
  int res_origin_func;

  // TEST 1 - COMMON - EQUAL STRINGS
  char *f1 = "Hello world\0";
  char *s1 = "Hello world\0";
  res_creat_func = s21_memcmp(f1, s1, 5);
  res_origin_func = memcmp(f1, s1, 5);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON - EQUAL STRINGS
  char *f2 = "Hello world\n\0";
  char *s2 = "Hello world\n\0";
  res_creat_func = s21_memcmp(f2, s2, 13);
  res_origin_func = memcmp(f2, s2, 13);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 3 - COMMON - NOT EQUAL STRINGS
  char *f3 = "a\n\0";
  char *s3 = "Hello world\n\0";
  res_creat_func = s21_memcmp(f3, s3, 3);
  res_origin_func = memcmp(f3, s3, 3);
  ck_assert_int_gt(res_creat_func, 0);
  ck_assert_int_gt(res_origin_func, 0);

  // TEST 4  COMMON - NOT EQUAL STRINGS
  char *f4 = "H\n\0";
  char *s4 = "a\n\0";
  res_creat_func = s21_memcmp(f4, s4, 1);
  res_origin_func = memcmp(f4, s4, 1);
  ck_assert_int_lt(res_creat_func, 0);
  ck_assert_int_lt(res_origin_func, 0);

  // TEST 5  - COMMON - NOT EQUAL STRINGS WITH \N \0
  char *f5 = " \n\0";
  char *s5 = " \0";
  res_creat_func = s21_memcmp(f5, s5, 1);
  res_origin_func = memcmp(f5, s5, 1);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 6 - COMMON - NOT EQUAL STRINGS WITH \N \0
  char *f6 = " \0";
  char *s6 = "\n\0";
  res_creat_func = s21_memcmp(f6, s6, 2);
  res_origin_func = memcmp(f6, s6, 2);
  ck_assert_int_gt(res_creat_func, 0);
  ck_assert_int_gt(res_origin_func, 0);
}
END_TEST

START_TEST(s21_memcpy_test) {
  const char *res_creat_func;
  const char *res_origin_func;
  char buffer[100] = "Hello ";

  // TEST 1 - COMMON - COPY ALL STRING
  res_creat_func = s21_memcpy(buffer, "Hello world\0", 12);
  res_origin_func = memcpy(buffer, "Hello world\0", 12);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON - COPY ALL STRING
  res_creat_func = s21_memcpy(buffer, "world", 5);
  res_origin_func = memcpy(buffer, "world", 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 3 - COMMON - COPY ALL STRING
  res_creat_func = s21_memcpy(buffer, "a\n\0", 4);
  res_origin_func = memcpy(buffer, "a\n\0", 4);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 4 - COMMON - COPY PART STRING
  res_creat_func = s21_memcpy(buffer, " \n\0", 1);
  res_origin_func = memcpy(buffer, " \n\0", 1);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 5 - COMMON - COPY ALL STRING
  res_creat_func = s21_memcpy(buffer, " \0", 3);
  res_origin_func = memcpy(buffer, " \0", 3);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 6 - COMMON - COPY ALL STRING WITH \0
  res_creat_func = s21_memcpy(buffer, "\n\0", 2);
  res_origin_func = memcpy(buffer, "\n\0", 2);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 7 - COMMON - COPY EMPTY STRING
  res_creat_func = s21_memcpy(buffer, "", 1);
  res_origin_func = memcpy(buffer, "", 1);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_memmove_test) {
  const char *res_creat_func;
  const char *res_origin_func;
  char buffer[13] = "Hello ";

  // TEST 1 - COMMON - MOVE ALL STRING
  res_creat_func = s21_memmove(buffer, "Hello world\0", 12);
  res_origin_func = memmove(buffer, "Hello world\0", 12);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON - MOVE ALL STRING
  res_creat_func = s21_memmove(buffer, "world", 5);
  res_origin_func = memmove(buffer, "world", 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 3 - COMMON - MOVE ALL STRING
  res_creat_func = s21_memmove(buffer, "a\n\0", 4);
  res_origin_func = memmove(buffer, "a\n\0", 4);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 4 - COMMON - MOVE PART STRING
  res_creat_func = s21_memmove(buffer, " \n\0", 1);
  res_origin_func = memmove(buffer, " \n\0", 1);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 5 - COMMON - MOVE ALL STRING WITH \0
  res_creat_func = s21_memmove(buffer, " \0", 3);
  res_origin_func = memmove(buffer, " \0", 3);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 6 - COMMON - MOVE ALL STRING WITH \0
  res_creat_func = s21_memmove(buffer, "\n\0", 2);
  res_origin_func = memmove(buffer, "\n\0", 2);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 7 - COMMON - MOVE EMPTY STRING
  res_creat_func = s21_memmove(buffer, "", 1);
  res_origin_func = memmove(buffer, "", 1);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 8 - COMMON - MOVE PART STRING
  res_creat_func = s21_memmove(buffer, "123456789012345", 5);
  res_origin_func = memmove(buffer, "123456789012345", 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);
}

END_TEST

START_TEST(s21_memset_test) {
  const char *res_creat_func;
  const char *res_origin_func;
  char buffer[100] = "Hello ";

  // TEST 1 - COMMON - PART STRING
  res_creat_func = s21_memset(buffer, 'w', 12);
  res_origin_func = memset(buffer, 'w', 12);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON - PART STRING
  res_creat_func = s21_memset(buffer, '\n', 5);
  res_origin_func = memset(buffer, '\n', 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 3  COMMON - PART STRING
  res_creat_func = s21_memset(buffer, 'a', 5);
  res_origin_func = memset(buffer, 'a', 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 4  COMMON - PART STRING
  res_creat_func = s21_memset(buffer, '\0', 1);
  res_origin_func = memset(buffer, '\0', 1);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 5 COMMON - ALL STRING
  res_creat_func = s21_memset(buffer, ' ', 100);
  res_origin_func = memset(buffer, ' ', 100);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON - PART STRING
  res_creat_func = s21_memset(buffer, 'p', 2);
  res_origin_func = memset(buffer, 'p', 2);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 7 COMMON - PART STRING
  res_creat_func = s21_memset(buffer, 'q', 1);
  res_origin_func = memset(buffer, 'q', 1);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strlen_test) {
  s21_size_t res_creat_func, res_origin_func;

  // common tests
  //  TEST 1 COMMON
  char *str_1 = "Hello world\0";
  res_creat_func = s21_strlen(str_1);
  res_origin_func = strlen(str_1);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 2 COMMON
  char *str_2 = "Hello world\n\0";
  res_creat_func = s21_strlen(str_2);
  res_origin_func = strlen(str_2);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON
  char *str_3 = "a\n\0";
  res_creat_func = s21_strlen(str_3);
  res_origin_func = strlen(str_3);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 4 COMMON
  char *str_4 = " \n\0";
  res_creat_func = s21_strlen(str_4);
  res_origin_func = strlen(str_4);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 5 COMMON
  char *str_5 = " \0";
  res_creat_func = s21_strlen(str_5);
  res_origin_func = strlen(str_5);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON
  char *str_6 = "\n\0";
  res_creat_func = s21_strlen(str_6);
  res_origin_func = strlen(str_6);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 7 COMMON
  char *str_7 = "\0";
  res_creat_func = s21_strlen(str_7);
  res_origin_func = strlen(str_7);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // extra tests
  //  TEST 8 - 0 SYMB AT THE MIDDLE OF STRING
  char *str_8 = "Hello \0world";
  res_creat_func = s21_strlen(str_8);
  res_origin_func = strlen(str_8);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 9 - EMPTY STRING
  char *str_9 = "";
  res_creat_func = s21_strlen(str_9);
  res_origin_func = strlen(str_9);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 10 - LETTERS
  char *str_10 = "Hello world";
  res_creat_func = s21_strlen(str_10);
  res_origin_func = strlen(str_10);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 11 - NUMBERS
  char *str_11 = "123";
  res_creat_func = s21_strlen(str_11);
  res_origin_func = strlen(str_11);
  ck_assert_int_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strcmp_test) {
  int res_creat_func, res_origin_func;

  // common tests
  //  TEST 1 COMMON - FIRST STRING CONTAIN SECOND STRING
  char *f1 = "Hello world\0";
  char *s1 = "Hello";
  res_creat_func = s21_strcmp(f1, s1);
  res_origin_func = strcmp(f1, s1);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 2 COMMON SECOND STRING CONTAIN FIRST STRING
  char *f2 = "Hello";
  char *s2 = "Hello world\0";
  res_creat_func = s21_strcmp(f2, s2);
  res_origin_func = strcmp(f2, s2);
  ck_assert_int_eq(res_creat_func < 0, res_origin_func < 0);

  // TEST 3 COMMON - EQUAL STRINGS
  char *f3 = "a\n\0";
  char *s3 = "a\n\0";
  res_creat_func = s21_strcmp(f3, s3);
  res_origin_func = strcmp(f3, s3);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 4 COMMON - FIRST STRING CONTAIN SECOND STRING
  char *f4 = " \n\0";
  char *s4 = " ";
  res_creat_func = s21_strcmp(f4, s4);
  res_origin_func = strcmp(f4, s4);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 5 COMMON - FIRST STRING CONTAIN SECOND STRING
  char *f5 = " \n\0";
  char *s5 = "\n";
  res_creat_func = s21_strcmp(f5, s5);
  res_origin_func = strcmp(f5, s5);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 6 COMMON - FIRST STRING NOT CONTAIN SECOND STRING
  char *f6 = "\n\0";
  char *s6 = "abc";
  res_creat_func = s21_strcmp(f6, s6);
  res_origin_func = strcmp(f6, s6);
  ck_assert_int_eq(res_creat_func < 0, res_origin_func < 0);

  // TEST 7 COMMON - EMPTY STRINGS
  char *f7 = "\0";
  char *s7 = "\0";
  res_creat_func = s21_strcmp(f7, s7);
  res_origin_func = strcmp(f7, s7);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // extra tests
  //  TEST 8 EQUAL STRINGS
  char *f8 = "Hello\0";
  char *s8 = "Hello\0";
  res_creat_func = s21_strcmp(f8, s8);
  res_origin_func = strcmp(f8, s8);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 9  EMPTY STRINGS
  char *f9 = "";
  char *s9 = "";
  res_creat_func = s21_strcmp(f9, s9);
  res_origin_func = strcmp(f9, s9);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 10 SECOND STRING - IS EMPTY
  char *f10 = "abc";
  char *s10 = "";
  res_creat_func = s21_strcmp(f10, s10);
  res_origin_func = strcmp(f10, s10);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 11 EQUAL STRINGS
  char *f11 = "Hello world";
  char *s11 = "Hello world";
  res_creat_func = s21_strcmp(f11, s11);
  res_origin_func = strcmp(f11, s11);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 12 ONE LETTER - DIFFERENT TYPE OF CASE
  char *f12 = "Hello world";
  char *s12 = "HEllo world";
  res_creat_func = s21_strcmp(f12, s12);
  res_origin_func = strcmp(f12, s12);
  ck_assert_int_eq(res_creat_func < 0, res_origin_func < 0);

  // TEST 13 LETTERS
  char *f13 = "Hello world\n";
  char *s13 = "Hello world\n";
  res_creat_func = s21_strcmp(f13, s13);
  res_origin_func = strcmp(f13, s13);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 14 NUMBERS
  char *f14 = "123";
  char *s14 = "123";
  res_creat_func = s21_strcmp(f14, s14);
  res_origin_func = strcmp(f14, s14);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 15 AT THE FIRST STRING - 2 SECOND
  char *f15 = "123 123";
  char *s15 = "123";
  res_creat_func = s21_strcmp(f15, s15);
  res_origin_func = strcmp(f15, s15);
  ck_assert_int_eq(res_creat_func < 0, res_origin_func < 0);
}
END_TEST

START_TEST(s21_strncmp_test) {
  int res_creat_func;
  int res_origin_func;

  // TEST 1 COMMON - EQUAL STRING, NOT FULL LEN
  char *f1 = "Hello world\0";
  char *s1 = "Hello world\0";
  res_creat_func = s21_strncmp(f1, s1, 5);
  res_origin_func = strncmp(f1, s1, 5);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 2 COMMON - EQUAL STRING, FULL LEN
  char *f2 = "Hello world\n\0";
  char *s2 = "Hello world\n\0";
  res_creat_func = s21_strncmp(f2, s2, 13);
  res_origin_func = strncmp(f2, s2, 13);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON - NOT EQUAL STRING, NOT FULL LEN
  char *f3 = "a\n\0";
  char *s3 = "Hello world\n\0";
  res_creat_func = s21_strncmp(f3, s3, 3);
  res_origin_func = strncmp(f3, s3, 3);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 4 COMMON - NOT EQUAL STRING, LEN 0
  char *f4 = " \n\0";
  char *s4 = "a\n\0";
  res_creat_func = s21_strncmp(f4, s4, 0);
  res_origin_func = strncmp(f4, s4, 0);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 5 COMMON - NOT EQUAL STRING, NOT FULL LEN
  char *f5 = " \n\0";
  char *s5 = " \0";
  res_creat_func = s21_strncmp(f5, s5, 1);
  res_origin_func = strncmp(f5, s5, 1);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON - NOT EQUAL STRING, FULL LEN
  char *f6 = " \0";
  char *s6 = "\n\0";
  res_creat_func = s21_strncmp(f6, s6, 2);
  res_origin_func = strncmp(f6, s6, 2);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 7 COMMON - EMPTY STRINGS, FULL LEN
  char *f7 = "\0";
  char *s7 = "\0";
  res_creat_func = s21_strncmp(f7, s7, 1);
  res_origin_func = strncmp(f7, s7, 1);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // extra tests
  //  TEST 8 TEST \0
  char *f8 = "Hello\0";
  char *s8 = "Hello";
  res_creat_func = s21_strncmp(f8, s8, 6);
  res_origin_func = strncmp(f8, s8, 6);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 9 EMPTY STRINGS, 0 LEN
  char *f9 = "";
  char *s9 = "";
  res_creat_func = s21_strncmp(f9, s9, 0);
  res_origin_func = strncmp(f9, s9, 0);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 10 EMPTY SECOND STRING, FULL LEN
  char *f10 = "abc";
  char *s10 = "";
  res_creat_func = s21_strncmp(f10, s10, 3);
  res_origin_func = strncmp(f10, s10, 3);
  ck_assert_int_eq(res_creat_func > 0, res_origin_func > 0);

  // TEST 11 EQUAL STRINGS, OVER FULL LEN
  char *f11 = "Hello world";
  char *s11 = "Hello world";
  res_creat_func = s21_strncmp(f11, s11, 20);
  res_origin_func = strncmp(f11, s11, 20);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 12 ONE LETTER - DIFFERENT TYPE OF CASE
  char *f12 = "Hello world";
  char *s12 = "HEllo world";
  res_creat_func = s21_strncmp(f12, s12, 2);
  res_origin_func = strncmp(f12, s12, 2);
  ck_assert_int_eq(res_creat_func < 0, res_origin_func < 0);

  // TEST 13 LETTERS
  char *f13 = "Hello world";
  char *s13 = "Hello world";
  res_creat_func = s21_strncmp(f13, s13, 11);
  res_origin_func = strncmp(f13, s13, 11);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 14 NUMBERS
  char *f14 = "123";
  char *s14 = "123";
  res_creat_func = s21_strncmp(f14, s14, 3);
  res_origin_func = strncmp(f14, s14, 3);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 15 DOUBLE NUMBERS
  char *f15 = "123 123";
  char *s15 = "123";
  res_creat_func = s21_strncmp(f15, s15, 4);
  res_origin_func = strncmp(f15, s15, 4);
  ck_assert_int_eq(res_creat_func < 0, res_origin_func < 0);
}
END_TEST

START_TEST(s21_strchr_test) {
  const char *res_creat_func;
  const char *res_origin_func;

  // common tests
  //  TEST 1 COMMON - CONTAIN \N
  char *s1 = "Hello world\n\0";
  res_creat_func = s21_strchr(s1, '\n');
  res_origin_func = strchr(s1, '\n');
  ck_assert_pstr_eq(res_creat_func,
                    res_origin_func);  // testing pointers for string

  // TEST 2 COMMON - CONTAIN LETTER
  char *s2 = "a\n\0";
  res_creat_func = s21_strchr(s2, 'a');
  res_origin_func = strchr(s2, 'a');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON - CONTAIN NUMBER (2 TIME)
  char *s3 = "123454321";
  res_creat_func = s21_strchr(s3, '1');
  res_origin_func = strchr(s3, '1');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 4 COMMON - CONTAIN SPACE
  char *s4 = " \0";
  res_creat_func = s21_strchr(s4, ' ');
  res_origin_func = strchr(s4, ' ');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 5 COMMON - CONTAIN \0
  char *s5 = "\n\0";
  res_creat_func = s21_strchr(s5, '\0');
  res_origin_func = strchr(s5, '\0');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON - EMPTY
  char *s6 = "";
  res_creat_func = s21_strchr(s6, '\0');
  res_origin_func = strchr(s6, '\0');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 7 COMMON - EMPTY
  char *s7 = "";
  res_creat_func = s21_strchr(s7, 'a');
  res_origin_func = strchr(s7, 'a');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // extra tests
  char *s = "Hello world\0";
  // TEST 8 CONTAIN SPACE
  res_creat_func = s21_strchr(s, ' ');
  res_origin_func = strchr(s, ' ');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 9 CONTAIN \0
  res_creat_func = s21_strchr(s, '\0');
  res_origin_func = strchr(s, '\0');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 10 CONTAIN LETTER
  res_creat_func = s21_strchr(s, 'w');
  res_origin_func = strchr(s, 'w');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 11 NOT CONTAIN LETTER
  char *s11 = " \n\0";
  res_creat_func = s21_strchr(s11, 'a');
  res_origin_func = strchr(s11, 'a');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 12 \0 AT THE CENTER
  char *s12 = "Hello \0world\n";
  res_creat_func = s21_strchr(s12, 'l');
  res_origin_func = strchr(s12, 'l');
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strcspn_test) {
  // TEST 1 CONTAINS ALL NUMBERS
  s21_size_t res_creat_func, res_origin_func;
  res_creat_func = s21_strcspn("123456789", "9876");
  res_origin_func = strcspn("123456789", "9876");
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 2 EMPTY STRING
  res_creat_func = s21_strcspn("", "9876");
  res_origin_func = strcspn("", "9876");
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // TEST 3 CONTAINS EMPTY
  res_creat_func = s21_strcspn("123456789", "");
  res_origin_func = strcspn("123456789", "");
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // common tests
  //  Test 4 COMMON - AT THE START
  char *str4 = "Hello world\0";
  char *sym4 = "He";
  res_creat_func = s21_strspn(str4, sym4);
  res_origin_func = strspn(str4, sym4);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 5 COMMON - AT THE END \N

  char *str5 = "Hello world\0";
  char *sym5 = "\n";
  res_creat_func = s21_strspn(str5, sym5);
  res_origin_func = strspn(str5, sym5);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 6 COMMON - AT THE END
  char *str6 = "Hello world\0";
  char *sym6 = "ld";
  res_creat_func = s21_strspn(str6, sym6);
  res_origin_func = strspn(str6, sym6);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 7 COMMON - AT THE END WITHOUT ONE LETTER (O)
  char *str7 = "Hello world\n\0";
  char *sym7 = "wld";
  res_creat_func = s21_strspn(str7, sym7);
  res_origin_func = strspn(str7, sym7);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 8 COMMON - AT THE START ONE LETTER
  char *str8 = "a\n\0";
  char *sym8 = "a";
  res_creat_func = s21_strspn(str8, sym8);
  res_origin_func = strspn(str8, sym8);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 9 COMMON - AT THE MIDDLE ONE LETTER
  char *str9 = " \n\0";
  char *sym9 = "\n";
  res_creat_func = s21_strspn(str9, sym9);
  res_origin_func = strspn(str9, sym9);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 10 COMMON - DIFFERENT
  char *str10 = " \0";
  char *sym10 = "abc";
  res_creat_func = s21_strspn(str10, sym10);
  res_origin_func = strspn(str10, sym10);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 11 COMMON SECOND EMPTY
  char *str11 = "\n\0";
  char *sym11 = "\0";
  res_creat_func = s21_strspn(str11, sym11);
  res_origin_func = strspn(str11, sym11);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 12 AS ARRAY - DIFFERENT
  char str12[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's'};
  ;
  char *sym12 = "123";
  res_creat_func = s21_strcspn(str12, sym12);
  res_origin_func = strcspn(str12, sym12);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 13 AS ARRAY - AT START
  char str13[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's'};
  ;
  char *sym13 = "qrr";
  res_creat_func = s21_strcspn(str13, sym13);
  res_origin_func = strcspn(str13, sym13);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 14 \0 AT THE MIDDLE
  char *str14 = "Hello \0world\n";
  char *sym14 = "wld";
  res_creat_func = s21_strcspn(str14, sym14);
  res_origin_func = strcspn(str14, sym14);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 15 FIRST CONTAINS SECOND TWO TIMES
  char *str15 = "Hello world Hello\n";
  char *sym15 = "Hello";
  res_creat_func = s21_strcspn(str15, sym15);
  res_origin_func = strcspn(str15, sym15);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 16 - 2 LETTER - DIFFERENT
  char *str16 = "aobc";
  char *sym16 = "aObz";
  res_creat_func = s21_strcspn(str16, sym16);
  res_origin_func = strcspn(str16, sym16);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 17 FIRST BIGGER STHAN SECOND
  char *str17 = "A12A3A4A5A";
  char *sym17 = "123";
  res_creat_func = s21_strcspn(str17, sym17);
  res_origin_func = strcspn(str17, sym17);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 18 NUMBERS
  char *str18 = "1234567890";
  char *sym18 = "0987654321";
  res_creat_func = s21_strcspn(str18, sym18);
  res_origin_func = strcspn(str18, sym18);
  ck_assert_int_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strpbrk_test) {
  const char *res_creat_func;
  const char *res_origin_func;

  // TEST 1 - COMMON START
  char *s1 = "Hello world\0";
  char *t1 = "Hello";
  res_creat_func = s21_strpbrk(s1, t1);
  res_origin_func = strpbrk(s1, t1);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON - SECOND EMPTY
  char *s2 = "Hello world\n\0";
  char *t2 = " ";
  res_creat_func = s21_strpbrk(s2, t2);
  res_origin_func = strpbrk(s2, t2);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON - AT THE END
  char *s3 = "a\n\0";
  char *t3 = "\n";
  res_creat_func = s21_strpbrk(s3, t3);
  res_origin_func = strpbrk(s3, t3);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 4 COMMON - DIFFERENT
  char *s4 = " \n\0";
  char *t4 = "a";
  res_creat_func = s21_strpbrk(s4, t4);
  res_origin_func = strpbrk(s4, t4);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 5 - COMMON - EQUAL
  char *s5 = " \0";
  char *t5 = " ";
  res_creat_func = s21_strpbrk(s5, t5);
  res_origin_func = strpbrk(s5, t5);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON - SECOND EMPTY
  char *s6 = "\n\0";
  char *t6 = "\0";

  res_creat_func = s21_strpbrk(s6, t6);
  res_origin_func = strpbrk(s6, t6);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 7 - COMMON - BOTH EMPTY
  char *s7 = "\0";
  char *t7 = "\0";
  res_creat_func = s21_strpbrk(s7, t7);
  res_origin_func = strpbrk(s7, t7);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 8 COMMON START
  char *s8 = "Hello world";
  char *t8 = "Hello";
  res_creat_func = s21_strpbrk(s8, t8);
  res_origin_func = strpbrk(s8, t8);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 9 ONE LETTER CASE SENS
  char *s9 = "Hello world";
  char *t9 = "HEllo";
  res_creat_func = s21_strpbrk(s9, t9);
  res_origin_func = strpbrk(s9, t9);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 10 TWO TIMES WORD
  char *s10 = "Hello world world";
  char *t10 = "world";
  res_creat_func = s21_strpbrk(s10, t10);
  res_origin_func = strpbrk(s10, t10);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 11 NUMBERS
  char *s11 = "123456";
  char *t11 = "234";
  res_creat_func = s21_strpbrk(s11, t11);
  res_origin_func = strpbrk(s11, t11);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 12 NUMBER
  char *s12 = "123456789 987654321";
  char *t12 = "9";
  res_creat_func = s21_strpbrk(s12, t12);
  res_origin_func = strpbrk(s12, t12);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 13 SPACES
  char *s13 = " ";
  char *t13 = " ";
  res_creat_func = s21_strpbrk(s13, t13);
  res_origin_func = strpbrk(s13, t13);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 14 EMPTIES
  char *s14 = "";
  char *t14 = "";
  res_creat_func = s21_strpbrk(s14, t14);
  res_origin_func = strpbrk(s14, t14);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 15 EMPTY AND SPACE
  char *s15 = "";
  char *t15 = " ";
  res_creat_func = s21_strpbrk(s15, t15);
  res_origin_func = strpbrk(s15, t15);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 16 \0 AT THE MIDDLE START
  char *s16 = "Hello \0world";
  char *t16 = "Hello";
  res_creat_func = s21_strpbrk(s16, t16);
  res_origin_func = strpbrk(s16, t16);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 17 \0 AT THE MIDDLE END
  char *s17 = "Hello \0world";
  char *t17 = "world";
  res_creat_func = s21_strpbrk(s17, t17);
  res_origin_func = strpbrk(s17, t17);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 18 SECOND EMPTY
  char *s18 = "Hello \0world";
  char *t18 = "";
  res_creat_func = s21_strpbrk(s18, t18);
  res_origin_func = strpbrk(s18, t18);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 19 AS ARRAY
  char s19[] = {'a', 'b', 'c'};
  char *t19 = "a";
  res_creat_func = s21_strpbrk(s19, t19);
  res_origin_func = strpbrk(s19, t19);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strrchr_test) {
  const char *res_creat_func;
  const char *res_origin_func;

  // TEST 1 - COMMON -STRING CONTAIN LETTER
  char *str1 = "Hello world";
  int c1 = 'e';
  res_creat_func = s21_strrchr(str1, c1);
  res_origin_func = strrchr(str1, c1);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON -STRING NOT CONTAIN LETTER
  char *str2 = "Hello world\0";
  int c2 = 'p';
  res_creat_func = s21_strrchr(str2, c2);
  res_origin_func = strrchr(str2, c2);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 3 - COMMON - EMPTY STRING
  char *str3 = "";
  int c3 = 'l';
  res_creat_func = s21_strrchr(str3, c3);
  res_origin_func = strrchr(str3, c3);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 4 - COMMON - \0 SYMB
  char *str4 = "Hello world";
  int c4 = 0;
  res_creat_func = s21_strrchr(str4, c4);
  res_origin_func = strrchr(str4, c4);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 5 - COMMON - FIRST LETTER
  char *str5 = "Hello world";
  int c5 = 'H';
  res_creat_func = s21_strrchr(str5, c5);
  res_origin_func = strrchr(str5, c5);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 6 - COMMON - FIRST LETTER
  char *str6 = "a\n\0";
  int c6 = 'a';
  res_creat_func = s21_strrchr(str6, c6);
  res_origin_func = strrchr(str6, c6);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 7 - COMMON - END LETTER
  char *str7 = "a\n\0";
  int c7 = '\n';
  res_creat_func = s21_strrchr(str7, c7);
  res_origin_func = strrchr(str7, c7);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 8 - COMMON - \0
  char *str8 = "a\n\0";
  int c8 = '\0';
  res_creat_func = s21_strrchr(str8, c8);
  res_origin_func = strrchr(str8, c8);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 9 - COMMON - SPACE
  char *str9 = " \n\0";
  int c9 = ' ';
  res_creat_func = s21_strrchr(str9, c9);
  res_origin_func = strrchr(str9, c9);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 10 - COMMON - EMPTY STRING
  char *str10 = "\0";
  int c10 = '\0';
  res_creat_func = s21_strrchr(str10, c10);
  res_origin_func = strrchr(str10, c10);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 11 - COMMON - \N
  char *str11 = "\n\0";
  int c11 = '\n';
  res_creat_func = s21_strrchr(str11, c11);
  res_origin_func = strrchr(str11, c11);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 12 - COMMON - STRING NOT CONTAIN LETTER
  char *str12 = " \0";
  int c12 = '1';
  res_creat_func = s21_strrchr(str12, c12);
  res_origin_func = strrchr(str12, c12);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // extra tests
  //  TEST 13 - LETTER TWO TIMES AT THE STRING
  char *str13 = "abcba";
  int c13 = 'a';
  res_creat_func = s21_strrchr(str13, c13);
  res_origin_func = strrchr(str13, c13);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 14 NUMBERS
  char *str14 = "123454321";
  int c14 = '2';
  res_creat_func = s21_strrchr(str14, c14);
  res_origin_func = strrchr(str14, c14);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 15 EMPTY STRING
  char *str15 = "";
  int c15 = '\0';
  res_creat_func = s21_strrchr(str15, c15);
  res_origin_func = strrchr(str15, c15);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strspn_test) {
  s21_size_t res_creat_func, res_origin_func;

  // extra tests
  //  Test 1 - AT THE START
  char *str1 = "0123456789";
  char *sym1 = "210";
  res_creat_func = s21_strspn(str1, sym1);
  res_origin_func = strspn(str1, sym1);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 2 - AT THE START
  char *str2 = "12345";
  char *sym2 = "123";
  res_creat_func = s21_strspn(str2, sym2);
  res_origin_func = strspn(str2, sym2);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 3 - SPACE
  char *str3 = "12345";
  char *sym3 = " ";
  res_creat_func = s21_strspn(str3, sym3);
  res_origin_func = strspn(str3, sym3);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 4 - EMPTY STRING
  char *str4 = "12345";
  char *sym4 = "";
  res_creat_func = s21_strspn(str4, sym4);
  res_origin_func = strspn(str4, sym4);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 5 SPACES
  char *str5 = " ";
  char *sym5 = " ";
  res_creat_func = s21_strspn(str5, sym5);
  res_origin_func = strspn(str5, sym5);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // common tests
  //  Test 6 COMMON - AT THE END
  char *str6 = "Hello world\0";
  char *sym6 = "ld";
  res_creat_func = s21_strspn(str6, sym6);
  res_origin_func = strspn(str6, sym6);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 7 COMMON - AT THE END + \N
  char *str7 = "Hello world\n\0";
  char *sym7 = "wld";
  res_creat_func = s21_strspn(str7, sym7);
  res_origin_func = strspn(str7, sym7);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 8 COMMON - AT THE START
  char *str8 = "a\n\0";
  char *sym8 = "a";
  res_creat_func = s21_strspn(str8, sym8);
  res_origin_func = strspn(str8, sym8);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 9 \N
  char *str9 = " \n\0";
  char *sym9 = "\n";
  res_creat_func = s21_strspn(str9, sym9);
  res_origin_func = strspn(str9, sym9);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 10 NOT CONTAIN
  char *str10 = " \0";
  char *sym10 = "abc";
  res_creat_func = s21_strspn(str10, sym10);
  res_origin_func = strspn(str10, sym10);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 11 EMPTY
  char *str11 = "\n\0";
  char *sym11 = "\0";
  res_creat_func = s21_strspn(str11, sym11);
  res_origin_func = strspn(str11, sym11);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 12 AS ARRAY NOT CONTAIN
  char str12[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's'};
  ;
  char *sym12 = "123";
  res_creat_func = s21_strspn(str12, sym12);
  res_origin_func = strspn(str12, sym12);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 13 AS ARRAY - CONTAIN
  char str13[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's'};
  ;
  char *sym13 = "qrr";
  res_creat_func = s21_strspn(str13, sym13);
  res_origin_func = strspn(str13, sym13);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 14 - \0 AT THE MIDDLE
  char *str14 = "Hello \0world\n";
  char *sym14 = "wld";
  res_creat_func = s21_strspn(str14, sym14);
  res_origin_func = strspn(str14, sym14);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 15 - START
  char *str15 = "Hello world Hello\n";
  char *sym15 = "Hello";
  res_creat_func = s21_strspn(str15, sym15);
  res_origin_func = strspn(str15, sym15);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 16 - DIFF TWO LETTERS
  char *str16 = "aobc";
  char *sym16 = "aObz";
  res_creat_func = s21_strspn(str16, sym16);
  res_origin_func = strspn(str16, sym16);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 17 FIRST > SECOND
  char *str17 = "1A2A3A4A5A";
  char *sym17 = "123";
  res_creat_func = s21_strspn(str17, sym17);
  res_origin_func = strspn(str17, sym17);
  ck_assert_int_eq(res_creat_func, res_origin_func);

  // Test 18 NUMBERS
  char *str18 = "1234567890";
  char *sym18 = "0987654321";
  res_creat_func = s21_strspn(str18, sym18);
  res_origin_func = strspn(str18, sym18);
  ck_assert_int_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strstr_test) {
  const char *res_creat_func;
  const char *res_origin_func;

  // TEST 1 COMMON - START
  char *str1 = "Hello world";
  char *sym1 = "Hello";
  res_creat_func = s21_strstr(str1, sym1);
  res_origin_func = strstr(str1, sym1);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 2 COMMON - EMPTY
  char *str2 = "Hello world\0";
  char *sym2 = "";
  res_creat_func = s21_strstr(str2, sym2);
  res_origin_func = strstr(str2, sym2);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON - NOT CONTAIN
  char *str3 = "Hello world\n\0";
  char *sym3 = "abc";
  res_creat_func = s21_strstr(str3, sym3);
  res_origin_func = strstr(str3, sym3);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 4 COMMON - LAST LETTER DIFF
  char *str4 = "Hello world";
  char *sym4 = "Hello worlt";
  res_creat_func = s21_strstr(str4, sym4);
  res_origin_func = strstr(str4, sym4);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 5 COMMON - TWO TIMES AT THE STRING
  char *str5 = "Hello world Hello";
  char *sym5 = "Hello";
  res_creat_func = s21_strstr(str5, sym5);
  res_origin_func = strstr(str5, sym5);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON - \N
  char *str6 = "a\n\0";
  char *sym6 = "\n";
  res_creat_func = s21_strstr(str6, sym6);
  res_origin_func = strstr(str6, sym6);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 7 COMMON - SPACE
  char *str7 = " \n\0";
  char *sym7 = " ";
  res_creat_func = s21_strstr(str7, sym7);
  res_origin_func = strstr(str7, sym7);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 8 COMMON - \0
  char *str8 = " \0";
  char *sym8 = "\0";
  res_creat_func = s21_strstr(str8, sym8);
  res_origin_func = strstr(str8, sym8);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 9 COMMON - EMPTY
  char *str9 = "\0";
  char *sym9 = "abc";
  res_creat_func = s21_strstr(str9, sym9);
  res_origin_func = strstr(str9, sym9);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 10 COMMON - \N
  char *str10 = "\n\0";
  char *sym10 = "\n";
  res_creat_func = s21_strstr(str10, sym10);
  res_origin_func = strstr(str10, sym10);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // extra tests
  //  TEST 11 - EMPTIES
  char *str11 = "";
  char *sym11 = "";
  res_creat_func = s21_strstr(str11, sym11);
  res_origin_func = strstr(str11, sym11);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 12 - EMPTIES
  char *str12 = "\0";
  char *sym12 = "\0";
  res_creat_func = s21_strstr(str12, sym12);
  res_origin_func = strstr(str12, sym12);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 13 - AT THE MIDDLE
  char *str13 = "Hello world";
  char *sym13 = "ell";
  res_creat_func = s21_strstr(str13, sym13);
  res_origin_func = strstr(str13, sym13);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 14 - \0 AT THE MIDDLE
  char *str14 = "H\0ello world";
  char *sym14 = "ell";
  res_creat_func = s21_strstr(str14, sym14);
  res_origin_func = strstr(str14, sym14);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 15 AS ARRAY - CONTAIN
  char str15[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
  char *sym15 = "qr";
  res_creat_func = s21_strstr(str15, sym15);
  res_origin_func = strstr(str15, sym15);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 16 AS ARRAY - REVERSE
  char str16[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
  ;
  char *sym16 = "rq";
  res_creat_func = s21_strstr(str16, sym16);
  res_origin_func = strstr(str16, sym16);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 17 DIFF CASES
  char *str17 = "abc";
  char *sym17 = "ABC";
  res_creat_func = s21_strstr(str17, sym17);
  res_origin_func = strstr(str17, sym17);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 18 EQUAL STRINGS
  char *str18 = "a";
  char *sym18 = "a";
  res_creat_func = s21_strstr(str18, sym18);
  res_origin_func = strstr(str18, sym18);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 19 REVERSE AND DIRECTIVE AT THE STRING
  char *str19 = "cba abc";
  char *sym19 = "abc";
  res_creat_func = s21_strstr(str19, sym19);
  res_origin_func = strstr(str19, sym19);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);

  // TEST 20 - EMPTY
  char *str20 = "";
  char *sym20 = "abc";
  res_creat_func = s21_strstr(str20, sym20);
  res_origin_func = strstr(str20, sym20);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strtok_test) {  // под каждый новый тест обеим функциям нужно
                               // давать СВОИ строки!!!
  const char *res_creat_func;
  const char
      *res_origin_func;  // оно работает как с массивом, но не с указателем

  // TEST 1 ONE DELIM - SPACE
  char str1c[] = "Hello world";
  char str1o[] = "Hello world";
  res_creat_func = s21_strtok(str1c, " ");
  res_origin_func = strtok(str1o, " ");
  printf("Test1 start create: %s\n", res_creat_func);
  printf("Test1 start orig: %s\n", res_origin_func);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, " ");
    res_origin_func = strtok(S21_NULL, " ");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test1 cont create: %s\n", res_creat_func);
    printf("Test1 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 2 - NO DELIM
  char str1_2c[] = "Hello world";
  char str1_2o[] = "Hello world";
  res_creat_func = s21_strtok(str1_2c, "");
  res_origin_func = strtok(str1_2o, "");
  printf("Test2 start create: %s\n", res_creat_func);
  printf("Test2 start orig: %s\n", res_origin_func);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "");
    res_origin_func = strtok(S21_NULL, "");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test2 cont create: %s\n", res_creat_func);
    printf("Test2 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 3 - DIFFERENT DELIMS
  char str1_3c[] = "Hello world";
  char str1_3o[] = "Hello world";
  res_creat_func = s21_strtok(str1_3c, " ");
  res_origin_func = strtok(str1_3o, " ");
  printf("Test3 start create: %s\n", res_creat_func);
  printf("Test3 start orig: %s\n", res_origin_func);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "l");  //не работает разные
    res_origin_func = strtok(S21_NULL, "l");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test3 cont create: %s\n", res_creat_func);
    printf("Test3 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 4 - TWO EQUAL DELIMS
  char str1_4c[] = "Hello world";
  char str1_4o[] = "Hello world";
  res_creat_func = s21_strtok(str1_4c, "ll");
  res_origin_func = strtok(str1_4o, "ll");
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test4 start create: %s\n", res_creat_func);
  printf("Test4 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "ll");
    res_origin_func = strtok(S21_NULL, "ll");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test4 cont create: %s\n", res_creat_func);
    printf("Test4 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 5 TWO DELIMRS - FIRST AT THE STR
  char str1_5c[] = "Hello world";
  char str1_5o[] = "Hello world";
  res_creat_func = s21_strtok(str1_5c, "He");
  res_origin_func = strtok(str1_5o, "He");
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test5 start create: %s\n", res_creat_func);
  printf("Test5 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "He");
    res_origin_func = strtok(S21_NULL, "He");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test5 cont create: %s\n", res_creat_func);
    printf("Test5 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 6 TWO DELIMRS - LAST AT THE STR
  char str1_6c[] = "Hello world";
  char str1_6o[] = "Hello world";
  res_creat_func = s21_strtok(str1_6c, "ld");
  res_origin_func = strtok(str1_6o, "ld");
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test6 start create: %s\n", res_creat_func);
  printf("Test6 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "ld");
    res_origin_func = strtok(S21_NULL, "ld");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test6 cont create: %s\n", res_creat_func);
    printf("Test6 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // падает res_creat_func == "", res_origin_func == (null)
  // TEST 7 ONE DELIM - FIRST LETTER AT STR
  char str1_7c[] = "Hello world";
  char str1_7o[] = "Hello world";
  res_creat_func = s21_strtok(str1_7c, "H");
  res_origin_func = strtok(str1_7o, "H");
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test7 start create: %s\n", res_creat_func);
  printf("Test7 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "H");
    res_origin_func = strtok(S21_NULL, "H");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test7 cont create: %s\n", res_creat_func);
    printf("Test7 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 8 ONE DELIM - LAST LETTER AT STR
  char str1_8c[] = "Hello world";
  char str1_8o[] = "Hello world";
  res_creat_func = s21_strtok(str1_8c, "d");
  res_origin_func = strtok(str1_8o, "d");
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test8 start create: %s\n", res_creat_func);
  printf("Test8 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "d");
    res_origin_func = strtok(S21_NULL, "d");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test8 cont create: %s\n", res_creat_func);
    printf("Test8 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 9 MULTI DELIMS - FROM DIFFERENT PLACES AT STR
  char str1_9c[] = "Hello world";
  char str1_9o[] = "Hello world";
  res_creat_func = s21_strtok(str1_9c, "e o");
  res_origin_func = strtok(str1_9o, "e o");
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test9 start create: %s\n", res_creat_func);
  printf("Test9 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, "e o");
    res_origin_func = strtok(S21_NULL, "e o");
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test9 cont create: %s\n", res_creat_func);
    printf("Test9 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 10 EMPTY STR
  char str1_10[] = "Hello world";  // as delims
  res_creat_func = s21_strtok("", str1_10);
  res_origin_func = strtok("", str1_10);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test10 start create: %s\n", res_creat_func);
  printf("Test10 start orig: %s\n", res_origin_func);
  printf("\n");

  // TEST 11 STR ONLY BY THE DELIMS
  char str11_c[] = "+++++";
  char str11_o[] = "+++++";
  res_creat_func = s21_strtok(str11_c, "+");
  res_origin_func = strtok(str11_o, "+");
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test10_1 start create: %s\n", res_creat_func);
  printf("Test10_1 start orig: %s\n", res_origin_func);
  printf("\n");

  // TEST 12 COMPLICATED_1 ONE DELIM. STR END WITH DELIM
  char str12_c[] = "Hello*world*";
  char str12_o[] = "Hello*world*";
  char del12[] = "*";
  res_creat_func = s21_strtok(str12_c, del12);
  res_origin_func = strtok(str12_o, del12);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test11_1 start create: %s\n", res_creat_func);
  printf("Test11_1 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, del12);
    res_origin_func = strtok(S21_NULL, del12);
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test11_1 cont create: %s\n", res_creat_func);
    printf("Test11_1 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 13 COMPLICATED_1 ONE DELIM. STR START WITH DELIM
  char str13_c[] = "*Hello*world";
  char str13_o[] = "*Hello*world";
  char del13[] = "*";
  res_creat_func = s21_strtok(str13_c, del13);
  res_origin_func = strtok(str13_o, del13);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test11 start create: %s\n", res_creat_func);
  printf("Test11 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, del13);
    res_origin_func = strtok(S21_NULL, del13);
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test11 cont create: %s\n", res_creat_func);
    printf("Test11 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 14 COMPLICATED_2 MULTI DELIMS ONE AFTER THE OTHER AT STR
  char str14_c[] = "*+Hello*world*";
  char str14_o[] = "*+Hello*world*";
  char del14[] = "*+";

  res_creat_func = s21_strtok(str14_c, del14);
  res_origin_func = strtok(str14_o, del14);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test12 start create: %s\n", res_creat_func);
  printf("Test12 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, del14);
    res_origin_func = strtok(S21_NULL, del14);
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test12 cont create: %s\n", res_creat_func);
    printf("Test12 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 15 COMPLICATED_3 MULTI DELIMS AT STR
  char str15_c[] = "*Hello+world*";
  char str15_o[] = "*Hello+world*";
  char del15[] = "*+";
  res_creat_func = s21_strtok(str15_c, del15);
  res_origin_func = strtok(str15_o, del15);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test13 start create: %s\n", res_creat_func);
  printf("Test13 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, del15);
    res_origin_func = strtok(S21_NULL, del15);
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test13 cont create: %s\n", res_creat_func);
    printf("Test13 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 16 NO DELIMS AT THE STR
  char str16_c[] = "*Hello+world*";
  char str16_o[] = "*Hello+world*";
  char del16[] = "abc";
  res_creat_func = s21_strtok(str16_c, del16);
  res_origin_func = strtok(str16_o, del16);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test14 start create: %s\n", res_creat_func);
  printf("Test14 start orig: %s\n", res_origin_func);
  while (res_origin_func != S21_NULL) {
    res_creat_func = s21_strtok(S21_NULL, del16);
    res_origin_func = strtok(S21_NULL, del16);
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test14 cont create: %s\n", res_creat_func);
    printf("Test14 cont orig: %s\n", res_origin_func);
  }
  printf("\n");

  // TEST 17 STEPS > WORDS
  char str17_c[] = "Hello1world2Hello3world";
  char str17_o[] = "Hello1world2Hello3world";
  char del17[] = "123";

  res_creat_func = s21_strtok(str17_c, del17);
  res_origin_func = strtok(str17_o, del17);
  ck_assert_pstr_eq(res_creat_func, res_origin_func);
  printf("Test15 start create: %s\n", res_creat_func);
  printf("Test15 start orig: %s\n", res_origin_func);
  s21_size_t steps = 5;
  while (steps) {
    res_creat_func = s21_strtok(S21_NULL, del17);
    res_origin_func = strtok(S21_NULL, del17);
    ck_assert_pstr_eq(res_creat_func, res_origin_func);
    printf("Test15 at the step %llu create: %s\n", 6 - steps, res_creat_func);
    printf("Test15 cont orig: %s\n", res_origin_func);
    steps--;
  }
}
END_TEST

START_TEST(s21_strncpy_test) {
  const char *res_creat_func;
  const char *res_origin_func;
  char buffer[100] = "Hello ";

  // TEST 1 COMMON - ALL STRING
  res_creat_func = s21_strncpy(buffer, "Hello world\0", 12);
  res_origin_func = strncpy(buffer, "Hello world\0", 12);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 2 COMMON - PART STRING
  res_creat_func = s21_strncpy(buffer, "world\0", 6);
  res_origin_func = strncpy(buffer, "world\0", 6);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON - ALL STRING
  res_creat_func = s21_strncpy(buffer, "a\n\0", 3);
  res_origin_func = strncpy(buffer, "a\n\0", 3);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 4 COMMON - OVER ALL STRING
  res_creat_func = s21_strncpy(buffer, " \n\0", 4);
  res_origin_func = strncpy(buffer, " \n\0", 4);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 5 COMMON - OVER ALL STRING
  res_creat_func = s21_strncpy(buffer, " \0", 5);
  res_origin_func = strncpy(buffer, " \0", 5);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 6 COMMON - OVER ALL STRING
  res_creat_func = s21_strncpy(buffer, "\n\0", 6);
  res_origin_func = strncpy(buffer, "\n\0", 6);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 7 EMPTY
  res_creat_func = s21_strncpy(buffer, "\0", 7);
  res_origin_func = strncpy(buffer, "\0", 7);
  ck_assert_ptr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strcat_test) {
  const char *res_creat_func;
  const char *res_origin_func;
  char s1[100] = "Hello ";

  // TEST 1 COMMON
  res_creat_func = s21_strcat(s1, "world");
  res_origin_func = strcat(s1, "world");
  ck_assert_str_eq(res_creat_func, res_origin_func);

  // TEST 2 COMMON - EMPTY
  res_creat_func = s21_strcat(s1, "");
  res_origin_func = strcat(s1, "");
  ck_assert_str_eq(res_creat_func, res_origin_func);

  // TEST 3 COMMON - \N
  res_creat_func = s21_strcat(s1, "\n");
  res_origin_func = strcat(s1, "\n");
  ck_assert_str_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strncat_test) {
  const char *res_creat_func;
  const char *res_origin_func;
  char s1[100] = "Hello ";

  // TEST 1 - COMMON
  res_creat_func = s21_strncat(s1, "world", 2);
  res_origin_func = strncat(s1, "world", 2);
  ck_assert_str_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON - EMPTY
  res_creat_func = s21_strncat(s1, "", 2);
  res_origin_func = strncat(s1, "", 2);
  ck_assert_str_eq(res_creat_func, res_origin_func);

  // TEST 3 - COMMON - \N
  res_creat_func = s21_strncat(s1, "\n", 0);
  res_origin_func = strncat(s1, "\n", 0);
  ck_assert_str_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strcpy_test) {
  const char *res_creat_func;
  const char *res_origin_func;
  char buffer[100] = "Hello ";

  // TEST 1 - COMMON
  res_creat_func = s21_strcpy(buffer, "Hello world\0");
  res_origin_func = strcpy(buffer, "Hello world\0");
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 2 - COMMON
  res_creat_func = s21_strcpy(buffer, "world");
  res_origin_func = strcpy(buffer, "world");
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 3 - COMMON
  res_creat_func = s21_strcpy(buffer, "a\n\0");
  res_origin_func = strcpy(buffer, "a\n\0");
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 4 - COMMON
  res_creat_func = s21_strcpy(buffer, " \n\0");
  res_origin_func = strcpy(buffer, " \n\0");
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 5 - COMMON
  res_creat_func = s21_strcpy(buffer, " \0");
  res_origin_func = strcpy(buffer, " \0");
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 6 - COMMON  \N\0
  res_creat_func = s21_strcpy(buffer, "\n\0");
  res_origin_func = strcpy(buffer, "\n\0");
  ck_assert_ptr_eq(res_creat_func, res_origin_func);

  // TEST 7 - COMMON - EMPTY
  res_creat_func = s21_strcpy(buffer, "\0");
  res_origin_func = strcpy(buffer, "\0");
  ck_assert_ptr_eq(res_creat_func, res_origin_func);
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = 0; i < 200; i++) {
    char *res_creat_func = s21_strerror(i);
    //  char *res_origin_func = strerror(i);
    printf("%s\n", res_creat_func);
    //  ck_assert_str_eq(res_creat_func, res_origin_func);
  }
}
END_TEST

// s21_to_upper tests
START_TEST(s21_to_upper_test_1) {
  char test_str[100] = {"zZNuLL 34 Aa 0123\0\n\t$%?!-=>"};
  char out_expected[100] = {"ZZNULL 34 AA 0123"};
  char *out_s21 = s21_to_upper(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  char test_str[50] = {""};
  char out_expected[50] = {""};
  char *out_s21 = s21_to_upper(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_to_upper_test_3) {
  char test_str[100] = {"zZNuLL 34 Aa 0123$%?!-=>"};
  char out_expected[100] = {"ZZNULL 34 AA 0123$%?!-=>"};
  char *out_s21 = s21_to_upper(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

// s21_to_lower test
START_TEST(s21_to_lower_test_1) {
  char test_str[100] = {"zZNuLL 34 Aa 0123$%?!-=>"};
  char out_expected[100] = {"zznull 34 aa 0123$%?!-=>"};
  char *out_s21 = s21_to_lower(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_to_lower_test_2) {
  char test_str[50] = {""};
  char out_expected[50] = {""};
  char *out_s21 = s21_to_lower(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

START_TEST(s21_to_lower_test_3) {
  char test_str[100] = {"zZNuLL 34 Aa 0123\0\n\t$%?!-=>"};
  char out_expected[100] = {"zznull 34 aa 0123"};
  char *out_s21 = s21_to_lower(test_str);
  ck_assert_str_eq(out_s21, out_expected);
  free(out_s21);
}
END_TEST

// s21_insert tests
START_TEST(s21_insert_test_1) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {" nice"};
  s21_size_t index = 6;
  char out_expected[50] = {"Hello, nice World!"};
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_str_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_2) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"Oh!!! "};
  s21_size_t index = 0;
  char out_expected[50] = {"Oh!!! Hello, World!"};
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_str_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_3) {
  char test_str[50] = {"Hello, World!"};
  char ins[50] = {"outoutoutoutout"};
  s21_size_t index = 50;
  char *out_expected = S21_NULL;
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_4) {
  char test_str[50] = {""};
  char ins[50] = {""};
  s21_size_t index = 0;
  char out_expected[50] = {""};
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_insert_test_5) {
  char *test_str = S21_NULL;
  char *ins = S21_NULL;
  s21_size_t index = 10;
  char *out_expected = S21_NULL;
  char *out_s21 = (char *)s21_insert(test_str, ins, index);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

// trim tests
START_TEST(s21_trim_test_1) {
  char test_str[50] = {""};
  char trims[50] = {""};
  char out_expected[50] = {""};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test_2) {
  char test_str[50] = {""};
  char trims[50] = {"@#$<hello >$%^"};
  char out_expected[50] = {""};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(s21_trim_test_3) {
  char test_str[50] = {" /***% Hello world ***"};
  char trims[50] = {""};
  char out_expected[50] = {"/***% Hello world ***"};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

START_TEST(sprintf_1) {
  char str1[100];
  char str2[100];

  unsigned int n1 = 0, n2 = 0;
  int r1 = sprintf(str1, "%d%o%s%c%i%e%f%E%g%u%x%G%X%%%n%s", 25, 342, "aboba",
                   'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                   8342, 0.0000456, 1235, &n1, "hello my friend");
  int r2 =
      s21_sprintf(str2, "%d%o%s%c%i%e%f%E%g%u%x%G%X%%%n%s", 25, 342, "aboba",
                  'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                  8342, 0.0000456, 1235, &n2, "hello my friend");

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_2) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST
START_TEST(sprintf_3) {
  char str1[1000];
  char str2[1000];
  void *p1 = (void *)0x123456789;
  void *p2 = (void *)4325234;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;
  int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                   10, p3, p1, 10, p4);
  int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                       p2, 10, p3, p1, 10, p4);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_4) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(
      str1,
      "%G%25G%#-15G%017G%#05.2G%#010.14G%+#8.6G%*.8G%#-10.*G%+#12.13G%*.*G",
      43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 0.000000342);
  int r2 = s21_sprintf(
      str2,
      "%G%25G%#-15G%017G%#05.2G%#010.14G%+#8.6G%*.8G%#-10.*G%+#12.13G%*.*G",
      43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5,
      111.432534243243242, 4324.43242, 25, -3213.43242, 16, -43.43242353242342,
      111.24324242, 25, 5, 0.000000342);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}

START_TEST(sprintf_5) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  int r1 =
      sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
              4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u,
              20, 2432u, l, h);
  int r2 = s21_sprintf(
      str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu", 4321u,
      34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l,
      h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST
START_TEST(sprintf_6) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 345;
  unsigned long l = 52342353242l;
  int r1 = sprintf(str1,
                   "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*"
                   "x%#10.*x%*.5hx%10.25lx",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%"
                       "20.*x%#10.*x%*.5hx%10.25lx",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_7) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(
      str1,
      "%+-10.3f%+10.2f%15.10f%+*.6f%*.10f%-10.*f%25.*f%25.f%#+10.f%*.*f% 2f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244, 13.567);
  int r2 = s21_sprintf(
      str2,
      "%+-10.3f%+10.2f%15.10f%+*.6f%*.10f%-10.*f%25.*f%25.f%#+10.f%*.*f% 2f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244, 13.567);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_8) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 253;
  unsigned long l = 4325234324242l;
  int r1 = sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                   12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  int r2 =
      s21_sprintf(str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                  12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_9) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.10E",
                   3456.4325, 8, 23452.43242, 5, -0.05234, 25.432523432, 10, 2,
                   53242.4242, 10, 456789.43242, 25, 1111122222.34567899,
                   2345678.23453242);
  int r2 = s21_sprintf(str2, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.10E",
                       3456.4325, 8, 23452.43242, 5, -0.05234, 25.432523432, 10,
                       2, 53242.4242, 10, 456789.43242, 25, 1111122222.34567899,
                       2345678.23453242);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_10) {
  char str1[1000];
  char str2[1000];
  int r1 =
      sprintf(str1, "%+-20e%010.*e%-*.10e%#025.7e%*.*e%*.9e%#010.*e%25.13e",
              2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
              11111.22, 16, -3245.3425342, 10, -0.00123, 235423424.43252);
  int r2 = s21_sprintf(
      str2, "%+-20e%010.*e%-*.10e%#025.7e%*.*e%*.9e%#010.*e%25.13e", 2543.43254,
      10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15, 11111.22, 16,
      -3245.3425342, 10, -0.00123, 235423424.43252);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_11) {
  char str1[1000];
  char str2[1000];
  short h = 34;
  long l = 2353423523424;
  int r1 = sprintf(str1, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                   34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  int r2 =
      s21_sprintf(str2, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                  34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_12) {
  char str1[1000];
  char str2[1000];
  char c1 = 'T', c2 = 'Z';
  int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e',
                   'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a',
                       'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_13) {
  char str1[100];
  char str2[100];

  unsigned int n1 = 0, n2 = 0;
  int r1 = sprintf(str1, "%d%o%s%c%i%e%f%E%g%u%x%G%X%%%n%s", 25, 342, "aboba",
                   'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                   8342, 0.0000456, 1235, &n1, "hello my friend");
  int r2 =
      s21_sprintf(str2, "%d%o%s%c%i%e%f%E%g%u%x%G%X%%%n%s", 25, 342, "aboba",
                  'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                  8342, 0.0000456, 1235, &n2, "hello my friend");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_14) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d% -10d% 10d", 252, 243,
                   256.34, 15, 12, -16);
  int r2 = s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d% -10d% 10d", 252, 243,
                       256.34, 15, 12, -16);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_15) {
  char str1[100];
  char str2[100];
  int r1 = sprintf(str1, "%g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567,
                   "HELLOMYDEARFRIEND");
  int r2 = s21_sprintf(str2, "%g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567,
                       "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_16) {
  char str1[100];
  char str2[100];
  void *p = (void *)43252342;
  int r1 = sprintf(str1, "%#24.f%-15.20i%20p%020u", 43253242.4342, 4567899, p,
                   43252342u);
  int r2 = s21_sprintf(str2, "%#24.f%-15.20i%20p%020u", 43253242.4342, 4567899,
                       p, 43252342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
  char str3[50];
  char str4[100];
  int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
  int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(sprintf_17) {
  char str1[1000];
  char str2[1000];
  short h = 34;
  int r1 = sprintf(
      str1, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(
      str2, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sprintf_simple_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "This is a simple value %d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_precise_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_minus_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+12d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_padding_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%012i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_star_width_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0*d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_star_precision_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.*i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_many_flags_many_ints) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char format[] = "%0.*i %d %4.*i %013d %d";
  int val = 69;
  ck_assert_int_eq(
      s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581),
      sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_long_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int res1 = 0, res2 = 0;
  char *format = "%+5.31li";
  long int val = 698518581899;
  res1 = s21_sprintf(str1, format, val);
  res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_short_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16.9hi";
  short int val = 6958;
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, format, val);
  res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_another_long_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.*ld";
  long val = 8581385185;
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, format, 2, val);
  res2 = sprintf(str2, format, 2, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_precision_zero_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.0d";
  int val = 0;
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, format, val);
  res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_space_flag_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% d";
  int val = 0;
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, format, val);
  res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% 5.51u";
  unsigned int val = 14140;
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, format, val);
  res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hu";
  unsigned short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  int res1 = 0, res2 = 0;
  res1 = s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
  res2 = sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
                 (unsigned)14414, (unsigned)9681);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_hash) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#o";
  int val = 57175;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hd";
  short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo";
  long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo, %o, %ho, %.5o, %5.o";
  long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_octal) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo";
  long int val = 84518;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5x%#010x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val),
                   sprintf(str2, format, val, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-10x%x%X%#x%#X%5.5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val, val, val, val, val),
                   sprintf(str2, format, val, val, val, val, val, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-5.10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#x";
  unsigned val = 0;
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#x";
  unsigned val = 18571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_short) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#hx";
  unsigned short val = 12352;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#lx";
  unsigned long val = 18571757371571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_one_longer_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#2x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_hex_two_longer_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#30x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%c";
  char val = 'X';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_one_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% -5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                   sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_many_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_long) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  int res1 = s21_sprintf(str1, format, val, s1, s2, s3);
  int res2 = sprintf(str2, format, val, s1, s2, s3);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_ptr) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_ptr_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_ptr_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_null_ptr) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%p";
  void *p = (void *)123456789;
  ck_assert_int_eq(s21_sprintf(str1, format, p), sprintf(str2, format, p));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_width_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *val = "kjafdiuhfjahfjdahf";
  char *format = "%120s";
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_n_specifier) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int ret = 0;
  char *format = "Hello darkness my old friend %n";
  ck_assert_int_eq(s21_sprintf(str1, format, &ret),
                   sprintf(str2, format, &ret));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%10Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.13Lf%010.13Lf";
  long double val = 15.35;
  long double val1 = 1.12335;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1),
                   sprintf(str2, format, val, val1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_huge_negative) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.13Lf";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0f %.lf %Lf %f %lf %Lf";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 9851.51351;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.13Le";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Le";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_precision_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Le";
  long double val = 15.000009121;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_precision_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.13Le%010.13Le";
  long double val = 0.000000000000000123;
  long double val1 = 10.0092123;
  int res1 = s21_sprintf(str1, format, val, val1);
  int res2 = sprintf(str2, format, val, val1);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_precision_huge_negative) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.13Le";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_huge) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Le";
  long double val = 72537572375.1431341;
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%015E";
  float val = 0;
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15e";
  float val = 15;
  int res1 = s21_sprintf(str1, format, val);
  int res2 = sprintf(str2, format, val);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_e_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0e %.le %Le %e %le %Le";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 0.094913941;
  long double val5 = 95919539159.53151351131;
  int res1 = s21_sprintf(str1, format, val, val1, val2, val3, val4, val5);
  int res2 = sprintf(str2, format, val, val1, val2, val3, val4, val5);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_E_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.14LE";
  long double val = 4134121;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_all_empty) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_empty_format_and_parameters) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_char) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                   sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
                   sprintf(str2, "%s", "Drop Sega PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_string) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
      sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d", 666), sprintf(str2, "%d", 666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
                   sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i", -0), sprintf(str2, "%i", -0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_int) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -999, 0, 666, -100),
                   sprintf(str2, "%i%i%i%i", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_float) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                   sprintf(str2, "%f", 0.0001));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_float) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(
      s21_sprintf(str1, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001),
      sprintf(str2, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                   sprintf(str2, "%u", (unsigned)100));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_unsigned_dec) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100),
                   sprintf(str2, "%u%u%u%u", (unsigned)999, (unsigned)0,
                           (unsigned)666, (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_char_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_char_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'),
                   sprintf(str2, "%-8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_char_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'),
      sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// START HEX TEST
START_TEST(sprintf_test_one_hex_lower) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "%x", (unsigned)INT32_MIN),
                   sprintf(str2, "%x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", INT32_MAX),
                   sprintf(str2, "%x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_hex_upper) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%X", (unsigned)INT32_MIN),
                   sprintf(str2, "%X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", INT32_MAX),
                   sprintf(str2, "%X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_lower) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_upper) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST
// // END HEX TEST

// START HEX WITH ALIGNMENT
START_TEST(sprintf_test_one_hex_lower_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-3x", (unsigned)INT32_MIN),
                   sprintf(str2, "%-3x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", 0), sprintf(str2, "%-3x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", INT32_MAX),
                   sprintf(str2, "%-3x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_hex_lower_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%13x", (unsigned)INT32_MIN),
                   sprintf(str2, "%13x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", 0), sprintf(str2, "%13x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", INT32_MAX),
                   sprintf(str2, "%13x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_hex_upper_with_alignment_left) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MIN),
                   sprintf(str2, "%-60X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", 0), sprintf(str2, "%-60X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MAX),
                   sprintf(str2, "%-60X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_hex_upper_with_alignment_right) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%7X", (unsigned)INT32_MIN),
                   sprintf(str2, "%7X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", 0), sprintf(str2, "%7X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", INT32_MAX),
                   sprintf(str2, "%7X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_lower_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_upper_with_alignment) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(
      s21_sprintf(str1, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST
// START HEX WITH ALIGNMENT

// START HEX TEST WITH #
START_TEST(sprintf_test_one_hex_with_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MIN),
                   sprintf(str2, "%#x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", 0), sprintf(str2, "%#x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MAX),
                   sprintf(str2, "%#x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_hex_upper_with_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MIN),
                   sprintf(str2, "%#X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", 0), sprintf(str2, "%#X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MAX),
                   sprintf(str2, "%#X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_lower_with_hashtag_and_alignm) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_upper_with_hashtag_and_alignm) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST
// END HEX TEST WITH #

// START HEX TEST with width *
START_TEST(sprintf_test_one_hex_lower_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MIN),
                   sprintf(str2, "%*x", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, 0),
                   sprintf(str2, "%*x", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MAX),
                   sprintf(str2, "%*x", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_hex_upper_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MIN),
                   sprintf(str2, "%*X", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, 0),
                   sprintf(str2, "%*X", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MAX),
                   sprintf(str2, "%*X", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_lower_with_width_star_and_align_and_hashtag) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#*x%*x%-12x%3x%*x", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*x%*x%-12x%3x%*x", 9, 127312897, -0, -1,
                           199, -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_upper_with_width_star) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1, 199,
                           -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST
// END HEX TEST WITH Width *

// START HEX TEST WITH precision
START_TEST(sprintf_test_one_hex_lower_with_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  int a = s21_sprintf(str1, "%*.6x", 11, 0);
  int b = sprintf(str2, "%*.6x", 11, 0);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_hex_upper_with_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  int a = s21_sprintf(str1, "%*.6X", 11, INT32_MIN);
  int b = sprintf(str2, "%*.6X", 11, (unsigned)INT32_MIN);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_lower_with_precision_and_other) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int a = s21_sprintf(
      str1, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
      4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
  int b = sprintf(str2, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x",
                  3, 126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9,
                  41, -41, 33);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_hex_upper_with_precision_and_other) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X",
                  3, -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
                  41, -41, 33),
      sprintf(str2, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
              -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9, 41,
              -41, 33));
  ck_assert_str_eq(str1, str2);
}
END_TEST
// END HEX TEST WITH precision

// START HEX TEST WITH Length
START_TEST(sprintf_test_one_hex_lower_with_length) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int res1 = s21_sprintf(str1, "%hx", -11);
  int res2 = sprintf(str2, "%hx", (unsigned short)-11);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  int res3 = s21_sprintf(str1, "%hx", 0);
  int res4 = sprintf(str2, "%hx", (unsigned short)0);
  ck_assert_int_eq(res3, res4);
  ck_assert_str_eq(str1, str2);

  int res5 = s21_sprintf(str1, "%hx", 11);
  int res6 = sprintf(str2, "%hx", (unsigned short)11);
  ck_assert_int_eq(res5, res6);
  ck_assert_str_eq(str1, str2);

  long unsigned int val = INT32_MAX;
  int res7 = s21_sprintf(str1, "%lx", val);
  int res8 = sprintf(str2, "%lx", val);
  ck_assert_int_eq(res7, res8);
  ck_assert_str_eq(str1, str2);
  long unsigned int v = 0;
  int res9 = s21_sprintf(str1, "%lx", v);
  int res10 = sprintf(str2, "%lx", v);
  ck_assert_int_eq(res9, res10);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%10ld";

  ck_assert_int_eq(s21_sprintf(str1, format, 1), sprintf(str2, format, 1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%1.1f";

  ck_assert_int_eq(s21_sprintf(str1, format, 1.1), sprintf(str2, format, 1.1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%8.3c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+5.5d aboba %10.s";
  char str[] = "abiba";

  int val = 10000;
  int a = s21_sprintf(str1, format, val, str);
  int b = sprintf(str2, format, val, str);
  ck_assert_int_eq(a, b);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.7f";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.123456),
                   sprintf(str2, format, 11.123456));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.4s";

  int res1 = s21_sprintf(str1, format, "aboba floppa");
  int res2 = sprintf(str2, format, "aboba floppa");
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%6.6u";

  ck_assert_int_eq(s21_sprintf(str1, format, 12341151),
                   sprintf(str2, format, 12341151));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%li%ld%lu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666666666666, 777, 111),
                   sprintf(str2, format, 666666666666, 777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%hi%hd%hu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666, -777, 111),
                   sprintf(str2, format, 666, -777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+li%+lu%+d%+lf";

  int res1 = s21_sprintf(str1, format, -123, 321, -5555, -1213.123);
  int res2 = sprintf(str2, format, -123, 321, -5555, -1213.123);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-11.11li%-35.5lu%-3.5ld%33.13Lf";
  long double k = 333.33213;
  int res1 = s21_sprintf(str1, format, 66666666666, 5555555555, 44444444444, k);
  int res2 = sprintf(str2, format, 66666666666, 5555555555, 44444444444, k);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0.0li% 0.0lu% 0.0ld % 0.0lf";
  int res1 = s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232);
  int res2 = sprintf(str2, format, 1, 222, 33333333333, -166513.1232);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0.0hi% 0.0hu% 0.0hd % 0.0hf";

  int res1 = s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232);
  int res2 = sprintf(str2, format, 1, 222, 33333333333, -166513.1232);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba likes floppa"),
                   sprintf(str2, format, "aboba likes floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s% c";

  ck_assert_int_eq(s21_sprintf(str1, format, "", 'f'),
                   sprintf(str2, format, "", 'f'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%210s";

  ck_assert_int_eq(s21_sprintf(str1, format, "AHHAHAHA\0AHHAHAHAH"),
                   sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf20) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-115s";

  ck_assert_int_eq(s21_sprintf(str1, format, "Nick her"),
                   sprintf(str2, format, "Nick her"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf24) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+2.1c%+4.2d%+5.4i%+10.2f%+55.55s%+1.1u";

  int res1 = s21_sprintf(str1, format, 'f', 21, 42, 666.666,
                         "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11);
  int res2 = sprintf(str2, format, 'f', 21, 42, 666.666,
                     "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf25) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 121.123),
                   sprintf(str2, format, 121.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf26) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%%"), sprintf(str2, "%%"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf27) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%%%%%%%%"), sprintf(str2, "%%%%%%%%"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf28) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int n1;
  int n2;
  int a = s21_sprintf(str1, "%d%n", 123, &n1);
  int b = sprintf(str2, "%d%n", 123, &n2);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf29) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.111),
                   sprintf(str2, format, 111.111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf30) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.1d";

  ck_assert_int_eq(s21_sprintf(str1, format, 111), sprintf(str2, format, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf31) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e";
  double x = 111;
  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf32) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e%e%e%e";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.111, 222.2222, 666., -555.125),
                   sprintf(str2, format, 11.111, 222.2222, 666., -555.125));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf33) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%Le";
  long double x = 122.1231;

  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf35) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.10e";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.184314818),
                   sprintf(str2, format, 111.184314818));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf36) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.3e%3.2e%lf";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.000111, 111.555, 1.999),
                   sprintf(str2, format, 0.000111, 111.555, 1.999));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf37) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.666666),
                   sprintf(str2, format, 0.666666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf38) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E%E%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.0000999, 111.9999, 6.666),
                   sprintf(str2, format, 0.0000999, 111.9999, 6.666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf39) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e ABOBA %Lf %Lf %Le";
  long double c = 848181;
  long double a = 0.00000001;
  long double b = 1111111.11;
  ck_assert_int_eq(s21_sprintf(str1, format, 123.123, a, b, c),
                   sprintf(str2, format, 123.123, a, b, c));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf40) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#e Floppa %#E%#f% 15f% -15f% 015f";

  ck_assert_int_eq(
      s21_sprintf(str1, format, 123.111, 0.0000999, 0.555, 2.8374, 3.983,
                  4.92837),
      sprintf(str2, format, 123.111, 0.0000999, 0.555, 2.8374, 3.983, 4.92837));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf41) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.Lf";
  long double a = 7.9418438184;

  ck_assert_int_eq(s21_sprintf(str1, format, a), sprintf(str2, format, a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf42) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#5p";
  int a = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, &a), sprintf(str2, format, &a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf43) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5o";

  ck_assert_int_eq(s21_sprintf(str1, format, 12345),
                   sprintf(str2, format, 12345));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf44) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#5lX";
  long hex = 314818438141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_trailing_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g%.g";
  double hex = 0.50300;
  double hex2 = 0.99999999;
  ck_assert_int_eq(s21_sprintf(str1, format, hex, hex2),
                   sprintf(str2, format, hex, hex2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_large) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g%.g%.g%.g%.g";
  double hex = 5131.43141;
  double hex2 = 0.909999999;
  double hex3 = 0.0000009900999999;
  double hex4 = 0.0090999999;
  double hex5 = 0.00009999999;
  ck_assert_int_eq(s21_sprintf(str1, format, hex, hex2, hex3, hex4, hex5),
                   sprintf(str2, format, hex, hex2, hex3, hex4, hex5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_small) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g%.g";
  double hex = 0.123000;
  double hex2 = 0.0000001239999999;
  ck_assert_int_eq(s21_sprintf(str1, format, hex, hex2),
                   sprintf(str2, format, hex, hex2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5g% +10.4g";
  double hex = 0.123000;
  double hex2 = 0.12300;
  ck_assert_int_eq(s21_sprintf(str1, format, hex, hex2),
                   sprintf(str2, format, hex, hex2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_precision_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.0g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_precision_missing) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_many_zeroes_in_front) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.g";
  double hex = 0.0004;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_one_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0;
  int res1 = s21_sprintf(str1, format, hex);
  int res2 = sprintf(str2, format, hex);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5g";
  double hex = 0;
  int res1 = s21_sprintf(str1, format, hex);
  int res2 = sprintf(str2, format, hex);
  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_mantiss) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_mantiss_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.8g";
  double hex = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_short_no_mantiss) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g% 010g% 010g% 10g% 30g%.g%g%.1g%.4g";
  double hex = 0.005;
  double hex2 = 0.00000053728;
  int res1 = s21_sprintf(str1, format, hex, hex2, hex, hex2, hex2, 1.0, 5.01,
                         hex, 50004.09);
  int res2 = sprintf(str2, format, hex, hex2, hex, hex2, hex2, 1.0, 5.01, hex,
                     50004.09);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_LG) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%LG";
  long double hex = 0.000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_g_many) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%LG %g %G %Lg %.5g";
  long double hex = 0.000005;
  double hex1 = 41.1341;
  double hex2 = 848.9000;
  long double hex3 = 0.0843;
  double hex4 = 0.0005;
  double hex5 = 0.8481481;
  ck_assert_int_eq(s21_sprintf(str1, format, hex, hex1, hex2, hex3, hex4, hex5),
                   sprintf(str2, format, hex, hex1, hex2, hex3, hex4, hex5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_trim_test_4) {
  char test_str[50] = {" /***% Hello world ***"};
  char trims[50] = {
      "*"
      " "
      "/"
      "%"
      "<^"};
  char out_expected[50] = {"Hello world"};
  char *out_s21 = s21_trim(test_str, trims);
  ck_assert_pstr_eq(out_s21, out_expected);
  if (out_s21) free(out_s21);
}
END_TEST

int main(void) {
  setlocale(LC_ALL, "RU");
  int number_failed;
  Suite *s = suite_create("s21_string");

  TCase *s21_string_h = tcase_create("s21_string_h");
  SRunner *sr = srunner_create(s);

  suite_add_tcase(s, s21_string_h);
  tcase_add_test(s21_string_h, sscanf_EOF1);
  tcase_add_test(s21_string_h, sscanf_EOF2);
  tcase_add_test(s21_string_h, sscanf_EOF3);
  tcase_add_test(s21_string_h, sscanf_EOF4);

  tcase_add_test(s21_string_h, sscanf_floats1);
  tcase_add_test(s21_string_h, sscanf_floats2);
  tcase_add_test(s21_string_h, sscanf_floats3);
  tcase_add_test(s21_string_h, sscanf_floats4);
  tcase_add_test(s21_string_h, sscanf_floats5);

  tcase_add_test(s21_string_h, sscanf_floats_sci1);
  tcase_add_test(s21_string_h, sscanf_floats_sci2);
  tcase_add_test(s21_string_h, sscanf_floats_sci3);
  tcase_add_test(s21_string_h, sscanf_floats_sci4);
  tcase_add_test(s21_string_h, sscanf_floats_sci5);

  tcase_add_test(s21_string_h, sscanf_pointer1);
  tcase_add_test(s21_string_h, sscanf_pointer2);
  tcase_add_test(s21_string_h, sscanf_pointer3);
  tcase_add_test(s21_string_h, sscanf_pointer4);

  tcase_add_test(s21_string_h, sscanf_perc1);
  tcase_add_test(s21_string_h, sscanf_perc2);
  tcase_add_test(s21_string_h, sscanf_perc3);
  tcase_add_test(s21_string_h, sscanf_perc5);

  tcase_add_test(s21_string_h, sscanf_hard1);
  tcase_add_test(s21_string_h, sscanf_hard3);
  tcase_add_test(s21_string_h, sscanf_hard4);
  tcase_add_test(s21_string_h, sscanf_hard5);

  tcase_add_test(s21_string_h, sscanf_mixed_ptrs1);
  tcase_add_test(s21_string_h, sscanf_mixed_ptrs2);
  tcase_add_test(s21_string_h, sscanf_mixed_ptrs3);
  tcase_add_test(s21_string_h, sscanf_mixed_ptrs4);
  tcase_add_test(s21_string_h, sscanf_mixed_ptrs5);

  tcase_add_test(s21_string_h, sscanf_only_ints1);
  tcase_add_test(s21_string_h, sscanf_only_ints2);
  tcase_add_test(s21_string_h, sscanf_only_ints4);

  tcase_add_test(s21_string_h, sscanf_ints_nwidth1);
  tcase_add_test(s21_string_h, sscanf_ints_nwidth2);
  tcase_add_test(s21_string_h, sscanf_ints_nwidth4);

  tcase_add_test(s21_string_h, sscanf_signed_ints1);
  tcase_add_test(s21_string_h, sscanf_signed_ints2);
  tcase_add_test(s21_string_h, sscanf_signed_ints3);
  tcase_add_test(s21_string_h, sscanf_signed_ints4);

  tcase_add_test(s21_string_h, sscanf_spec_i_int1);
  tcase_add_test(s21_string_h, sscanf_spec_i_int2);
  tcase_add_test(s21_string_h, sscanf_spec_i_int3);

  tcase_add_test(s21_string_h, sscanf_only_chars1);
  tcase_add_test(s21_string_h, sscanf_only_chars2);
  tcase_add_test(s21_string_h, sscanf_only_chars3);
  tcase_add_test(s21_string_h, sscanf_only_chars4);
  tcase_add_test(s21_string_h, sscanf_only_chars5);

  tcase_add_test(s21_string_h, sscanf_special_symbols_as_chars1);
  tcase_add_test(s21_string_h, sscanf_special_symbols_as_chars2);
  tcase_add_test(s21_string_h, sscanf_special_symbols_as_chars3);

  tcase_add_test(s21_string_h, sscanf_chars_flags1);
  tcase_add_test(s21_string_h, sscanf_chars_flags2);
  tcase_add_test(s21_string_h, sscanf_chars_flags3);
  tcase_add_test(s21_string_h, sscanf_chars_flags4);
  tcase_add_test(s21_string_h, sscanf_chars_flags5);

  tcase_add_test(s21_string_h, sscanf_chars_aster1);
  tcase_add_test(s21_string_h, sscanf_chars_aster2);

  tcase_add_test(s21_string_h, sscanf_spec_i_oct1);
  tcase_add_test(s21_string_h, sscanf_spec_i_oct2);

  tcase_add_test(s21_string_h, sscanf_spec_i_hex1);
  tcase_add_test(s21_string_h, sscanf_spec_i_hex2);

  tcase_add_test(s21_string_h, sscanf_strings1);
  tcase_add_test(s21_string_h, sscanf_strings2);
  tcase_add_test(s21_string_h, sscanf_strings3);
  tcase_add_test(s21_string_h, sscanf_strings4);
  tcase_add_test(s21_string_h, sscanf_strings5);
  tcase_add_test(s21_string_h, sscanf_strings6);
  tcase_add_test(s21_string_h, sscanf_strings_mixed1);
  tcase_add_test(s21_string_h, sscanf_strings_mixed2);
  tcase_add_test(s21_string_h, sscanf_strings_mixed3);

  tcase_add_test(s21_string_h, sscanf_n1);
  tcase_add_test(s21_string_h, sscanf_n2);
  tcase_add_test(s21_string_h, sscanf_n3);
  tcase_add_test(s21_string_h, sscanf_n4);
  tcase_add_test(s21_string_h, sscanf_n5);

  tcase_add_test(s21_string_h, sscanf_uint1);
  tcase_add_test(s21_string_h, sscanf_uint2);
  tcase_add_test(s21_string_h, sscanf_uint4);
  tcase_add_test(s21_string_h, sscanf_uint5);

  tcase_add_test(s21_string_h, sscanf_upeer_hex_overflow);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_0x);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_0X);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_empty);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_fail);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_spaces_tabs_sns);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_short);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_long);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_2x);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_nohex);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_lower);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_sign);
  tcase_add_test(s21_string_h, sscanf_upeer_hex_base_version);
  tcase_add_test(s21_string_h, upper_hex_len);

  tcase_add_test(s21_string_h, sscanf_lower_hex_base_version);
  tcase_add_test(s21_string_h, sscanf_lower_hex_overflow);
  tcase_add_test(s21_string_h, sscanf_lower_hex_0x);
  tcase_add_test(s21_string_h, sscanf_lower_hex_0X);
  tcase_add_test(s21_string_h, sscanf_lower_hex_empty);
  tcase_add_test(s21_string_h, sscanf_lower_hex_fail);
  tcase_add_test(s21_string_h, sscanf_lower_hex_spaces_tabs_sns);
  tcase_add_test(s21_string_h, sscanf_lower_hex_short);
  tcase_add_test(s21_string_h, sscanf_lower_hex_long);
  tcase_add_test(s21_string_h, sscanf_lower_hex_longlong);
  tcase_add_test(s21_string_h, sscanf_lower_hex_2x);
  tcase_add_test(s21_string_h, sscanf_lower_hex_star);
  tcase_add_test(s21_string_h, sscanf_lower_hex_nohex);
  tcase_add_test(s21_string_h, sscanf_lower_hex_lower);
  tcase_add_test(s21_string_h, sscanf_lower_hex_sign);
  tcase_add_test(s21_string_h, sscanf_lower_hex_len);

  tcase_add_test(s21_string_h, sscanf_octal_base_version);
  tcase_add_test(s21_string_h, sscanf_octal_overflow);
  tcase_add_test(s21_string_h, sscanf_octal_0x);
  tcase_add_test(s21_string_h, sscanf_octal_0X);
  tcase_add_test(s21_string_h, sscanf_octal_empty);
  tcase_add_test(s21_string_h, sscanf_octal_fail);
  tcase_add_test(s21_string_h, sscanf_octal_spaces_tabs_sns);
  tcase_add_test(s21_string_h, sscanf_octal_short);
  tcase_add_test(s21_string_h, sscanf_octal_long);
  tcase_add_test(s21_string_h, sscanf_octal_2x);
  tcase_add_test(s21_string_h, sscanf_octal_star);
  tcase_add_test(s21_string_h, sscanf_octal_nohex);
  tcase_add_test(s21_string_h, sscanf_octal_lower);
  tcase_add_test(s21_string_h, sscanf_octal_sign);
  tcase_add_test(s21_string_h, sscanf_octal_len);

  tcase_add_test(s21_string_h, sscanf_buff1);
  tcase_add_test(s21_string_h, sscanf_buff2);
  tcase_add_test(s21_string_h, sscanf_buff3);

  tcase_add_test(s21_string_h, s21_memchr_test);
  tcase_add_test(s21_string_h, s21_memcmp_test);
  tcase_add_test(s21_string_h, s21_memcpy_test);
  tcase_add_test(s21_string_h, s21_memmove_test);
  tcase_add_test(s21_string_h, s21_memset_test);
  tcase_add_test(s21_string_h, s21_strlen_test);
  tcase_add_test(s21_string_h, s21_strcmp_test);
  tcase_add_test(s21_string_h, s21_strncmp_test);
  tcase_add_test(s21_string_h, s21_strchr_test);
  tcase_add_test(s21_string_h, s21_strspn_test);
  tcase_add_test(s21_string_h, s21_strcspn_test);
  tcase_add_test(s21_string_h, s21_strpbrk_test);
  tcase_add_test(s21_string_h, s21_strrchr_test);
  tcase_add_test(s21_string_h, s21_strstr_test);
  tcase_add_test(s21_string_h, s21_strtok_test);
  tcase_add_test(s21_string_h, s21_strncpy_test);
  tcase_add_test(s21_string_h, s21_strcat_test);
  tcase_add_test(s21_string_h, s21_strncat_test);
  tcase_add_test(s21_string_h, s21_strcpy_test);
  tcase_add_test(s21_string_h, s21_strerror_test);
  tcase_add_test(s21_string_h, s21_to_upper_test_1);
  tcase_add_test(s21_string_h, s21_to_upper_test_2);
  tcase_add_test(s21_string_h, s21_to_upper_test_3);
  tcase_add_test(s21_string_h, s21_to_lower_test_1);
  tcase_add_test(s21_string_h, s21_to_lower_test_2);
  tcase_add_test(s21_string_h, s21_to_lower_test_3);
  tcase_add_test(s21_string_h, s21_insert_test_1);
  tcase_add_test(s21_string_h, s21_insert_test_2);
  tcase_add_test(s21_string_h, s21_insert_test_3);
  tcase_add_test(s21_string_h, s21_insert_test_4);
  tcase_add_test(s21_string_h, s21_insert_test_5);
  tcase_add_test(s21_string_h, s21_trim_test_1);
  tcase_add_test(s21_string_h, s21_trim_test_2);
  tcase_add_test(s21_string_h, s21_trim_test_3);
  tcase_add_test(s21_string_h, s21_trim_test_4);
  tcase_add_test(s21_string_h, sprintf_1);
  tcase_add_test(s21_string_h, sprintf_2);
  tcase_add_test(s21_string_h, sprintf_3);
  tcase_add_test(s21_string_h, sprintf_4);
  tcase_add_test(s21_string_h, sprintf_5);
  tcase_add_test(s21_string_h, sprintf_6);
  tcase_add_test(s21_string_h, sprintf_7);
  tcase_add_test(s21_string_h, sprintf_8);
  tcase_add_test(s21_string_h, sprintf_9);
  tcase_add_test(s21_string_h, sprintf_10);
  tcase_add_test(s21_string_h, sprintf_11);
  tcase_add_test(s21_string_h, sprintf_12);
  tcase_add_test(s21_string_h, sprintf_13);
  tcase_add_test(s21_string_h, sprintf_14);
  tcase_add_test(s21_string_h, sprintf_15);
  tcase_add_test(s21_string_h, sprintf_16);
  tcase_add_test(s21_string_h, sprintf_17);
  tcase_add_test(s21_string_h, sprintf_simple_int);
  tcase_add_test(s21_string_h, sprintf_precise_int);
  tcase_add_test(s21_string_h, sprintf_width_int);
  tcase_add_test(s21_string_h, sprintf_minus_width_int);
  tcase_add_test(s21_string_h, sprintf_plus_width_int);
  tcase_add_test(s21_string_h, sprintf_padding_int);
  tcase_add_test(s21_string_h, sprintf_star_width_int);
  tcase_add_test(s21_string_h, sprintf_star_precision_int);
  tcase_add_test(s21_string_h, sprintf_many_flags_many_ints);
  tcase_add_test(s21_string_h, sprintf_flags_long_int);
  tcase_add_test(s21_string_h, sprintf_flags_short_int);
  tcase_add_test(s21_string_h, sprintf_flags_another_long_int);
  tcase_add_test(s21_string_h, sprintf_zero_precision_zero_int);
  tcase_add_test(s21_string_h, sprintf_space_flag_int);
  tcase_add_test(s21_string_h, sprintf_unsigned_val);
  tcase_add_test(s21_string_h, sprintf_unsigned_val_width);
  tcase_add_test(s21_string_h, sprintf_unsigned_val_flags);
  tcase_add_test(s21_string_h, sprintf_unsigned_val_precision);
  tcase_add_test(s21_string_h, sprintf_unsigned_val_many_flags);
  tcase_add_test(s21_string_h, sprintf_unsigned_val_short);
  tcase_add_test(s21_string_h, sprintf_unsigned_val_long);
  tcase_add_test(s21_string_h, sprintf_unsigned_val_many);
  tcase_add_test(s21_string_h, sprintf_octal_width);
  tcase_add_test(s21_string_h, sprintf_octal_flags);
  tcase_add_test(s21_string_h, sprintf_octal_precision);
  tcase_add_test(s21_string_h, sprintf_octal_many_flags);
  tcase_add_test(s21_string_h, sprintf_octal_short);
  tcase_add_test(s21_string_h, sprintf_octal_long);
  tcase_add_test(s21_string_h, sprintf_octal_many);
  tcase_add_test(s21_string_h, sprintf_octal);
  tcase_add_test(s21_string_h, sprintf_octal_zero);
  tcase_add_test(s21_string_h, sprintf_octal_hash);
  tcase_add_test(s21_string_h, sprintf_unsigned_zero);
  tcase_add_test(s21_string_h, sprintf_hex_width);
  tcase_add_test(s21_string_h, sprintf_hex_flags);
  tcase_add_test(s21_string_h, sprintf_hex_precision);
  tcase_add_test(s21_string_h, sprintf_hex_many);
  tcase_add_test(s21_string_h, sprintf_hex_many_flags);
  tcase_add_test(s21_string_h, sprintf_hex_zero);
  tcase_add_test(s21_string_h, sprintf_hex_huge);
  tcase_add_test(s21_string_h, sprintf_hex_short);
  tcase_add_test(s21_string_h, sprintf_hex_long);
  tcase_add_test(s21_string_h, sprintf_hex_one_longer_width);
  tcase_add_test(s21_string_h, sprintf_hex_two_longer_width);
  tcase_add_test(s21_string_h, sprintf_one_char);
  tcase_add_test(s21_string_h, sprintf_one_precision);
  tcase_add_test(s21_string_h, sprintf_one_flags);
  tcase_add_test(s21_string_h, sprintf_one_width);
  tcase_add_test(s21_string_h, sprintf_one_many);
  tcase_add_test(s21_string_h, sprintf_one_many_flags);
  tcase_add_test(s21_string_h, sprintf_string);
  tcase_add_test(s21_string_h, sprintf_string_precision);
  tcase_add_test(s21_string_h, sprintf_string_width);
  tcase_add_test(s21_string_h, sprintf_string_flags);
  tcase_add_test(s21_string_h, sprintf_string_long);
  tcase_add_test(s21_string_h, sprintf_string_many);
  tcase_add_test(s21_string_h, sprintf_ptr);
  tcase_add_test(s21_string_h, sprintf_ptr_width);
  tcase_add_test(s21_string_h, sprintf_ptr_precision);
  tcase_add_test(s21_string_h, sprintf_null_ptr);
  tcase_add_test(s21_string_h, sprintf_n_specifier);
  tcase_add_test(s21_string_h, sprintf_string_width_huge);
  tcase_add_test(s21_string_h, sprintf_float_precision);
  tcase_add_test(s21_string_h, sprintf_float_width);
  tcase_add_test(s21_string_h, sprintf_float_precision_zero);
  tcase_add_test(s21_string_h, sprintf_float_precision_empty);
  tcase_add_test(s21_string_h, sprintf_float_precision_huge);
  tcase_add_test(s21_string_h, sprintf_float_precision_huge_negative);
  tcase_add_test(s21_string_h, sprintf_float_huge);
  tcase_add_test(s21_string_h, sprintf_float_flags);
  tcase_add_test(s21_string_h, sprintf_float_many);
  tcase_add_test(s21_string_h, sprintf_e_precision);
  tcase_add_test(s21_string_h, sprintf_e_precision_zero);
  tcase_add_test(s21_string_h, sprintf_e_precision_empty);
  tcase_add_test(s21_string_h, sprintf_e_precision_huge);
  tcase_add_test(s21_string_h, sprintf_e_precision_huge_negative);
  tcase_add_test(s21_string_h, sprintf_e_huge);
  tcase_add_test(s21_string_h, sprintf_e_many);
  tcase_add_test(s21_string_h, sprintf_e_width);
  tcase_add_test(s21_string_h, sprintf_e_flags);
  tcase_add_test(s21_string_h, sprintf_E_int);
  tcase_add_test(s21_string_h, sprintf_all_empty);
  tcase_add_test(s21_string_h, sprintf_empty_format_and_parameters);
  tcase_add_test(s21_string_h, sprintf_test_one_char);
  tcase_add_test(s21_string_h, sprintf_test_many_char);
  tcase_add_test(s21_string_h, sprintf_test_one_string);
  tcase_add_test(s21_string_h, sprintf_test_many_string);
  tcase_add_test(s21_string_h, sprintf_test_one_dec);
  tcase_add_test(s21_string_h, sprintf_test_many_dec);
  tcase_add_test(s21_string_h, sprintf_test_one_int);
  tcase_add_test(s21_string_h, sprintf_test_many_int);
  tcase_add_test(s21_string_h, sprintf_test_one_float);
  tcase_add_test(s21_string_h, sprintf_test_many_float);
  tcase_add_test(s21_string_h, sprintf_test_one_unsigned_dec);
  tcase_add_test(s21_string_h, sprintf_test_many_unsigned_dec);
  tcase_add_test(s21_string_h, sprintf_test_one_char_with_alignment_left);
  tcase_add_test(s21_string_h, sprintf_test_one_char_with_alignment_right);
  tcase_add_test(s21_string_h, sprintf_test_many_char_with_alignment);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_lower);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_upper);
  tcase_add_test(s21_string_h, sprintf_test_many_hex_lower);
  tcase_add_test(s21_string_h, sprintf_test_many_hex_upper);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_lower_with_alignment_left);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_lower_with_alignment_right);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_upper_with_alignment_left);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_upper_with_alignment_right);
  tcase_add_test(s21_string_h, sprintf_test_many_hex_lower_with_alignment);
  tcase_add_test(s21_string_h, sprintf_test_many_hex_upper_with_alignment);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_with_hashtag);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_upper_with_hashtag);
  tcase_add_test(s21_string_h,
                 sprintf_test_many_hex_lower_with_hashtag_and_alignm);
  tcase_add_test(s21_string_h,
                 sprintf_test_many_hex_upper_with_hashtag_and_alignm);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_lower_with_width_star);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_upper_with_width_star);
  tcase_add_test(
      s21_string_h,
      sprintf_test_many_hex_lower_with_width_star_and_align_and_hashtag);
  tcase_add_test(s21_string_h, sprintf_test_many_hex_upper_with_width_star);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_lower_with_precision);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_upper_with_precision);
  tcase_add_test(s21_string_h,
                 sprintf_test_many_hex_lower_with_precision_and_other);
  tcase_add_test(s21_string_h,
                 sprintf_test_many_hex_upper_with_precision_and_other);
  tcase_add_test(s21_string_h, sprintf_test_one_hex_lower_with_length);
  tcase_add_test(s21_string_h, sprintf_test_sprintf1);
  tcase_add_test(s21_string_h, sprintf_test_sprintf2);
  tcase_add_test(s21_string_h, sprintf_test_sprintf3);
  tcase_add_test(s21_string_h, sprintf_test_sprintf4);
  tcase_add_test(s21_string_h, sprintf_test_sprintf6);
  tcase_add_test(s21_string_h, sprintf_test_sprintf7);
  tcase_add_test(s21_string_h, sprintf_test_sprintf8);
  tcase_add_test(s21_string_h, sprintf_test_sprintf9);
  tcase_add_test(s21_string_h, sprintf_test_sprintf10);
  tcase_add_test(s21_string_h, sprintf_test_sprintf11);
  tcase_add_test(s21_string_h, sprintf_test_sprintf12);
  tcase_add_test(s21_string_h, sprintf_test_sprintf14);
  tcase_add_test(s21_string_h, sprintf_test_sprintf15);
  tcase_add_test(s21_string_h, sprintf_test_sprintf16);
  tcase_add_test(s21_string_h, sprintf_test_sprintf17);
  tcase_add_test(s21_string_h, sprintf_test_sprintf18);
  tcase_add_test(s21_string_h, sprintf_test_sprintf19);
  tcase_add_test(s21_string_h, sprintf_test_sprintf20);
  tcase_add_test(s21_string_h, sprintf_test_sprintf24);
  tcase_add_test(s21_string_h, sprintf_test_sprintf25);
  tcase_add_test(s21_string_h, sprintf_test_sprintf26);
  tcase_add_test(s21_string_h, sprintf_test_sprintf27);
  tcase_add_test(s21_string_h, sprintf_test_sprintf28);
  tcase_add_test(s21_string_h, sprintf_test_sprintf29);
  tcase_add_test(s21_string_h, sprintf_test_sprintf30);
  tcase_add_test(s21_string_h, sprintf_test_sprintf31);
  tcase_add_test(s21_string_h, sprintf_test_sprintf32);
  tcase_add_test(s21_string_h, sprintf_test_sprintf33);
  tcase_add_test(s21_string_h, sprintf_test_sprintf35);
  tcase_add_test(s21_string_h, sprintf_test_sprintf36);
  tcase_add_test(s21_string_h, sprintf_test_sprintf37);
  tcase_add_test(s21_string_h, sprintf_test_sprintf38);
  tcase_add_test(s21_string_h, sprintf_test_sprintf39);
  tcase_add_test(s21_string_h, sprintf_test_sprintf40);
  tcase_add_test(s21_string_h, sprintf_test_sprintf41);
  tcase_add_test(s21_string_h, sprintf_test_sprintf42);
  tcase_add_test(s21_string_h, sprintf_test_sprintf43);
  tcase_add_test(s21_string_h, sprintf_test_sprintf44);
  tcase_add_test(s21_string_h, sprintf_g_trailing_zero);
  tcase_add_test(s21_string_h, sprintf_g_large);
  tcase_add_test(s21_string_h, sprintf_g_small);
  tcase_add_test(s21_string_h, sprintf_g_precision);
  tcase_add_test(s21_string_h, sprintf_g_precision_zero);
  tcase_add_test(s21_string_h, sprintf_g_precision_missing);
  tcase_add_test(s21_string_h, sprintf_g_many_zeroes_in_front);
  tcase_add_test(s21_string_h, sprintf_g_one_zero);
  tcase_add_test(s21_string_h, sprintf_g_zero);
  tcase_add_test(s21_string_h, sprintf_g_mantiss);
  tcase_add_test(s21_string_h, sprintf_g_mantiss_flags);
  tcase_add_test(s21_string_h, sprintf_g_short_no_mantiss);
  tcase_add_test(s21_string_h, sprintf_LG);
  tcase_add_test(s21_string_h, sprintf_g_many);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}