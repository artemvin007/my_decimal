#include <limits.h>
#include <stdlib.h>

#define S21_MAX 4294967295

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// extra methods

int get_bit(s21_decimal value, int pos);  // получает бит по адресу
s21_decimal *set_bit(s21_decimal *value, int pos,
                     int bit);  // устанавливает бит по адресу
int get_sign(s21_decimal value);  // получает знак
s21_decimal *set_sign(s21_decimal *value, int sign);  // устанавливает знак
int get_scale(s21_decimal value);  // получает степень
s21_decimal *set_scale(s21_decimal *value, int bit);  // устанавливает степень

void normalize_scale(
    s21_decimal *value_1,
    s21_decimal *value_2);  // приравнивает степени ( для арифметики пока )
s21_decimal *increase_scale(s21_decimal *value,
                            int shift);  // повышение степени 10^4 -> 10^5
s21_decimal *decrease_scale(s21_decimal *value,
                            int shift);  // понижение степени 10^5 -> 10^4
s21_decimal *shifting_left(s21_decimal *value,
                           int shift);  // сдвиг числа влево 101 -> 1010
s21_decimal *shifting_right(s21_decimal *value,
                            int shift);  // сдвиг числа вправо 1010 -> 101
int find_last_bit(s21_decimal value);  // находит последний значимый бит

s21_decimal *subtraction(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);  // побитовое вычитание
int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             int sign);  // побитовое сложение

s21_decimal *div_with_remain(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result,
                             s21_decimal *remain);  // деление с остатком
int find_power(
    s21_decimal value_1,
    s21_decimal value_2);  // поиск степени двойки для деления с остатком
s21_decimal *div_with_fraction(s21_decimal *remain, s21_decimal div_value,
                               s21_decimal *result);  // деление дробной части

s21_decimal *multiplication(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result,
                            int overflow);  // перемножение чисел
s21_decimal *simple_mult(
    s21_decimal value_1, s21_decimal value_2,
    s21_decimal *result);  // простое перемножение чисел без переполнения
int find_overflow(s21_decimal value_1,
                  s21_decimal value_2);  // поиск переполнения, если оно есть

s21_decimal *s21_copydec(
    s21_decimal *result,
    s21_decimal value);  // копирование числа в новую переменную
s21_decimal *s21_resdec(
    s21_decimal *result);  // сброс числа ( приравнивание к нулю )

void set_null(s21_decimal *a);
void null_power(s21_decimal *src);
int is_correct_decimal(s21_decimal *a);
void pow_ten(s21_decimal *res, int scale);

int is_nulls(s21_decimal value_1, s21_decimal value_2);
//

int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // ok
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // ok
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // ok
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // ok

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);  // ok