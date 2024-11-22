#include "s21_decimal_test.h"

START_TEST(from_decimal_to_int_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_scale(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  int res = -1234;
  int tmp = 0.;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal val = {{123456789, 123456789, 0, 0}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  int dst = 0;
  ck_assert_int_eq(1, s21_from_decimal_to_int(val, &dst));
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal val = {{123456789, 123456789, 0, 123456789}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  int dst = 0;
  ck_assert_int_eq(1, s21_from_decimal_to_int(val, &dst));
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal val = {{123456789, 123456789, 0, 0}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  int *dst = NULL;
  ck_assert_int_eq(1, s21_from_decimal_to_int(val, dst));
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s = suite_create("\033[103mS21_FROM_DECIMAL_TO_INT\033[0m");
  TCase *tc = tcase_create("convertors_tc");

  tcase_add_test(tc, from_decimal_to_int_0);
  tcase_add_test(tc, from_decimal_to_int_1);
  tcase_add_test(tc, from_decimal_to_int_2);
  tcase_add_test(tc, from_decimal_to_int_3);
  tcase_add_test(tc, from_decimal_to_int_4);

  suite_add_tcase(s, tc);
  return s;
}