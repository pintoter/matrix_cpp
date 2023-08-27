#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows) {
  if (rows < 1)
    throw std::invalid_argument("Sizes of rows or cols must be greater than 0");

  rows_ = rows;
  cols_ = rows;
  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument("Sizes of rows or cols must be greater than 0");

  rows_ = rows;
  cols_ = cols;
  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix& o) noexcept
    : rows_(o.rows_), cols_(o.cols_), matrix_(new double[o.rows_ * o.cols_]()) {
  std::copy(o.matrix_, o.matrix_ + rows_ * cols_, matrix_);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (this == &o) return *this;

  double* ptr = new double[o.rows_ * o.cols_]();
  delete[] matrix_;

  rows_ = o.rows_;
  cols_ = o.cols_;
  matrix_ = ptr;
  std::copy(o.matrix_, o.matrix_ + rows_ * cols_, matrix_);
  return *this;
}

S21Matrix::S21Matrix(S21Matrix&& o) noexcept
    : rows_(o.rows_), cols_(o.cols_), matrix_(o.matrix_) {
  o.rows_ = 0;
  o.cols_ = 0;
  o.matrix_ = nullptr;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& o) {
  if (this == &o) return *this;

  delete[] matrix_;

  rows_ = o.rows_;
  cols_ = o.cols_;
  matrix_ = o.matrix_;

  o.rows_ = 0;
  o.cols_ = 0;
  o.matrix_ = nullptr;
  return *this;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

double& S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0)
    throw std::out_of_range("Incorrect parametrs of Matrix");

  return matrix_[rows * cols_ + cols];
}

double* S21Matrix::operator[](int rows) const {
  if (rows >= rows_ || rows < 0)
    throw std::out_of_range("Incorrect parametrs of Matrix");

  return matrix_ + rows * cols_;
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1)
    throw std::invalid_argument("The number of rows must be greater than 0");

  S21Matrix temp(rows, cols_);

  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols_; ++j) {
      temp[i][j] = i < rows_ ? (*this)[i][j] : 0;
    }
  }

  *this = std::move(temp);
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1)
    throw std::invalid_argument("The number of cols must be greater than 0");

  S21Matrix temp(rows_, cols);

  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols; ++j) {
      temp[i][j] = j < cols_ ? (*this)[i][j] : 0;
    }
  }

  *this = std::move(temp);
}

std::istream& operator>>(std::istream& in, S21Matrix& o) noexcept {
  for (int i = 0; i != o.rows_ * o.cols_; ++i) {
    in >> o.matrix_[i];
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const S21Matrix& o) noexcept {
  for (int i = 0; i != o.rows_; ++i) {
    for (int j = 0; j != o.cols_; ++j) {
      out << o.matrix_[i * o.cols_ + j] << " ";
    }
    out << "\n";
  }
  return out;
}

bool S21Matrix::EqMatrix(const S21Matrix& o) const noexcept {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    return false;
  }

  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      if (fabs((*this)[i][j] - o[i][j]) > PRECISION) {
        return false;
      }
    }
  }
  return true;
}

bool S21Matrix::operator==(const S21Matrix& o) const noexcept {
  return EqMatrix(o);
}

void S21Matrix::SumMatrix(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_)
    throw std::logic_error("Matrices have different size of parametrs");

  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      (*this)[i][j] += o[i][j];
    }
  }
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  SumMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) const {
  S21Matrix res(*this);

  res.SumMatrix(o);

  return res;
}

void S21Matrix::SubMatrix(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::logic_error("Matrices have different size of parametrs");
  }

  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      (*this)[i][j] -= o[i][j];
    }
  }
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  SubMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) const {
  S21Matrix res(*this);

  res.SubMatrix(o);

  return res;
}

void S21Matrix::MulNumber(const double o) noexcept {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      (*this)[i][j] *= o;

      if (fabs((*this)[i][j]) < PRECISION) {
        (*this)[i][j] = 0;
      }
    }
  }
}

S21Matrix& S21Matrix::operator*=(const double& o) noexcept {
  this->MulNumber(o);
  return *this;
}

S21Matrix S21Matrix::operator*(const double& o) const noexcept {
  S21Matrix res(*this);

  res.MulNumber(o);

  return res;
}

S21Matrix operator*(const double& o1, const S21Matrix& o2) noexcept {
  S21Matrix res(o2);
  return res *= o1;
}

void S21Matrix::MulMatrix(const S21Matrix& o) {
  if (cols_ != o.rows_ || o.cols_ < 1) {
    throw std::logic_error(
        "The required parameters of matrix have different sizes");
  }

  S21Matrix temp(rows_, o.cols_);

  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != o.cols_; ++j) {
      for (int k = 0; k != cols_; ++k) {
        temp[i][j] += (*this)[i][k] * o[k][j];

        if (fabs(temp[i][j]) < PRECISION) {
          temp[i][j] = 0;
        }
      }
    }
  }

  *this = std::move(temp);
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  this->MulMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) const {
  S21Matrix res(*this);

  res.MulMatrix(o);

  return res;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix res(cols_, rows_);

  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      res[j][i] = (*this)[i][j];
    }
  }
  return res;
}

int get_sign(int& row, int& col) { return (row + col) % 2 == 0 ? 1 : -1; }

void fill_matrix(const S21Matrix& in, S21Matrix& out, const int& skip_row,
                 const int& skip_col) {
  int row = 0;

  for (int i = 0; i != in.GetRows(); ++i) {
    if (i != skip_row) {
      int col = 0;

      for (int j = 0; j != in.GetCols(); ++j) {
        if (j != skip_col) {
          out[row][col] = in[i][j];
          ++col;
        }
      }

      ++row;
    }
  }
}

double det(const S21Matrix& in, int size) {
  if (size == 1) {
    return in[0][0];
  }

  double res = 0;
  int row = 0;

  S21Matrix temp(size);

  for (int i = 0; i != size; ++i) {
    fill_matrix(in, temp, row, i);
    res += get_sign(row, i) * in[row][i] * det(temp, temp.GetCols() - 1);
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::logic_error("The matrix isn't squared");

  S21Matrix res(rows_);

  if (rows_ == 1) {
    res[0][0] = 1;
    return res;
  }

  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      S21Matrix temp(rows_ - 1);
      fill_matrix(*this, temp, i, j);
      res[i][j] = get_sign(i, j) * det(temp, temp.GetCols());
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix isn't squared");
  }

  return det(*this, rows_);
}

S21Matrix S21Matrix::InverseMatrix() const {
  double res_det = det(*this, rows_);

  if (fabs(res_det) < PRECISION) {
    throw std::logic_error(
        "The determinant is 0, the inverse matrix isn't exists");
  }

  S21Matrix res(CalcComplements().Transpose());
  res *= 1 / res_det;
  return res;
}
