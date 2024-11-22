#include "s21_decimal_test.h"

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = INT_MIN;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_3) {
  s21_decimal *val = NULL;
  int tmp = 123456789;
  ck_assert_int_eq(1, s21_from_int_to_decimal(tmp, val));
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s = suite_create("\033[103mS21_FROM_INT_TO_DECIMAL\033[0m");
  TCase *tc = tcase_create("convertors_tc");

  tcase_add_test(tc, from_int_to_decimal_0);
  tcase_add_test(tc, from_int_to_decimal_1);
  tcase_add_test(tc, from_int_to_decimal_2);
  tcase_add_test(tc, from_int_to_decimal_3);

  suite_add_tcase(s, tc);
  return s;
}