#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  s21_resdec(result);
  if (!s21_is_equal(value_1, value_2)) {
    if (sign_1 == sign_2) {
      normalize_scale(&value_1, &value_2);
      set_sign(&value_1, 1);
      set_sign(&value_2, 1);
      if (s21_is_greater(value_1, value_2)) {
        subtraction(value_1, value_2, result);
        set_scale(set_sign(result, sign_1), get_scale(value_1));
      } else {
        subtraction(value_2, value_1, result);
        set_scale(set_sign(result, !sign_1), get_scale(value_1));
      }
    } else {
      set_sign(&value_2, sign_1);
      err = s21_add(value_2, value_1, result);
    }
  }
  return err;
}

s21_decimal *subtraction(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
  for (int i = 0; i < 96; i++) {
    int bit_1 = get_bit(value_1, i), bit_2 = get_bit(value_2, i);
    int dif = bit_1 - bit_2;
    if (dif != -1)
      set_bit(result, i, dif);
    else {
      int j = i;
      for (; bit_1 == 0; j++) {
        set_bit(&value_1, j, 1);
        bit_1 = get_bit(value_1, j + 1);
      }
      set_bit(&value_1, j, 0);
      set_bit(result, i, 1);
    }
  }
  return result;
}