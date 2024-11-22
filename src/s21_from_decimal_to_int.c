#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err_code = 0;
  if (!dst || !is_correct_decimal(&src)) {
    err_code = 1;
  } else {
    s21_decimal truncated_src = {0};
    s21_truncate(src, &truncated_src);
    if (src.bits[1] != 0 || src.bits[2] != 0) {
      err_code = 1;
    } else {
      *dst = truncated_src.bits[0];
      if (get_sign(src) && *dst != INT_MIN) {
        *dst = -*dst;
      }
    }
  }
  return err_code;
}