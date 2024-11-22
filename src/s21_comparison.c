#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (sign_1 != sign_2 && !is_nulls(value_1, value_2)) {
    result = sign_1 > sign_2;
  } else {
    normalize_scale(&value_1, &value_2);
    if (value_1.bits[2] < value_2.bits[2]) {
      result = 1;
    } else if (value_1.bits[2] == value_2.bits[2]) {
      if (value_1.bits[1] < value_2.bits[1]) {
        result = 1;
      } else if (value_1.bits[1] == value_2.bits[1]) {
        if (value_1.bits[0] < value_2.bits[0]) {
          result = 1;
        }
      }
    }
    if (sign_1 && sign_2) {
      result = !result;
    }
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less_or_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  normalize_scale(&value_1, &value_2);
  if (!is_nulls(value_1, value_2)) {
    result = result && (sign_1 == sign_2);
    for (int i = 0; i < 3; i++) {
      result = result && (value_1.bits[i] == value_2.bits[i]);
    }
  }

  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int is_nulls(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  for (int i = 0; i < 3; i++) {
    res = res && (value_1.bits[i] == 0 && value_2.bits[i] == 0);
  }
  return res;
}