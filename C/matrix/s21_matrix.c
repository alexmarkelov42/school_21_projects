#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  double **arr = (double **)calloc(rows, sizeof(double *));
  /* TODO check if arr is NULL (not enough memory) */
  for (int i = 0; i < rows; i++) {
    arr[i] = (double *)calloc(columns, sizeof(double));
  }
  result->matrix = arr;
  result->rows = rows;
  result->columns = columns;
  return 0;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

/* void print_matrix(matrix_t *A) { */
/*   for (int i = 0; i < A->rows; i++) { */
/*     for (int j = 0; j < A->columns; j++) { */
/*       printf("%lf ", A->matrix[i][j]); */
/*     } */
/*     printf("\n"); */
/*   } */
/*   printf("\n"); */
/* } */

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  bool is_end = false;
  if ((s21_check_matrix(A) != OK) || (s21_check_matrix(B) != OK) ||
      (A->rows != B->rows) || (A->columns != B->columns)) {
    result = FAILURE;
  } else {
    for (int i = 0; (i < A->rows) && (is_end == false); i++) {
      for (int j = 0; j < A->columns && (is_end == false); j++) {
        if (fabs((A->matrix[i][j] - B->matrix[i][j])) >= 1e-6) {
          result = FAILURE;
          is_end = true;
        }
      }
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if ((s21_check_matrix(A) != OK) || (s21_check_matrix(B) != OK)) {
    res = INCORRECT_MATRIX;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if ((s21_check_matrix(A) != OK) || (s21_check_matrix(B) != OK)) {
    res = INCORRECT_MATRIX;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (s21_check_matrix(A) != OK) {
    res = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if ((s21_check_matrix(A) != OK) || (s21_check_matrix(B) != OK)) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    res = CALC_ERROR;
  } else {
    result->rows = A->rows;
    result->columns = B->columns;
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (s21_check_matrix(A) != OK) {
    res = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return res;
}

int is_matrix_square(matrix_t *A) {
  int result = SUCCESS;
  if (A->rows != A->columns) {
    result = FAILURE;
  }
  return result;
}

void small_det(matrix_t *A, double *result) {
  *result =
      A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  matrix_t tmp = {0};
  double det = 0;
  s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      calc_minor(A, i, j, &tmp);
      s21_determinant(&tmp, &det);
      result->matrix[i][j] = det * pow(-1, i + j);
    }
  }
  s21_remove_matrix(&tmp);
  return error;
}

int calc_minor(matrix_t *A, int i, int j, matrix_t *result) {
  int error = OK;
  int res_row = 0;
  int res_col = 0;
  for (int k = 0; k < A->rows; k++) {
    for (int l = 0; l < A->columns; l++) {
      if ((k != i) && (l != j)) {
        result->matrix[res_row][res_col] = A->matrix[k][l];
        res_col += 1;
      }
    }
    res_col = 0;
    if (k != i) {
      res_row += 1;
    }
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;
  double tmp = 0;
  int sign = 1;
  *result = 0;
  if (s21_check_matrix(A) != OK) {
    error = INCORRECT_MATRIX;
  } else if (is_matrix_square(A) != SUCCESS) {
    error = CALC_ERROR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    }
    if (A->rows == 2) {
      small_det(A, result);
    }
    if (A->rows > 2) {
      matrix_t minor_m = {0};
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor_m);
      for (int j = 0; j < A->rows; j++) {
        calc_minor(A, 0, j, &minor_m);
        s21_determinant(&minor_m, &tmp);
        tmp *= A->matrix[0][j];
        *result += tmp * sign;
        sign *= -1;
      }
      s21_remove_matrix(&minor_m);
    }
  }
  return error;
}

void read_matrix_from_file(matrix_t *A, char *filename) {
  FILE *fp = fopen(filename, "r");
  double tmp = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      fscanf(fp, "%lf", &tmp);
      A->matrix[i][j] = tmp;
    }
  }
  fclose(fp);
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (s21_check_matrix(A) != OK) {
    error = INCORRECT_MATRIX;
  } else if (is_matrix_square(A) != SUCCESS) {
    error = CALC_ERROR;
  } else {
    matrix_t M_tr = {0};
    matrix_t tmp = {0};
    double det = 0;
    s21_determinant(A, &det);
    if (det == 0) {
      error = CALC_ERROR;
    } else {
      s21_calc_complements(A, &tmp);
      s21_transpose(&tmp, &M_tr);
      s21_mult_number(&M_tr, 1 / det, result);
      s21_remove_matrix(&M_tr);
      s21_remove_matrix(&tmp);
    }
  }
  return error;
}

int s21_check_matrix(matrix_t *A) {
  int error = OK;
  if ((A->rows < 1) || (A->columns < 1) || (A == NULL) || (A->matrix == NULL)) {
    error = INCORRECT_MATRIX;
  }
  return error;
}
