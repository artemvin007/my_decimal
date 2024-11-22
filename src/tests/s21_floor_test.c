#include "s21_decimal_test.h"

START_TEST(floor_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
  ck_assert_int_eq(res.bits[0], 2);
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  set_sign(&val, 1);
  ck_assert_int_eq(0, s21_floor(val, &res));
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{200000, 0, 0, 0}};
  s21_decimal res = {0};
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_floor(val, &res));
  ck_assert_int_eq(res.bits[0], 2);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{200000, 0, 0, 0}};
  s21_decimal res = {0};
  set_sign(&val, 1);
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_floor(val, &res));
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal val = {{210000, 0, 0, 0}};
  s21_decimal res = {0};
  set_sign(&val, 1);
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_floor(val, &res));
  ck_assert_int_eq(res.bits[0], 3);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(floor_5) {
  s21_decimal val = {{201000, 0, 0, 123456789}};
  s21_decimal *res = NULL;
  ck_assert_int_eq(1, s21_floor(val, res));
}
END_TEST

START_TEST(floor_6) {
  s21_decimal val = {{201000, 0, 0, 123456789}};
  s21_decimal res = {0};
  ck_assert_int_eq(1, s21_floor(val, &res));
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s = suite_create("\033[103mS21_FLOOR\033[0m");
  TCase *tc = tcase_create("floor_tc");

  tcase_add_test(tc, floor_0);
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, floor_5);
  tcase_add_test(tc, floor_6);

  suite_add_tcase(s, tc);
  return s;
}
