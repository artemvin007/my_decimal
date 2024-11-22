#include "s21_decimal_test.h"

START_TEST(is_less_0) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  set_bit(&val1, 1, 127);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  set_sign(&val1, 1);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

Suite *s21_is_less_suite(void) {
  Suite *s = suite_create("\033[103mS21_IS_LESS\033[0m");
  TCase *tc = tcase_create("less_tc");

  tcase_add_test(tc, is_less_0);
  tcase_add_test(tc, is_less_1);
  tcase_add_test(tc, is_less_2);
  tcase_add_test(tc, is_less_3);
  tcase_add_test(tc, is_less_4);
  tcase_add_test(tc, is_less_5);
  tcase_add_test(tc, is_less_6);
  tcase_add_test(tc, is_less_7);
  tcase_add_test(tc, is_less_8);

  suite_add_tcase(s, tc);
  return s;
}
