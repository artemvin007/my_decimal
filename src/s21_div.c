#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;

  s21_resdec(result);
  if (s21_is_equal(*result, value_2))
    err = 3;
  else {
    int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    int sign = !(sign_1 == sign_2);

    int scale_1 = get_scale(value_1), scale_2 = get_scale(value_2);
    set_scale(&value_1, 0);
    set_scale(&value_2, 0);
    int scale = scale_1 - scale_2;

    if (scale < 0 &&
        find_last_bit(value_1) - find_last_bit(value_2) - (scale + 27) > 95 &&
        !sign)
      err = 1;
    else if (scale < 0 &&
             find_last_bit(value_1) - find_last_bit(value_2) - (scale + 27) >
                 95 &&
             sign)
      err = 2;
    else {
      s21_decimal remain = {0};
      s21_decimal zero = {0};
      div_with_remain(value_1, value_2, result, &remain);

      while (!s21_is_equal(zero, remain) && (get_scale(*result) < 28) &&
             !get_bit(*result, 95)) {
        increase_scale(result, 1);
        increase_scale(&remain, 1);
        scale++;
        div_with_fraction(&remain, value_2, result);
      }
      while (scale < 0 && !get_bit(*result, 95) && (get_scale(*result) < 28)) {
        increase_scale(result, 1);
        scale++;
      }

      set_sign(result, sign);
      set_scale(result, scale);
    }
  }
  return err;
}

s21_decimal *div_with_remain(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result, s21_decimal *remain) {
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  set_scale(&value_1, 0);
  set_scale(&value_2, 0);
  if (s21_is_greater(value_2, value_1)) {
    s21_resdec(result);
    s21_copydec(remain, value_1);
  } else if (s21_is_equal(value_2, value_1))
    set_bit(result, 1, 1);
  else {
    int power_two = find_power(value_1, value_2);
    int power_remain = 0;
    s21_decimal div_copy = {0};
    s21_decimal two = {0};
    two.bits[0] = 1;

    shifting_left(s21_copydec(&div_copy, value_2), power_two);
    s21_copydec(s21_resdec(result), *shifting_left(&two, power_two));
    subtraction(value_1, div_copy, remain);

    while (s21_is_greater_or_equal(*remain, value_2)) {
      power_remain = find_power(*remain, value_2);
      two.bits[0] = 1;
      shifting_left(s21_copydec(s21_resdec(&div_copy), value_2), power_remain);
      subtraction(*remain, div_copy, remain);
      addition(*result, *shifting_left(&two, power_remain), result, 0);
    }
  }
  return result;
}

int find_power(s21_decimal value_1, s21_decimal value_2) {
  int power_two = 0;
  while (!s21_is_greater(value_2, value_1)) {
    shifting_left(&value_2, 1);
    power_two++;
  }
  if (power_two != 0) power_two--;
  return power_two;
}

s21_decimal *div_with_fraction(s21_decimal *remain, s21_decimal div_value,
                               s21_decimal *result) {
  s21_decimal new_rem = {0};
  s21_decimal plus_res = {0};
  div_with_remain(*remain, div_value, &plus_res, &new_rem);
  addition(*result, plus_res, result, 0);
  s21_copydec(s21_resdec(remain), new_rem);

  return result;
}