#include "s21_decimal_test.h"

START_TEST(from_decimal_to_float_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_scale(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal val = {{123456789, 0, 0, 123456789}};
  float dst = 0.0;
  ck_assert_int_eq(1, s21_from_decimal_to_float(val, &dst));
}
END_TEST

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s = suite_create("\033[103mS21_FROM_DECIMAL_TO_FLOAT\033[0m");
  TCase *tc = tcase_create("convertors_tc");

  tcase_add_test(tc, from_decimal_to_float_0);
  tcase_add_test(tc, from_decimal_to_float_1);
  tcase_add_test(tc, from_decimal_to_float_2);

  suite_add_tcase(s, tc);
  return s;
}