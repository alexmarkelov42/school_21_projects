#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "s21_math.h"

START_TEST(s21_abs_test) {
    for (int i = -1234567; i < 1234567; i += 10) {
        ck_assert_int_eq(s21_abs(i), abs(i));
    }
}
END_TEST

START_TEST(s21_acos_test) {
    for (double i = -1.; i < 1.; i += 0.01) {
        ck_assert_ldouble_eq_tol(s21_acos(i), acos(i), 1e-6);
    }
    ck_assert_ldouble_nan(s21_acos(-1.234567));
    ck_assert_ldouble_nan(s21_acos(1.234567));
}
END_TEST

START_TEST(s21_ceil_test) {
    for (double i = -10.; i < 10.; i += 0.01) {
        ck_assert_int_eq(s21_ceil(i), ceil(i));
    }
}
END_TEST

START_TEST(s21_floor_test) {
    for (double i = -10.; i < 10.; i += 0.01) {
        ck_assert_int_eq(s21_floor(i), floor(i));
    }
}
END_TEST

START_TEST(s21_asin_test) {
    for (double i = -1.; i < 1.; i += 0.01) {
        ck_assert_ldouble_eq_tol(s21_asin(i), asin(i), 1e-6);
    }
    ck_assert_ldouble_nan(s21_asin(-1.234567));
    ck_assert_ldouble_nan(s21_asin(1.234567));
}
END_TEST

START_TEST(s21_atan_test) {
    for (double i = -1.; i < 1.; i += 0.001) {
        ck_assert_ldouble_eq_tol(s21_atan(i), atan(i), 1e-6);
    }
    ck_assert_ldouble_eq_tol(s21_atan(1), atan(1), 1e-6);
    ck_assert_ldouble_eq_tol(s21_atan(0), atan(0), 1e-6);
}
END_TEST

START_TEST(s21_cos_test) {
    for (double i = -10.; i < 10.; i += 0.01) {
        ck_assert_ldouble_eq_tol(s21_cos(i), cos(i), 1e-6);
    }
    ck_assert_ldouble_eq_tol(s21_cos(S21_PI_2), cos(S21_PI_2), 1e-6);
}
END_TEST

START_TEST(s21_tan_test) {
    for (double i = -1.99; i < 2.75; i += 0.001) {
        ck_assert_ldouble_eq_tol(s21_tan(i), tan(i), 1e-6);
    }
    ck_assert_ldouble_eq_tol(s21_tan(S21_PI_2 - 0.001), tan(S21_PI_2 - 0.001), 1e-6);
}
END_TEST

START_TEST(s21_exp_test) {
    for (double i = -1; i < 1; i += 0.001) {
        ck_assert_ldouble_eq_tol(s21_exp(i), exp(i), 1e-6);
    }
    ck_assert_ldouble_eq_tol(s21_exp(-2), exp(-2), 1e-6);
    ck_assert_ldouble_eq_tol(s21_exp(-13.253678), exp(-13.253678), 1e-6);
    ck_assert_ldouble_infinite(s21_exp(1324561238.253678));
    ck_assert_ldouble_eq_tol(s21_exp(-5647475856), exp(-5647475856), 1e-6);
    ck_assert_ldouble_eq_tol(s21_exp(-5.946047569), exp(-5.946047569), 1e-6);
    ck_assert_ldouble_eq_tol(s21_exp(DBL_MIN - 1), exp(DBL_MIN - 1), 1e-6);
}
END_TEST

START_TEST(s21_pow_test) {
    ck_assert_ldouble_eq_tol(s21_pow(2.3, 4.21), pow(2.3, 4.21), 1e-6);
    ck_assert_ldouble_eq_tol(s21_pow(4.0, 11.0), pow(4.0, 11.0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_pow(41.243, 5.3), pow(41.243, 5.3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_pow(41.243, 0.7), pow(41.243, 0.7), 1e-6);
    ck_assert_ldouble_eq_tol(s21_pow(2.3, 2.3), pow(2.3, 2.3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_pow(-12, 4), pow(-12, 4), 1e-6);
    ck_assert_ldouble_nan(s21_pow(-1.234567, 4.8));
    ck_assert_ldouble_nan(s21_pow(-1243, 4.8));
    ck_assert_ldouble_nan(s21_pow(-1243, -4.8));
    ck_assert_ldouble_eq_tol(s21_pow(1243, -4.21), pow(1243, -4.21), 1e-6);
}
END_TEST

START_TEST(s21_sin_test) {
    for (double i = -S21_PI; i < S21_PI; i += 0.001) {
        ck_assert_ldouble_eq_tol(s21_sin(i), sin(i), 1e-6);
    }
    ck_assert_ldouble_eq_tol(s21_sin(0), sin(0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(S21_PI), sin(S21_PI), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(S21_PI / 3), sin(S21_PI / 3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(S21_PI / 6), sin(S21_PI / 6), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(S21_PI / 2), sin(S21_PI / 2), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(S21_PI / 4), sin(S21_PI / 4), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(-S21_PI / 4), sin(-S21_PI / 4), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(-S21_PI / 2), sin(-S21_PI / 2), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(-S21_PI / 3), sin(-S21_PI / 3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(-S21_PI / 6), sin(-S21_PI / 6), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(2 * S21_PI / 3), sin(2 * S21_PI / 3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(5 * S21_PI / 6), sin(5 * S21_PI / 6), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(2 * S21_PI / 4), sin(2 * S21_PI / 4), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(3 * S21_PI / 4), sin(3 * S21_PI / 4), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(126.8647465), sin(126.8647465), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(-235.3456458), sin(-235.3456458), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(75846.8647465), sin(75846.8647465), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(-92553.3456458), sin(-92553.3456458), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(5659782464.8647465), sin(5659782464.8647465), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sin(-5237385933.3456458), sin(-5237385933.3456458), 1e-6);
}
END_TEST

START_TEST(s21_sqrt_test) {
    /* for (int i = 0; i < INT_MAX; i++) { */
    /*     ck_assert_ldouble_eq_tol(s21_sqrt(i), sqrt(i), 1e-6); */
    /*     for (int j = 0; j < 1e6; j++) { */
    /*         double d = i + 1e-6 * j; */
    /*         ck_assert_ldouble_eq_tol(s21_sqrt(d), sqrt(d), 1e-6); */
    /*     } */
    /* } */

    ck_assert_ldouble_nan(s21_sqrt(-1.234567));
    ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrt(0), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(1), sqrt(1), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(3), sqrt(3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(S21_PI), sqrt(S21_PI), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(788544), sqrt(788544), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(S21_PI / 3), sqrt(S21_PI / 3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(S21_PI / 6), sqrt(S21_PI / 6), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(S21_PI / 2), sqrt(S21_PI / 2), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(126.8647465), sqrt(126.8647465), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(277715298169), sqrt(277715298169), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(75846.8647465), sqrt(75846.8647465), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(1234567898675), sqrt(1234567898675), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(2 * S21_PI / 3), sqrt(2 * S21_PI / 3), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(5 * S21_PI / 6), sqrt(5 * S21_PI / 6), 1e-6);
    ck_assert_ldouble_eq_tol(s21_sqrt(2129412464.86474652345), sqrt(2129412464.86474652345), 1e-6);
}
END_TEST

START_TEST(s21_log_test) {
    for (double i = 0.001; i < 1; i += 0.001) {
        ck_assert_ldouble_eq_tol(s21_log(i), log(i), 1e-6);
    }
    ck_assert_ldouble_nan(s21_log(-1));
    ck_assert_ldouble_infinite(s21_log(0));
    ck_assert_ldouble_eq_tol(s21_log(1.1), log(1.1), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(12356), log(12356), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(1), log(1), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(123), log(123), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(0.1234), log(0.1234), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(0.9876), log(0.9876), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(S21_PI), log(S21_PI), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(0.5), log(0.5), 1e-6);
    ck_assert_ldouble_eq_tol(s21_log(547893), log(547893), 1e-6);
}
END_TEST

START_TEST(s21_fabs_test) {
    ck_assert_ldouble_eq_tol(s21_fabs(-612367.54783), fabs(-612367.54783), 1e-6);
    ck_assert_ldouble_eq_tol(s21_fabs(-45.345), fabs(-45.345), 1e-6);
    ck_assert_ldouble_eq_tol(s21_fabs(1.0), fabs(1.0), 1e-6);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, s21_abs_test);
    tcase_add_test(tc1_1, s21_ceil_test);
    tcase_add_test(tc1_1, s21_floor_test);
    tcase_add_test(tc1_1, s21_acos_test);
    tcase_add_test(tc1_1, s21_asin_test);
    tcase_add_test(tc1_1, s21_tan_test);
    tcase_add_test(tc1_1, s21_atan_test);
    tcase_add_test(tc1_1, s21_cos_test);
    tcase_add_test(tc1_1, s21_exp_test);
    tcase_add_test(tc1_1, s21_fabs_test);
    tcase_add_test(tc1_1, s21_log_test);
    tcase_add_test(tc1_1, s21_pow_test);
    tcase_add_test(tc1_1, s21_sin_test);
    tcase_add_test(tc1_1, s21_sqrt_test);
    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}
