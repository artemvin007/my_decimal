#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err_code = 0;
  if (!dst || !is_correct_decimal(&src)) {
    err_code = 1;
  } else {
    *dst = 0.0;
    double tmp = 0.0;
    int sign = get_sign(src);
    int scale = get_scale(src);
    for (int i = 0; i < 96; i++) {
      if (get_bit(src, i)) {
        tmp += 1 << i;
      }
    }
    for (int i = 0; i < scale; i++) {
      tmp /= 10;
    }
    if (sign) {
      tmp *= -1;
    }
    *dst = (float)tmp;
  }

  return err_code;
}