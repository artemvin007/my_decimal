#include "s21_decimal_test.h"

START_TEST(is_equal_0) {
  s21_decimal val1 = {{144, 0, 0, 0}};
  s21_decimal val2 = {{144, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal val1 = {{144, 0, 0, 0}};
  s21_decimal val2 = {{144, 0, 0, 0}};
  set_sign(&val1, 1);
  set_sign(&val2, 0);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal val1 = {{144, 0, 0, 0}};
  s21_decimal val2 = {{144, 0, 0, 0}};
  set_sign(&val1, 0);
  set_sign(&val2, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal val1 = {{144, 1, 0, 0}};
  s21_decimal val2 = {{144, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_scale(&val1, 3);
  set_scale(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

Suite *s21_is_equal_suite(void) {
  Suite *s = suite_create("\033[103mS21_IS_EQUAL\033[0m");
  TCase *tc = tcase_create("equal_tc");

  tcase_add_test(tc, is_equal_0);
  tcase_add_test(tc, is_equal_1);
  tcase_add_test(tc, is_equal_2);
  tcase_add_test(tc, is_equal_3);
  tcase_add_test(tc, is_equal_4);
  tcase_add_test(tc, is_equal_5);
  tcase_add_test(tc, is_equal_6);
  tcase_add_test(tc, is_equal_7);

  suite_add_tcase(s, tc);
  return s;
}
