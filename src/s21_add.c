#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  s21_resdec(result);
  if (sign_1 == sign_2) {
    normalize_scale(&value_1, &value_2);
    err = addition(value_1, value_2, result, sign_1);
    set_scale(set_sign(result, sign_1), get_scale(value_1));
  } else if (sign_1)
    s21_sub(value_2, *set_sign(&value_1, !sign_1), result);
  else
    s21_sub(value_1, *set_sign(&value_2, !sign_2), result);
  return err;
}

int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             int sign) {
  int err = 0;
  int ex_bit = 0;
  for (int i = 0; i < 96; i++) {
    int bit_1 = get_bit(value_1, i), bit_2 = get_bit(value_2, i);
    int sum = bit_1 + bit_2 + ex_bit;
    if (i == 95 && sum >= 2) {
      if ((!get_scale(value_1) || !get_scale(value_2)) && !sign)
        err = 1;
      else if ((!get_scale(value_1) || !get_scale(value_2)) && sign)
        err = 2;
      else if (get_scale(value_1) > 0 && get_scale(value_2) > 0) {
        set_scale(decrease_scale(&value_1, 1), get_scale(value_1) - 1);
        set_scale(decrease_scale(&value_2, 1), get_scale(value_2) - 1);
        err = s21_add(value_1, value_2, result);
      }
      break;
    }
    set_bit(result, i, sum % 2);
    if (sum < 2)
      ex_bit = 0;
    else
      ex_bit = 1;
  }
  return err;
}