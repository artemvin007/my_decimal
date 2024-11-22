#include <math.h>

#include "s21_decimal.h"

#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err_code = 0;
  if (!dst) {
    err_code = 1;
  } else if (isinf(src) || isnan(src) || fabs(src) > MAX_FLOAT_TO_CONVERT ||
             fabs(src) < MIN_FLOAT_TO_CONVERT) {
    err_code = 1;
  } else {
    set_null(dst);
    int scale = 0;
    for (int i = 0; i < 7 && (int)src != src; i++) {
      src *= 10;
      scale += 1;
    }
    src = roundf(src);
    s21_from_int_to_decimal(abs((int)src), dst);
    set_scale(dst, scale);
    set_sign(dst, src < 0);
  }
  return err_code;
}