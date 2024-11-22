#include "s21_decimal_test.h"

START_TEST(truncate_0) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{2, 0, 0, 0}};
  set_scale(&val, 10);
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));

  END_TEST
}

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, 0}};
  set_scale(&val, 10);
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  set_scale(&val, 10);
  s21_decimal res = {0};
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
}
END_TEST

START_TEST(truncate_4) {
  s21_decimal val = {{2, 0, 0, 123456789}};
  s21_decimal res = {0};
  ck_assert_int_eq(1, s21_truncate(val, &res));
}
END_TEST

START_TEST(truncate_5) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal *res = NULL;
  ck_assert_int_eq(1, s21_truncate(val, res));
}
END_TEST

Suite *s21_truncate_suite(void) {
  Suite *s = suite_create("\033[103mS21_TRUNCATE\033[0m");
  TCase *tc = tcase_create("truncate_tc");

  tcase_add_test(tc, truncate_0);
  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_test(tc, truncate_5);

  suite_add_tcase(s, tc);
  return s;
}