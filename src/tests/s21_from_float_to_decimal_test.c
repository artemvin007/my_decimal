#include "s21_decimal_test.h"

START_TEST(from_float_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = -1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  float res = 0.;
  float tmp = 1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  printf(" ");
  s21_from_decimal_to_float(val, &res);
  ck_assert_float_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal val = {{0, 0, 0, 12345689}};
  float src = 0;
  ck_assert_int_eq(1, s21_from_float_to_decimal(src, &val));
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  s21_decimal *val = NULL;
  float src = 120.0f;
  ck_assert_int_eq(1, s21_from_float_to_decimal(src, val));
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s = suite_create("\033[103mS21_FROM_FLOAT_TO_DECIMAL\033[0m");
  TCase *tc = tcase_create("convertors_tc");

  tcase_add_test(tc, from_float_to_decimal_0);
  tcase_add_test(tc, from_float_to_decimal_1);
  tcase_add_test(tc, from_float_to_decimal_2);
  tcase_add_test(tc, from_float_to_decimal_3);

  suite_add_tcase(s, tc);
  return s;
}