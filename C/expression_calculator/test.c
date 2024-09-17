#include <check.h>
#include <math.h>
#include <stdio.h>

#include "smart_calc_1_0.h"

START_TEST(test1) {
  char input1[300];
  int parse_err = 0;
  int eval_err = 0;
  double x;
  double res;
  s21_stack rpn = {0};

  strcpy(input1, "sin(x) + ln(x) - (log(x) * x^2)");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, 0);
  ck_assert_int_eq(eval_err, 0);
  ck_assert_double_le_tol(res, 0.39328128947, 1e-7);
  s21_clear_stack(&rpn);

  strcpy(input1,
         "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
         "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2))))))))))"
         ")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
         "))))))))))))))))))))))))))))))))))))))))))))))))");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, 0);
  ck_assert_int_eq(eval_err, 0);
  ck_assert_double_le_tol(res, 2, 1e-7);
  s21_clear_stack(&rpn);

  strcpy(input1, "asin(0.42)+acos(atan(0.42))");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, 0);
  ck_assert_int_eq(eval_err, 0);
  ck_assert_double_le_tol(res, 1.59531141711, 1e-7);
  s21_clear_stack(&rpn);

  strcpy(input1, "cos(x)^2^2");
  x = 3.14;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, 0);
  ck_assert_int_eq(eval_err, 0);
  ck_assert_double_le_tol(res, 0.99999492692, 1e-7);
  s21_clear_stack(&rpn);

  strcpy(input1, "tan(sqrt(-3*-3))");
  x = 3.14;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, 0);
  ck_assert_int_eq(eval_err, 0);
  ck_assert_double_le_tol(res, -0.14254654307, 1e-7);
  s21_clear_stack(&rpn);

  strcpy(input1, "(ln(12) / log(12) )mod x");
  x = 3.14;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, 0);
  ck_assert_int_eq(eval_err, 0);
  ck_assert_double_le_tol(res, 2.30258509299, 1e-7);
  s21_clear_stack(&rpn);
}

END_TEST

START_TEST(err_test) {
  char input1[300];
  int parse_err = 0;
  int eval_err = 0;
  double x;
  double res;
  s21_stack rpn = {0};

  strcpy(input1,
         "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
         "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2))))))))))"
         ")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
         ")))))))))))))))))))))))))))))))))))))))))))))))))");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, STRING_TOO_BIG);
  s21_clear_stack(&rpn);

  strcpy(input1,
         "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("
         "((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2))))))))"
         ")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
         ")))))))))))))))))))))))))))))))))))))))))))))))))");

  strcpy(input1, "(2))");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, BRACKET_MISSMATCH);
  s21_clear_stack(&rpn);

  strcpy(input1, "((2)");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, BRACKET_MISSMATCH);
  s21_clear_stack(&rpn);

  strcpy(input1, "x+xxxx");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, PARSE_ERROR);
  s21_clear_stack(&rpn);

  strcpy(input1, "2++2..");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, PARSE_ERROR);
  s21_clear_stack(&rpn);

  strcpy(input1, "2++++2");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, INVALID_EXPRESSION);
  s21_clear_stack(&rpn);

  strcpy(input1, "2+");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, INVALID_EXPRESSION);
  s21_clear_stack(&rpn);

  strcpy(input1, "2------2");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, INVALID_EXPRESSION);
  s21_clear_stack(&rpn);

  strcpy(input1, "kappa");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, PARSE_ERROR);
  s21_clear_stack(&rpn);

  strcpy(input1, "+");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, INVALID_EXPRESSION);
  s21_clear_stack(&rpn);
  /* TODO  */

  strcpy(input1, "+2-3");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, OK);
  ck_assert_double_le_tol(res, -1, 1e-7);
  s21_clear_stack(&rpn);

  strcpy(input1, "sqrt(-2)");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, MATH_ERROR);
  s21_clear_stack(&rpn);

  strcpy(input1, "2/0");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, DIV_BY_ZERO);
  s21_clear_stack(&rpn);

  strcpy(input1, "2 mod 0");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, DIV_BY_ZERO);
  s21_clear_stack(&rpn);

  strcpy(input1, "log(-2)");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, MATH_ERROR);
  s21_clear_stack(&rpn);

  strcpy(input1, "ln(-2)");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, MATH_ERROR);
  s21_clear_stack(&rpn);

  strcpy(input1, "2 3 4 5 6 7 8 9 10 + -2");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, OK);
  ck_assert_int_eq(eval_err, INVALID_EXPRESSION);
  s21_clear_stack(&rpn);

  strcpy(input1, "");
  x = 0.42;
  parse_err = convert_to_rpn(input1, &rpn);
  eval_err = eval_expr(rpn, x, &res);
  ck_assert_int_eq(parse_err, PARSE_ERROR);
  s21_clear_stack(&rpn);
}
END_TEST

Suite *f_example_suite_create() {
  Suite *s1 = suite_create("Test_smartcalc");
  TCase *core_test = tcase_create("All");
  suite_add_tcase(s1, core_test);
  tcase_add_test(core_test, test1);
  tcase_add_test(core_test, err_test);

  return s1;
}

int main() {
  Suite *s1 = f_example_suite_create();
  // Runner
  SRunner *runner = srunner_create(s1);
  int number_failed;
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed == 0 ? 0 : 1;
}
