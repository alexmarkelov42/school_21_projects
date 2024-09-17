#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define S21_E 2.7182818284590452354         /* e */
#define S21_LOG2E 1.4426950408889634074     /* log_2 e */
#define S21_LOG10E 0.43429448190325182765   /* log_10 e */
#define S21_LN2 0.69314718055994530942      /* log_e 2 */
#define S21_LN10 2.30258509299404568402     /* log_e 10 */
#define S21_PI 3.14159265358979323846       /* pi */
#define S21_PI_2 1.57079632679489661923     /* pi/2 */
#define S21_PI_4 0.78539816339744830962     /* pi/4 */
#define S21_1_PI 0.31830988618379067154     /* 1/pi */
#define S21_2_PI 0.63661977236758134308     /* 2/pi */
#define S21_2_SQRTPI 1.12837916709551257390 /* 2/sqrt(pi) */
#define S21_SQRT2 1.41421356237309504880    /* sqrt(2) */
#define S21_SQRT1_2 0.70710678118654752440
#define NUM_OF_TERMS 30
#define S21_NAN 0.0f/0.0f
#define S21_INFINITY 1.0f/0.0f
#define S21_NEG_INFINITY -1.0f/0.0f

int s21_abs(int x);                            // computes absolute value of an integer value
long double s21_acos(double x);                // computes arc cosine
long double s21_asin(double x);                // computes arc sine
long double s21_atan(double x);                // computes arc tangent
long double s21_ceil(double x);                // returns the nearest integer not less than the given value
long double s21_cos(double x);                 // computes cosine
long double s21_exp(double x);                 // returns e raised to the given power
long double s21_fabs(double x);                // computes absolute value of a floating-point value
long double s21_lfabs(long double x);          // same as fabs but long
long double s21_floor(double x);               // returns the nearest integer not greater than the given value
long double s21_fmod(double x, double y);      // remainder of the floating-point division operation
long double s21_log(double x);                 // computes natural logarithm
long double s21_pow(double base, double exp);  // raises a number to the given power
long double s21_sin(double x);                 // computes sine
long double s21_sqrt(double x);                // computes square root
long double s21_tan(double x);                 // computes tangent
long double s21_atan_series(double x);          // arc tangent via taylor series(additional function)

#endif  // SRC_S21_MATH_H_
