#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int err_code = 0;
  if (!result) {
    err_code = 1;
  } else if (!is_correct_decimal(&value)) {
    err_code = 1;
  } else {
    s21_resdec(result);
    int scale = get_scale(value);
    int sign = get_sign(value);
    null_power(&value);
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal remain = {0};
    for (; scale > 0; scale--) {
      div_with_remain(value, ten, &value, &remain);
    }
    s21_copydec(result, value);
    set_sign(result, sign);
  }

  return err_code;
}
