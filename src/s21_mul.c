#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int sign = !(get_sign(value_1) == get_sign(value_2));
  int scale = get_scale(value_1) + get_scale(value_2);

  s21_resdec(result);
  if (!s21_is_equal(*result, value_1) && !s21_is_equal(*result, value_2)) {
    int overflow = find_overflow(value_1, value_2);
    if (scale - overflow < 0 && !sign)
      err = 1;
    else if (scale - overflow < 0 && sign)
      err = 2;
    else {
      multiplication(value_1, value_2, result, overflow);
      set_sign(result, sign);
      set_scale(result, scale - overflow);
    }
  }
  return err;
}

int find_overflow(s21_decimal value_1, s21_decimal value_2) {
  int last_1 = find_last_bit(value_1), last_2 = find_last_bit(value_2);
  int overflow = last_1 + last_2 - 95;
  if (overflow < 0) overflow = 0;
  return overflow;
}

s21_decimal *multiplication(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result, int overflow) {
  if (overflow > 0) {
    s21_decimal ten_pow = {0};
    ten_pow.bits[0] = 10;
    increase_scale(&ten_pow, overflow);

    // mul_1 * mul_2 * 10^of + mul_1 * mod_2 + mul_2 * mod_1 + mod_1 * mod_2 /
    // 10^of-of1

    s21_decimal mul_1 = {0};
    s21_decimal mul_2 = {0};
    s21_decimal mod_1 = {0};
    s21_decimal mod_2 = {0};
    div_with_remain(value_1, ten_pow, &mul_1, &mod_1);
    div_with_remain(value_2, ten_pow, &mul_2, &mod_2);

    s21_decimal add_1 = {0};
    s21_decimal add_2 = {0};
    s21_decimal add_3 = {0};
    s21_decimal add_4 = {0};

    simple_mult(*simple_mult(mul_1, mul_2, &add_1), ten_pow, &add_1);
    simple_mult(mul_1, mod_2, &add_2);
    simple_mult(mul_2, mod_1, &add_3);

    int of_mod = find_overflow(mod_1, mod_2);
    s21_mul(mod_1, mod_2, &add_4);
    s21_resdec(&ten_pow);
    ten_pow.bits[0] = 10;
    increase_scale(&ten_pow, overflow - of_mod);
    s21_div(add_4, ten_pow, &add_4);

    addition(add_1, add_2, result, 0);
    addition(*result, add_3, result, 0);
    addition(*result, add_4, result, 0);

  } else
    simple_mult(value_1, value_2, result);
  return result;
}

s21_decimal *simple_mult(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
  s21_decimal temp = {0};
  s21_copydec(&temp, value_1);
  for (int i = 0; i < 96; i++) {
    if (get_bit(value_2, i)) addition(*result, temp, result, 0);
    shifting_left(&temp, 1);
  }
  return result;
}
