#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int err_code = 0;
  if (dst == NULL) {
    err_code = 1;
  } else {
    set_null(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      if (src != INT_MIN) {
        src *= -1;
      }
    }
    dst->bits[0] = src;
    set_sign(dst, sign);
  }
  return err_code;
}