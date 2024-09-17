#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows_val, int cols_val)
    : rows_(rows_val), cols_(cols_val) {
  if ((rows_val < 1) || (cols_val < 1)) {
    throw std::out_of_range(
        "Error. cannot create matrix with rows or columns less than 1");
  }
  data_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix &m) : rows_(m.rows_), cols_(m.cols_) {
  data_ = new double[rows_ * cols_]();
  CopyObject(m);
}

S21Matrix::S21Matrix(S21Matrix &m) : rows_(m.rows_), cols_(m.cols_) {
  data_ = new double[rows_ * cols_]();
  CopyObject(m);
}

S21Matrix::S21Matrix(S21Matrix &&m) : rows_(m.rows_), cols_(m.cols_) {
  if (this != &m) {
    data_ = m.data_;
    m.data_ = nullptr;
  }
}

S21Matrix::~S21Matrix() {
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
  }
}
void S21Matrix::CheckIndex(int rows, int columns) const {
  if ((rows_ < rows) || (cols_ < columns) || rows < 1 || columns < 1) {
    throw std::out_of_range("Error. Invalid index");
  }
}

void S21Matrix::CopyObject(S21Matrix &m) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      data_[i * cols_ + j] = m.data_[i * cols_ + j];
    }
  }
}

void S21Matrix::CopyObject(S21Matrix const &m) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      data_[i * cols_ + j] = m.data_[i * cols_ + j];
    }
  }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetColumns() const { return cols_; }

double S21Matrix::GetValue(int rows, int columns) const {
  CheckIndex(rows, columns);
  return data_[(rows - 1) * (columns - 1) + (columns - 1)];
}

void S21Matrix::SetRows(int rows) { SetDimension(rows, cols_); }

void S21Matrix::SetColumns(int columns) { SetDimension(rows_, columns); }

void S21Matrix::SetValue(int rows, int columns, double value) {
  CheckIndex(rows, columns);
  data_[(rows - 1) * (columns - 1) + (columns - 1)] = value;
}

void S21Matrix::SetDimension(int new_rows, int new_cols) {
  if ((new_rows < 1) || (new_cols < 1)) {
    throw std::out_of_range("Error. Invalid index");
  }
  double *tmp = new double[new_rows * new_cols]();
  int ind1 = rows_, ind2 = cols_;
  if (new_rows < rows_) {
    ind1 = new_rows;
  }
  if (new_cols < cols_) {
    ind2 = new_cols;
  }
  for (int i = 0; i < ind1; i++) {
    for (int j = 0; j < ind2; j++) {
      tmp[i * new_cols + j] = data_[i * cols_ + j];
    }
  }
  if (data_ != nullptr) {
    delete[] data_;
    data_ = nullptr;
  }
  rows_ = new_rows;
  cols_ = new_cols;
  data_ = tmp;
}

void S21Matrix::CheckDimension(S21Matrix const *m1, S21Matrix const *m2) const {
  if ((m1->rows_ != m2->rows_) || (m1->cols_ != m2->cols_)) {
    throw std::out_of_range("Error. Matrixes should have the same size");
  }
}

void S21Matrix::ReadMatrixFromFile(std::string filename) const {
  std::ifstream input_file;
  input_file.open(filename.c_str());
  if (input_file.is_open()) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        input_file >> data_[i * cols_ + j];
      }
    }
    input_file.close();
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &m) const noexcept {
  if ((rows_ != m.rows_ || (cols_ != m.cols_))) {
    return false;
  }
  for (int i = 0; (i < rows_); i++) {
    for (int j = 0; (j < cols_); j++) {
      if (abs(data_[i * cols_ + j] - m.data_[i * cols_ + j]) >= 1e-6) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix *m) {
  CheckDimension(this, m);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      data_[i * cols_ + j] += m->data_[i * cols_ + j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix *m) {
  CheckDimension(this, m);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      data_[i * cols_ + j] -= m->data_[i * cols_ + j];
    }
  }
}

void S21Matrix::MulNumber(double const val) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      data_[i * cols_ + j] *= val;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix *m) {
  if (cols_ != m->rows_) {
    throw std::out_of_range("Error. Matrixes can not be multiplied");
  } else {
    double *result = new double[rows_ * m->cols_]();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < m->cols_; j++) {
        for (int k = 0; k < cols_; k++) {
          result[i * m->cols_ + j] +=
              data_[i * cols_ + k] * m->data_[k * m->cols_ + j];
        }
      }
    }
    cols_ = m->cols_;
    delete[] data_;
    data_ = result;
  }
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.data_[i * result.cols_ + j] = data_[j * cols_ + i];
    }
  }
  return result;
}

double S21Matrix::SmallDet() const {
  return data_[0] * data_[3] - data_[1] * data_[2];
}

S21Matrix S21Matrix::CalcMinor(int i, int j) const {
  S21Matrix result(rows_ - 1, cols_ - 1);
  int count = 0;
  for (int k = 0; k < rows_; k++) {
    for (int l = 0; l < cols_; l++) {
      if ((k != i) && (l != j)) {
        result.data_[count] = data_[k * rows_ + l];
        count++;
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::out_of_range("Error. Matrix should be square");
  }
  if (rows_ == 1) {
    return data_[0];
  }
  if (rows_ == 2) {
    return SmallDet();
  }
  int sign = 1;
  double tmp = 0, result = 0;
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    minor = CalcMinor(0, i);
    tmp = minor.Determinant() * data_[i];
    result += tmp * sign;
    sign *= -1;
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);
  double tmp_det = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      minor = CalcMinor(i, j);
      tmp_det = minor.Determinant();
      result.data_[i * cols_ + j] = tmp_det * pow(-1, i + j);
    }
  }
  return result.Transpose();
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument(
        "Error. Matrix do not have a inverse matrix. (determinant = 0)");
  }
  S21Matrix tmp(rows_, cols_);
  tmp = CalcComplements();
  tmp *= (1 / det);
  return tmp;
}

void S21Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      printf("%.6lf ", data_[i * cols_ + j]);
    }
    printf("\n");
  }
  printf("\n");
}

double S21Matrix::operator()(int x, int y) const {
  CheckIndex(x, y);
  return data_[(x - 1) * cols_ + (y - 1)];
}

double S21Matrix::operator()(int x, int y) {
  CheckIndex(x, y);
  return data_[(x - 1) * cols_ + (y - 1)];
}

S21Matrix &S21Matrix::operator+=(S21Matrix const &m) {
  SumMatrix(&m);
  return *this;
}

S21Matrix operator+(S21Matrix const &m1, S21Matrix const &m2) {
  S21Matrix result(m1);
  result += m2;
  return result;
}

S21Matrix &S21Matrix::operator-=(S21Matrix const &m) {
  SubMatrix(&m);
  return *this;
}

S21Matrix operator-(S21Matrix const &m1, S21Matrix const &m2) {
  S21Matrix result(m1);
  result -= m2;
  return result;
}

S21Matrix &S21Matrix::operator*=(S21Matrix const &m) {
  MulMatrix(&m);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double const val) {
  MulNumber(val);
  return *this;
}

S21Matrix operator*(double val, S21Matrix const &m) {
  S21Matrix result(m);
  result.MulNumber(val);
  return result;
}

S21Matrix operator*(S21Matrix const &m1, S21Matrix const &m2) {
  S21Matrix result(m1);
  result *= m2;
  return result;
}

S21Matrix operator*(S21Matrix const &m, const double val) {
  S21Matrix result(m);
  result.MulNumber(val);
  return result;
}

S21Matrix &S21Matrix::operator=(S21Matrix const &m) {
  CheckDimension(this, &m);
  if (this == &m) {
    return *this;
  }
  CopyObject(m);
  return *this;
}

S21Matrix const &S21Matrix::operator=(S21Matrix const &m) const {
  CheckDimension(this, &m);
  if (this == &m) {
    return *this;
  }
  CopyObject(m);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&m) noexcept {
  CheckDimension(this, &m);
  if (this != &m) {
    rows_ = m.rows_;
    cols_ = m.cols_;
    if (data_ != nullptr) {
      delete[] data_;
    }
    data_ = m.data_;
    m.data_ = nullptr;
  }
  return *this;
}

bool operator==(S21Matrix const &m1, S21Matrix const &m2) {
  return m1.EqMatrix(m2);
}
