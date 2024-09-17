#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(core, constructors) {
  S21Matrix matrix1 = S21Matrix();
  S21Matrix matrix2(7, 7);
  S21Matrix matrix3(matrix2);
  S21Matrix matrix4(std::move(matrix3));
  S21Matrix const matrix5 = S21Matrix();
}

TEST(eq, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, y);
  S21Matrix matrix3(3, 1);
  bool result = false;

  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix3.ReadMatrixFromFile("./test_files/matrix3.txt");
  result = matrix1.EqMatrix(matrix2);
  ASSERT_EQ(result, true);
  result = matrix1.EqMatrix(matrix3);
  ASSERT_EQ(result, false);
}

TEST(mul_number, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, y);
  double val = 2;

  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("./test_files/test_1.txt");
  matrix1.MulNumber(val);
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(matrix1(i, j) - matrix2(i, j)), 1e-6);
    }
  }
}

TEST(sum, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, y);
  S21Matrix matrix3(x, y);

  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("test_files/matrix2.txt");
  matrix3.ReadMatrixFromFile("test_files/test_2.txt");
  matrix1.SumMatrix(&matrix2);
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(matrix1(i, j) - matrix3(i, j)), 1e-6);
    }
  }
}

TEST(sub, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, y);
  S21Matrix matrix3(x, y);
  S21Matrix matrix_ans(x, y);

  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("test_files/matrix2.txt");
  matrix3.ReadMatrixFromFile("test_files/test_3.txt");
  matrix1.SubMatrix(&matrix2);
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(matrix1(i, j) - matrix3(i, j)), 1e-6);
    }
  }
}

TEST(mul, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, y);
  S21Matrix matrix3(x, y);

  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("./test_files/matrix2.txt");
  matrix3.ReadMatrixFromFile("./test_files/test_4.txt");
  matrix1.MulMatrix(&matrix2);
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(matrix1(i, j) - matrix3(i, j)), 1e-6);
    }
  }
}

TEST(mul, 3x1) {
  int x = 3, y = 3, z = 1;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, z);
  S21Matrix matrix3(x, z);

  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("./test_files/matrix3.txt");
  matrix3.ReadMatrixFromFile("./test_files/test_5.txt");
  matrix1.MulMatrix(&matrix2);
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= z; j++) {
      EXPECT_LT(abs(matrix1(i, j) - matrix3(i, j)), 1e-6);
    }
  }
}

TEST(set_dimension, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1 = S21Matrix(x, y);

  S21Matrix matrix2 = S21Matrix(4, 4);
  S21Matrix matrix3 = S21Matrix(2, 2);

  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("./test_files/test_9.txt");
  matrix3.ReadMatrixFromFile("./test_files/test_10.txt");

  matrix1.SetDimension(4, 4);

  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 4; j++) {
      EXPECT_LT(abs(matrix1(i, j) - matrix2(i, j)), 1e-6);
    }
  }

  matrix1.SetDimension(3, 3);
  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix1.SetDimension(2, 2);

  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= 2; j++) {
      EXPECT_LT(abs(matrix1(i, j) - matrix3(i, j)), 1e-6);
    }
  }
}

TEST(transpose, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1 = S21Matrix(x, y);
  S21Matrix result1 = S21Matrix(x, y);

  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  result1.ReadMatrixFromFile("./test_files/test_11.txt");

  matrix1 = matrix1.Transpose();
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      EXPECT_LT(abs(matrix1(i, j) - result1(i, j)), 1e-6);
    }
  }
}

TEST(transpose, 3x1) {
  S21Matrix matrix1 = S21Matrix(3, 1);
  S21Matrix result1 = S21Matrix(1, 3);
  S21Matrix matrix2 = S21Matrix(1, 3);
  matrix1.ReadMatrixFromFile("./test_files/matrix3.txt");
  result1.ReadMatrixFromFile("./test_files/test_12.txt");
  matrix2 = matrix1.Transpose();
  for (int i = 1; i <= 1; i++) {
    for (int j = 1; j <= 3; j++) {
      EXPECT_LT(abs(matrix2(i, j) - result1(i, j)), 1e-6);
    }
  }
}

TEST(determinant, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  double result1 = 0;
  double result2 = 0;
  std::ifstream input_file;
  input_file.open("./test_files/test_7.txt");
  if (input_file.is_open()) {
    input_file >> result1;
    input_file.close();
  }
  S21Matrix matrix2(x, y);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  result2 = matrix1.Determinant();
  EXPECT_LT(abs(result1 - result2), 1e-6);
}

TEST(determinant, 1x1) {
  S21Matrix matrix1 = S21Matrix();
  ASSERT_EQ(matrix1.Determinant(), 0);
}

TEST(calc_complements, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix result1(x, y);
  S21Matrix matrix2(x, y);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  result1.ReadMatrixFromFile("test_files/test_8.txt");
  matrix2 = matrix1.CalcComplements();
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(result1(i, j) - matrix2(i, j)), 1e-6);
    }
  }
}

TEST(inverse, 3x3) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix result1(x, y);
  S21Matrix matrix2(x, y);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  result1.ReadMatrixFromFile("test_files/test_6.txt");
  matrix2 = matrix1.InverseMatrix();
  matrix1.PrintMatrix();
  matrix2.PrintMatrix();
  result1.PrintMatrix();
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(result1(i, j) - matrix2(i, j)), 1e-6);
    }
  }
}

TEST(operators, plus) {
  int x = 3, y = 3;
  S21Matrix const matrix1(x, y);
  S21Matrix const matrix2(x, y);
  S21Matrix test1(x, y);
  S21Matrix result1(x, y);
  S21Matrix result2(x, y);
  matrix1(1, 1);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("test_files/matrix2.txt");
  test1.ReadMatrixFromFile("test_files/test_2.txt");
  result1 = matrix1;
  result1 += matrix2;
  result2 = matrix1 + matrix2;
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(result1(i, j) - test1(i, j)), 1e-6);
      EXPECT_LT(abs(result2(i, j) - test1(i, j)), 1e-6);
    }
  }
}

TEST(operators, minus) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, y);
  S21Matrix matrix3(x, y);
  S21Matrix result1(x, y);
  S21Matrix result2(x, y);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("test_files/matrix2.txt");
  matrix3.ReadMatrixFromFile("test_files/test_3.txt");
  result1 = matrix1;
  result1 -= matrix2;
  result2 = matrix1 - matrix2;
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(result1(i, j) - matrix3(i, j)), 1e-6);
      EXPECT_LT(abs(result2(i, j) - matrix3(i, j)), 1e-6);
    }
  }
}

TEST(operators, mul_num) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix matrix3(x, y);
  S21Matrix result1(x, y);
  S21Matrix result2(x, y);
  S21Matrix result3(x, y);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix3.ReadMatrixFromFile("test_files/test_1.txt");
  result1 = matrix1;
  result1 *= 2;
  result2 = 2 * matrix1;
  result3 = matrix1 * 2;
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(result1(i, j) - matrix3(i, j)), 1e-6);
      EXPECT_LT(abs(result2(i, j) - matrix3(i, j)), 1e-6);
      EXPECT_LT(abs(result3(i, j) - matrix3(i, j)), 1e-6);
    }
  }
}

TEST(operators, mul_matrix) {
  int x = 3, y = 3, z = 1;
  S21Matrix matrix1(x, y);
  S21Matrix matrix2(x, y);
  S21Matrix matrix3(x, z);
  S21Matrix test1(x, y);
  S21Matrix test2(x, z);
  S21Matrix result1(x, y);
  S21Matrix result2(x, z);
  matrix1.ReadMatrixFromFile("./test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("./test_files/matrix2.txt");
  matrix3.ReadMatrixFromFile("./test_files/matrix3.txt");
  test1.ReadMatrixFromFile("./test_files/test_4.txt");
  test2.ReadMatrixFromFile("./test_files/test_5.txt");
  result1.ReadMatrixFromFile("./test_files/matrix1.txt");
  result1 *= matrix2;
  result2 = matrix1 * matrix3;
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      EXPECT_LT(abs(result1(i, j) - test1(i, j)), 1e-6);
    }
  }

  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= z; j++) {
      EXPECT_LT(abs(result2(i, j) - test2(i, j)), 1e-6);
    }
  }
}

TEST(operators, eq) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix const matrix2(x, y);
  S21Matrix matrix3(x, y);
  S21Matrix const matrix4(x, y);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix3.ReadMatrixFromFile("test_files/matrix2.txt");
  bool result1 = (matrix1 == matrix2);
  bool result2 = (matrix1 == matrix3);
  bool result3 = (matrix2 == matrix3);
  matrix4 = matrix3;
  EXPECT_TRUE(result1);
  EXPECT_FALSE(result2);
  EXPECT_FALSE(result3);
}

TEST(operators, get_set) {
  int x = 3, y = 3;
  S21Matrix matrix1(x, y);
  S21Matrix const matrix2(x, y);
  S21Matrix matrix3(x, y);
  matrix1.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix2.ReadMatrixFromFile("test_files/matrix1.txt");
  matrix3.ReadMatrixFromFile("test_files/matrix2.txt");
  ASSERT_EQ(matrix1.GetRows(), 3);
  ASSERT_EQ(matrix1.GetColumns(), 3);
  matrix1.SetValue(1, 1, 3.14);
  ASSERT_EQ(matrix1.GetValue(1, 1), 3.14);
  matrix1.SetRows(2);
  matrix1.SetColumns(4);
  ASSERT_EQ(matrix1.GetRows(), 2);
  ASSERT_EQ(matrix1.GetColumns(), 4);
  ASSERT_EQ(matrix1(1, 1), 3.14);
}

TEST(errors, invalid_index_get_set) {
  S21Matrix matrix1 = S21Matrix();
  S21Matrix matrix2(2, 2);
  try {
    matrix2.GetValue(3, 6);
  } catch (std::out_of_range &ex1) {
    EXPECT_STREQ(ex1.what(), "Error. Invalid index");
  }

  try {
    matrix2.SetValue(3, 6, 3.14);
  } catch (std::out_of_range &ex2) {
    EXPECT_STREQ(ex2.what(), "Error. Invalid index");
  }

  try {
    matrix2.SetDimension(-1, -2);
  } catch (std::out_of_range &ex3) {
    EXPECT_STREQ(ex3.what(), "Error. Invalid index");
  }
  S21Matrix matrix3(matrix2);
}

TEST(errors, invalid_index_mul) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  S21Matrix matrix2(2, 2);
  S21Matrix matrix3(4, 4);
  try {
    matrix3 = matrix1 * matrix2;
  } catch (std::out_of_range &ex1) {
    EXPECT_STREQ(ex1.what(), "Error. Matrixes can not be multiplied");
  }
}

TEST(errors, invalid_index) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  try {
    printf("%lf\n", matrix1(4, 4));
  } catch (std::out_of_range &ex1) {
    EXPECT_STREQ(ex1.what(), "Error. Invalid index");
  }
  try {
    S21Matrix matrix2(0, -1);
  } catch (std::out_of_range &ex2) {
    EXPECT_STREQ(
        ex2.what(),
        "Error. cannot create matrix with rows or columns less than 1");
  }
}

TEST(errors, invalid_determinant) {
  S21Matrix matrix1 = S21Matrix();
  S21Matrix matrix2(2, 3);
  try {
    matrix2.Determinant();
  } catch (std::out_of_range &ex1) {
    EXPECT_STREQ(ex1.what(), "Error. Matrix should be square");
  }
}

TEST(errors, no_inverse) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  S21Matrix matrix2 = S21Matrix(3, 3);
  matrix1.ReadMatrixFromFile("./test_files/matrix_test.txt");
  try {
    matrix2 = matrix1.InverseMatrix();
  } catch (std::invalid_argument &ex1) {
    EXPECT_STREQ(
        ex1.what(),
        "Error. Matrix do not have a inverse matrix. (determinant = 0)");
  }
}

TEST(errors, sum_wrong_dimensions) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  S21Matrix matrix2 = S21Matrix(2, 2);
  matrix1.ReadMatrixFromFile("./test_files/matrix_test.txt");
  try {
    matrix2 += matrix1;
  } catch (std::out_of_range &ex1) {
    EXPECT_STREQ(ex1.what(), "Error. Matrixes should have the same size");
  }
}

TEST(generic, const_matrix) {
  S21Matrix const matrix1(3, 3);
  matrix1.Determinant();
  matrix1.Transpose();
  try {
    matrix1.InverseMatrix();
  } catch (std::invalid_argument &ex1) {
    EXPECT_STREQ(
        ex1.what(),
        "Error. Matrix do not have a inverse matrix. (determinant = 0)");
  }
  matrix1.CalcComplements();
}
