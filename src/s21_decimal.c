#include "s21_decimal.h"

void set_null(s21_decimal *a) {
  for (int i = 0; i < 4; i++) {
    a->bits[i] = 0;
  }
}

int get_bit(s21_decimal value, int pos) {
  int bit = 0 < (value.bits[pos / 32] & (1u << (pos % 32)));
  return bit;
}

s21_decimal *set_bit(s21_decimal *value, int pos, int bit) {
  int index = pos / 32;
  int bit_num = pos % 32;
  if (bit && index < 4)
    value->bits[index] |= (1u << bit_num);
  else if (!bit && index < 4)
    value->bits[index] &= ~(1u << bit_num);
  return value;
}

int get_sign(s21_decimal value) {
  int sign = 0 < (value.bits[3] & (1u << 31));
  return sign;
}

s21_decimal *set_sign(s21_decimal *value, int sign) {
  value = set_bit(value, 127, sign);
  return value;
}

int get_scale(s21_decimal value) {
  int scale = (char)(value.bits[3] >> 16);
  return scale;
}

s21_decimal *set_scale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale < 29) {
    int sign = get_sign(*value);
    value->bits[3] = 0;
    value->bits[3] |= scale << 16;
    if (sign) set_sign(value, 1);
  }
  return value;
}

void normalize_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = get_scale(*value_1);
  int scale_2 = get_scale(*value_2);
  if (scale_1 != scale_2) {
    if (scale_1 < scale_2)
      normalize_scale(value_2, value_1);
    else {
      for (; scale_1 - scale_2 > 0 && !get_bit(*value_2, 95); scale_2++)
        increase_scale(value_2, 1);
      for (; scale_1 - scale_2 > 0; scale_1--) decrease_scale(value_1, 1);
    }
  }
}

s21_decimal *increase_scale(s21_decimal *value, int shift) {
  int scale = get_scale(*value);
  if (scale + shift < 29) {
    set_scale(value, scale + shift);
    s21_decimal value_1 = *shifting_left(value, 1);
    s21_decimal value_2 = *shifting_left(value, 2);
    addition(value_1, value_2, value, 0);
  }
  return value;
}

s21_decimal *decrease_scale(s21_decimal *value, int shift) {
  int temp;
  unsigned long long overflow;
  for (int i = 0; i < shift; i++) {
    overflow = value->bits[2];
    value->bits[i] = overflow / 10;
    for (int j = 2; j > 0; j--) {
      temp = overflow % 10;
      value->bits[j] = overflow / 10;
      overflow = temp * (S21_MAX + 1) + value->bits[j - 1];
      if (j - 1 == 0) value->bits[i] = overflow / 10;
    }
  }
  set_scale(value, (get_scale(*value) - shift));
  return value;
}

void null_power(s21_decimal *src) { src->bits[3] = 0; }

s21_decimal *shifting_left(s21_decimal *value, int shift) {
  if (!get_bit(*value, 95) && shift < 95) {
    for (int i = 0; i < shift; i++) {
      int bit_31 = get_bit(*value, 31), bit_63 = get_bit(*value, 63);
      for (int j = 0; j < 3; j += 1) value->bits[j] <<= 1;
      value = set_bit(value, 32, bit_31);
      value = set_bit(value, 64, bit_63);
    }
  }
  return value;
}

int find_last_bit(s21_decimal value) {
  int last = 0;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(value, i)) {
      last = i;
      break;
    }
  }
  return last;
}

s21_decimal *s21_copydec(s21_decimal *result, s21_decimal value) {
  for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  return result;
}

s21_decimal *s21_resdec(s21_decimal *result) {
  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  return result;
}

int is_correct_decimal(s21_decimal *a) {
  int res = 1;
  for (int i = 96; i < 112; i++) {
    res = res && (get_bit(*a, i) == 0);
  }
  res = res && (get_scale(*a) <= 28);
  for (int i = 119; i < 127; i++) {
    res = res && (get_bit(*a, i) == 0);
  }
  return res;
}