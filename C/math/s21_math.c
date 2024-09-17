#include "s21_math.h"
#include <float.h>

int s21_abs(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}
long double s21_atan(double x) {
    long double result = 0;
    if (x == 1) {
        result = S21_PI / 4;
    }
    if (x == -1) {
        result = -S21_PI / 4;
    }
    if (x == 0) {
        result = 0;
    }
    if (x < 1 && x > -1) {
        result = s21_atan_series(x);
    }
    if (x > 1) {
        result = S21_PI / 2 - s21_atan_series(1 / x);
    }
    if (x < -1) {
        result = -S21_PI / 2 - s21_atan_series(1 / x);
    }
    return result;
}

long double s21_atan_series(double x) {
    long double result = x, temp = x, i = 1;
    while (s21_lfabs(result) > 10E-12) {
        result = -1 * result * x * x * (2 * i - 1) / (2 * i + 1);
        i += 1;
        temp += result;
    }
    return temp;
}
long double s21_asin(double x) {
    long double res = 0.0;
    if (x <= 1 && x >= -1) {
        double sarg = x / s21_sqrt(1 - x * x);
        res = s21_atan(sarg);
    } else {
        res = S21_NAN;
    }
    return res;
}

long double s21_acos(double x) {
    long double res = 0.0;
    if (x <= 1 && x >= -1) {
        res = S21_PI / 2 - s21_asin(x);
    } else {
        res = S21_NAN;
    }
    return res;
}

long double s21_ceil(double x) {
    long double result = (long double) (int) x;
    if (x - (int) x > 0) {
        result += 1;
    }
    return result;
}
long double s21_cos(double x) {
    int sign = 1;
    x = s21_fmod(x, S21_PI * 2);
    double x_2 = x * x;
    long double last_term = 1;
    long double result = 1;
    for (int i = 1; i <= NUM_OF_TERMS; i++) {
        last_term = last_term * ((x_2 * (-1)) / ((i * 2 - 1) * (i * 2)));
        result += last_term;
    }
    return sign * result;
}
long double s21_exp(double x) {
    long double last_term = 1;
    long double result = last_term;
    int i = 1;
    int sign = 1;
    if (x < 0) {
        sign = -1;
        x *= -1;
    }
    int flag = 1;
    while ((last_term > 1e-17) && flag) {
        if (result > DBL_MAX) {
            if (sign == -1) {
                result = 0;
                flag = 0;
                continue;
            } else {
                result = S21_INFINITY;
                flag = 0;
                continue;
            }
        }
        if (result < DBL_MIN) {
            result = 0;
            flag = 0;
            continue;
        }
        last_term *= (x / i);
        i++;
        result += last_term;
    }
    if ((sign == -1) && flag) {
        result = 1.0 / result;
    }
    return result;
}
long double s21_fabs(double x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}
long double s21_lfabs(long double x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

long double s21_floor(double x) {
    long double result = (long double) (int) x;
    if (x - (int) x < 0) {
        result -= 1;
    }
    return result;
}
long double s21_fmod(double x, double y) {
    return ((x) - (int) ((x) / (y)) * (y));
}
long double s21_log(double x) {
    if (x == 0) {
        return S21_NEG_INFINITY;
    }
    if (x < 0) {
        return S21_NAN;
    }
    long double x1 = x;
    int k = 0;
    while (x1 > 1) {
        x1 /= 10;
        k++;
    }
    long double xn = x1 - 1;
    long double term = xn;
    long double result = term;
    int n = 1;
    while (s21_fabs(term) > 1e-17) {
        n++;
        xn *= -(x1 - 1);
        term = xn / n;
        result += term;
    }
    return result + k * S21_LN10;
}
long double s21_pow(double base, double exp) {
    long double result = 0;
    if ((base < 0) && ((int) exp - exp != 0)) {
        return S21_NAN;
    }
    if (base < 0) {
        base *= -1;
        result = s21_exp(exp * s21_log(base));
    } else {
        result = s21_exp(exp * s21_log(base));
    }
    return result;
}
long double s21_sin(double x) {
    int sign = 1;
    x = s21_fmod(x, S21_PI * 2);
    double x_2 = x * x;
    long double last_term = x;
    long double result = x;
    for (int i = 1; i <= NUM_OF_TERMS; i++) {
        last_term = last_term * ((x_2 * (-1)) / ((i * 2) * (i * 2 + 1)));
        result += last_term;
    }
    return sign * result;
}

long double s21_sqrt(double x) {
    if (x < 0) {
        return S21_NAN;
    }
    long double xn = x / 2;
    long double xp = 0;
    while (s21_fabs(xn - xp) > 1e-7) {
        xp = xn;
        xn = 0.5 * (xn + x / xn);
    }
    return xn;
}
long double s21_tan(double x) {
    return s21_sin(x) / s21_cos(x);
}
