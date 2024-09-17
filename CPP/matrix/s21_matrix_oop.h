#ifndef CPP1_S21_MATRIXPLUS_5_SRC_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_5_SRC_S21_MATRIX_OOP_H

#include <math.h>

#include <cstdio>
#include <fstream>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows_val, int cols_val);
  S21Matrix(const S21Matrix &m);
  S21Matrix(S21Matrix &m);
  S21Matrix(const S21Matrix &&m);
  S21Matrix(S21Matrix &&m);
  ~S21Matrix();

  int GetRows() const;
  int GetColumns() const;
  void SetRows(int rows);
  void SetColumns(int columns);
  double GetValue(int rows, int columns) const;
  void SetValue(int rows, int columns, double value);
  void SetDimension(int x, int y);

  friend S21Matrix operator+(S21Matrix const &m1, S21Matrix const &m2);
  friend S21Matrix operator-(S21Matrix const &m1, S21Matrix const &m2);
  friend S21Matrix operator*(S21Matrix const &m1, S21Matrix const &m2);
  friend S21Matrix operator*(double val, S21Matrix const &m);
  friend S21Matrix operator*(S21Matrix const &m, double val);

  double operator()(int x, int y) const;
  double operator()(int x, int y);
  S21Matrix &operator=(S21Matrix const &m);
  S21Matrix const &operator=(S21Matrix const &m) const;
  S21Matrix &operator=(S21Matrix &&m) noexcept;
  friend bool operator==(S21Matrix const &m1, S21Matrix const &m2);
  S21Matrix &operator+=(S21Matrix const &m);
  S21Matrix &operator-=(S21Matrix const &m);
  S21Matrix &operator*=(double const val);
  S21Matrix &operator*=(S21Matrix const &m);

  bool EqMatrix(const S21Matrix &m) const noexcept;
  void SumMatrix(const S21Matrix *m);
  void SubMatrix(const S21Matrix *m);
  void MulNumber(double const val) noexcept;
  void MulMatrix(const S21Matrix *m);
  S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  void PrintMatrix() const;
  void ReadMatrixFromFile(std::string filename) const;

 private:
  int rows_, cols_;
  double *data_;
  void CheckDimension(S21Matrix const *m1, S21Matrix const *m2) const;
  void AllocateMemory();
  void CopyObject(S21Matrix &m);
  void CopyObject(S21Matrix const &m) const;
  void CheckIndex(int rows, int columns) const;
  double SmallDet() const;
  S21Matrix CalcMinor(int i, int j) const;
};

S21Matrix operator+(S21Matrix const &m1, S21Matrix const &m2);
S21Matrix operator-(S21Matrix const &m1, S21Matrix const &m2);
S21Matrix operator*(double val, S21Matrix const &m);
S21Matrix operator*(S21Matrix const &m1, S21Matrix const &m2);
S21Matrix operator*(S21Matrix const &m, double val);
bool operator==(S21Matrix const &m1, S21Matrix const &m2);

#endif  // CPP1_S21_MATRIXPLUS_5_SRC_S21_MATRIX_OOP_H
