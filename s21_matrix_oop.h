#pragma once

#include <cmath>
#include <iostream>

#define PRECISION 1e-7

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows);
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& o) noexcept;
  S21Matrix(S21Matrix&& o) noexcept;
  ~S21Matrix();

  S21Matrix& operator=(const S21Matrix& o);
  S21Matrix& operator=(S21Matrix&& o);
  double& operator()(int row, int col) const;
  double* operator[](int row) const;
  bool operator==(const S21Matrix& o) const noexcept;
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix operator+(const S21Matrix& o) const;
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o) const;
  S21Matrix& operator*=(const double& o) noexcept;
  S21Matrix operator*(const double& o) const noexcept;
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o) const;

  bool EqMatrix(const S21Matrix& o) const noexcept;
  void SumMatrix(const S21Matrix& o);
  void SubMatrix(const S21Matrix& o);
  void MulNumber(const double o) noexcept;
  void MulMatrix(const S21Matrix& o);

  S21Matrix Transpose() const noexcept;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int);
  void SetCols(int);
  friend std::ostream& operator<<(std::ostream& out, const S21Matrix& o) noexcept;
  friend std::istream& operator>>(std::istream& in, S21Matrix& o) noexcept;
  friend S21Matrix operator*(const double& o1, const S21Matrix& o2) noexcept;

 private:
  int rows_, cols_;
  double* matrix_;
};