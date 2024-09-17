#include <check.h>
#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

START_TEST(eq_test) {
  matrix_t M1 = {0};
  matrix_t M2 = {0};
  int result = FAILURE;
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(4, 4, &M2);
  read_matrix_from_file(&M1, "./data/M1.txt");
  read_matrix_from_file(&M2, "./data/M1.txt");
  /* eq */
  result = s21_eq_matrix(&M1, &M2);
  ck_assert_int_eq(result, SUCCESS);
  /* not eq */
  read_matrix_from_file(&M2, "./data/M2.txt");
  result = s21_eq_matrix(&M1, &M2);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&M1);
  s21_remove_matrix(&M2);
}
END_TEST

START_TEST(sum_test) {
  matrix_t M1 = {0};
  matrix_t M2 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(4, 4, &M2);
  s21_create_matrix(4, 4, &answer);
  read_matrix_from_file(&M1, "./data/M1.txt");
  read_matrix_from_file(&M2, "./data/M2.txt");
  read_matrix_from_file(&answer, "./data/sum_test_answer.txt");
  s21_sum_matrix(&M1, &M2, &result);
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&M2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(sub_test) {
  matrix_t M1 = {0};
  matrix_t M2 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(4, 4, &M2);
  s21_create_matrix(4, 4, &answer);
  read_matrix_from_file(&M1, "./data/M1.txt");
  read_matrix_from_file(&M2, "./data/M2.txt");
  read_matrix_from_file(&answer, "./data/sub_test_answer.txt");
  s21_sub_matrix(&M1, &M2, &result);
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&M2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(mult_test_4x4) {
  matrix_t M1 = {0};
  matrix_t M2 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(4, 4, &M2);
  s21_create_matrix(4, 4, &answer);
  read_matrix_from_file(&M1, "./data/M1.txt");
  read_matrix_from_file(&M2, "./data/M2.txt");
  read_matrix_from_file(&answer, "./data/mult_test_answer.txt");
  s21_mult_matrix(&M1, &M2, &result);
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&M2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(mult_test_6_2_on_2_4) {
  matrix_t M1 = {0};
  matrix_t M2 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(6, 2, &M1);
  s21_create_matrix(2, 5, &M2);
  s21_create_matrix(6, 5, &answer);
  read_matrix_from_file(&M1, "./data/matrix_6_2.txt");
  read_matrix_from_file(&M2, "./data/matrix_2_5.txt");
  read_matrix_from_file(&answer, "./data/matrix_6_5.txt");
  s21_mult_matrix(&M1, &M2, &result);
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&M2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(mult_by_scalar) {
  matrix_t M1 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  double scalar = 3.14;
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(4, 4, &answer);
  read_matrix_from_file(&M1, "./data/M1.txt");
  s21_mult_number(&M1, scalar, &result);
  read_matrix_from_file(&answer, "./data/M1_mult_scalar.txt");
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(determinant) {
  matrix_t M1 = {0};
  double result = 0;
  double answer = -0.237123;
  s21_create_matrix(4, 4, &M1);
  read_matrix_from_file(&M1, "./data/M1.txt");
  s21_determinant(&M1, &result);
  ck_assert_double_eq_tol(result, answer, 1e-6);
  s21_remove_matrix(&M1);
  /* test for 1x1 matrix */
  matrix_t M11 = {0};
  s21_create_matrix(1, 1, &M11);
  M11.matrix[0][0] = 5;
  s21_determinant(&M11, &result);
  ck_assert_double_eq_tol(result, 5, 1e-6);
  s21_remove_matrix(&M11);
}
END_TEST

START_TEST(transpose) {
  matrix_t M1 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(4, 4, &answer);
  read_matrix_from_file(&M1, "./data/M1.txt");
  s21_transpose(&M1, &result);
  read_matrix_from_file(&answer, "./data/M1_transposed.txt");
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(transpose_7x6) {
  matrix_t M1 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(7, 6, &M1);
  s21_create_matrix(6, 7, &answer);
  read_matrix_from_file(&M1, "./data/random_7x6.txt");
  s21_transpose(&M1, &result);
  read_matrix_from_file(&answer, "./data/random_7x6_transposed.txt");
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(inverse_matrix) {
  matrix_t M1 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(4, 4, &answer);
  read_matrix_from_file(&M1, "./data/M1.txt");
  s21_inverse_matrix(&M1, &result);
  read_matrix_from_file(&answer, "./data/M1_inverse.txt");
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(complement) {
  matrix_t M1 = {0};
  matrix_t result = {0};
  matrix_t answer = {0};
  s21_create_matrix(3, 3, &M1);
  s21_create_matrix(3, 3, &answer);
  read_matrix_from_file(&M1, "./data/M3.txt");
  s21_calc_complements(&M1, &result);
  read_matrix_from_file(&answer, "./data/M3_compl.txt");
  for (int i = 0; i < answer.rows; i++) {
    for (int j = 0; j < answer.columns; j++) {
      ck_assert_double_le_tol(result.matrix[i][j], answer.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&M1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(non_square_determinant) {
  matrix_t M1 = {0};
  double result;
  int error = 0;
  s21_create_matrix(2, 5, &M1);
  read_matrix_from_file(&M1, "./data/matrix_2_5.txt");
  error = s21_determinant(&M1, &result);
  ck_assert_int_eq(error, CALC_ERROR);
  s21_remove_matrix(&M1);
}
END_TEST

START_TEST(calc_err) {
  matrix_t M1 = {0};
  matrix_t M2 = {0};
  matrix_t result = {0};
  int err = 0;
  double det = 0;
  s21_create_matrix(4, 4, &M1);
  s21_create_matrix(2, 5, &M2);
  read_matrix_from_file(&M1, "./data/M1.txt");
  read_matrix_from_file(&M2, "./data/matrix_2_5.txt");
  /* summ */
  err = s21_sum_matrix(&M1, &M2, &result);
  ck_assert_int_eq(err, CALC_ERROR);
  /* sub */
  err = s21_sub_matrix(&M1, &M2, &result);
  ck_assert_int_eq(err, CALC_ERROR);
  /* mult */
  err = s21_mult_matrix(&M1, &M2, &result);
  ck_assert_int_eq(err, CALC_ERROR);
  /* determinant */
  err = s21_determinant(&M2, &det);
  ck_assert_int_eq(err, CALC_ERROR);
  /* inverse_matrix , not square*/
  err = s21_inverse_matrix(&M2, &result);
  ck_assert_int_eq(err, CALC_ERROR);
  /* inverse_matrix , null determinant*/
  read_matrix_from_file(&M1, "./data/null_determinant_matrix.txt");
  err = s21_inverse_matrix(&M1, &result);
  ck_assert_int_eq(err, CALC_ERROR);
  s21_remove_matrix(&M1);
  s21_remove_matrix(&M2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(incorrect_matrix_err) {
  matrix_t M1 = {0};
  matrix_t M2 = {0};
  matrix_t result = {0};
  int err = 0;
  double det = 0;
  read_matrix_from_file(&M1, "./data/M1.txt");
  read_matrix_from_file(&M2, "./data/matrix_2_5.txt");
  /* sum */
  err = s21_sum_matrix(&M1, &M2, &result);
  ck_assert_int_eq(err, INCORRECT_MATRIX);
  /* sub */
  err = s21_sub_matrix(&M1, &M2, &result);
  ck_assert_int_eq(err, INCORRECT_MATRIX);
  /* eq_matrix */
  err = s21_eq_matrix(&M1, &M2);
  ck_assert_int_eq(err, FAILURE);
  /* mult_number */
  err = s21_mult_number(&M1, 2, &result);
  ck_assert_int_eq(err, INCORRECT_MATRIX);
  /* mult_matrix */
  err = s21_mult_matrix(&M1, &M2, &result);
  ck_assert_int_eq(err, INCORRECT_MATRIX);
  /* transpose */
  err = s21_transpose(&M1, &result);
  ck_assert_int_eq(err, INCORRECT_MATRIX);
  /* det */
  err = s21_determinant(&M1, &det);
  ck_assert_int_eq(err, INCORRECT_MATRIX);
  /* inverse */
  err = s21_inverse_matrix(&M1, &result);
  ck_assert_int_eq(err, INCORRECT_MATRIX);
}
END_TEST

Suite *f_example_suite_create() {
  Suite *s1 = suite_create("Test_matrix");
  TCase *core_test = tcase_create("All");
  suite_add_tcase(s1, core_test);
  tcase_add_test(core_test, eq_test);
  tcase_add_test(core_test, sum_test);
  tcase_add_test(core_test, sub_test);
  tcase_add_test(core_test, mult_test_4x4);
  tcase_add_test(core_test, mult_test_6_2_on_2_4);
  tcase_add_test(core_test, mult_by_scalar);
  tcase_add_test(core_test, transpose);
  tcase_add_test(core_test, transpose_7x6);
  tcase_add_test(core_test, determinant);
  tcase_add_test(core_test, inverse_matrix);
  tcase_add_test(core_test, non_square_determinant);
  tcase_add_test(core_test, incorrect_matrix_err);
  tcase_add_test(core_test, calc_err);
  tcase_add_test(core_test, complement);
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
