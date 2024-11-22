#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int err_code = 0;
  if (!result) {
    err_code = 1;
  } else if (!is_correct_decimal(&value)) {
    err_code = 1;
  } else {
    s21_decimal ten = {0};
    ten.bits[1] = 10;
    int power = get_scale(value);
    int sign = get_sign(value);
    null_power(&value);
    s21_decimal remain = {0};
    for (; power > 0; power--) {
      div_with_remain(value, ten, &value, &remain);
    }
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    if (remain.bits[0] >= 5) {
      result->bits[0] += 1;
    }
    set_sign(result, sign);
  }
  return err_code;
}
