#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int err = 0;
  result = s21_copydec(s21_resdec(result), value);
  if (get_sign(value))
    set_sign(result, 0);
  else
    set_sign(result, 1);
  return err;
}