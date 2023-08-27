#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"

TEST(test_contructors, test_basic_con) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

TEST(test_contructors, test_parametrized_con_1) {
  S21Matrix m(3, 3);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(test_contructors, test_parametrized_con_2) {
  EXPECT_THROW({ S21Matrix m(1, 0); }, std::invalid_argument);
  EXPECT_THROW({ S21Matrix m(-1, -1); }, std::invalid_argument);
}

TEST(test_contructors, test_copy_con) {
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m2[i][j] = ++counter;
    }
  }

  S21Matrix m1(m2);

  EXPECT_TRUE(m1 == m2);
}

TEST(test_contructors, test_move_con) {
  S21Matrix m2(3, 3);
  S21Matrix m1(std::move(m2));

  EXPECT_EQ(m2.GetCols(), 0);
  EXPECT_EQ(m2.GetRows(), 0);

  EXPECT_EQ(m1.GetRows(), 3);
  EXPECT_EQ(m1.GetRows(), 3);
}

TEST(test_operations, test_eqmatrix) {
  S21Matrix m2(3, 3);

  int counter = 0;
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      m2[i][j] = ++counter;
    }
  }

  S21Matrix m1(m2);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(test_operations, test_summatrix_1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m2[i][j] = ++counter;
      m1[i][j] = counter * 2;
    }
  }

  S21Matrix res(m2);
  res.SumMatrix(m2);

  EXPECT_TRUE(res == m1);
}

TEST(test_operations, test_summatrix_2) {
  S21Matrix m2(3, 3);
  S21Matrix m1(1, 2);

  EXPECT_THROW(m1.SumMatrix(m2), std::logic_error);
}

TEST(test_operations, test_submatrix_1) {
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m2[i][j] = ++counter;
    }
  }

  S21Matrix m1(m2);
  m1.SubMatrix(m2);

  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      EXPECT_NEAR(m1[i][j], 0, PRECISION);
    }
  }
}

TEST(test_operations, test_submatrix_2) {
  S21Matrix m2(3, 3);
  S21Matrix m1(1, 2);

  EXPECT_THROW(m1.SubMatrix(m2), std::logic_error);
}

TEST(test_operations, test_mulmatrix) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m1[i][j] = ++counter;
      m2[i][j] = counter * 2;
    }
  }

  m1.MulNumber(2);

  EXPECT_TRUE(m1 == m2);
}

TEST(test_operations, test_mulmatrix_2x2) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  m1(0, 0) = 4;
  m1(0, 1) = 2;
  m1(1, 0) = 9;
  m1(1, 1) = 0;

  m2(0, 0) = 3;
  m2(0, 1) = 1;
  m2(1, 0) = -3;
  m2(1, 1) = 4;

  m1.MulMatrix(m2);

  EXPECT_EQ(m1(0, 0), 6);
  EXPECT_EQ(m1(0, 1), 12);
  EXPECT_EQ(m1(1, 0), 27);
  EXPECT_EQ(m1(1, 1), 9);
}

TEST(test_operations, test_mulmatrix_2x3_3x2) {
  S21Matrix m1(3, 2);
  S21Matrix m2(2, 3);

  m1(0, 0) = 2;
  m1(0, 1) = 1;
  m1(1, 0) = -3;
  m1(1, 1) = 0;
  m1(2, 0) = 4;
  m1(2, 1) = -1;

  m2(0, 0) = 5;
  m2(0, 1) = -1;
  m2(0, 2) = 6;
  m2(1, 0) = -3;
  m2(1, 1) = 0;
  m2(1, 2) = 7;

  m1.MulMatrix(m2);

  EXPECT_EQ(m1(0, 0), 7);
  EXPECT_EQ(m1(0, 1), -2);
  EXPECT_EQ(m1(0, 2), 19);
  EXPECT_EQ(m1(1, 0), -15);
  EXPECT_EQ(m1(1, 1), 3);
  EXPECT_EQ(m1(1, 2), -18);
  EXPECT_EQ(m1(2, 0), 23);
  EXPECT_EQ(m1(2, 1), -4);
  EXPECT_EQ(m1(2, 2), 17);
}

TEST(test_operations, test_mulmatrix_3x3) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 1) = 4;
  m1(0, 2) = 3;
  m1(1, 0) = 2;
  m1(1, 1) = 1;
  m1(1, 2) = 5;
  m1(2, 0) = 3;
  m1(2, 1) = 2;
  m1(2, 2) = 1;

  m2(0, 0) = 5;
  m2(0, 1) = 2;
  m2(0, 2) = 1;
  m2(1, 0) = 4;
  m2(1, 1) = 3;
  m2(1, 2) = 2;
  m2(2, 0) = 2;
  m2(2, 1) = 1;
  m2(2, 2) = 5;

  m1.MulMatrix(m2);

  EXPECT_EQ(m1(0, 0), 27);
  EXPECT_EQ(m1(0, 1), 17);
  EXPECT_EQ(m1(0, 2), 24);
  EXPECT_EQ(m1(1, 0), 24);
  EXPECT_EQ(m1(1, 1), 12);
  EXPECT_EQ(m1(1, 2), 29);
  EXPECT_EQ(m1(2, 0), 25);
  EXPECT_EQ(m1(2, 1), 13);
  EXPECT_EQ(m1(2, 2), 12);
}

TEST(test_operations, test_transpose) {
  int rows = 2, cols = 3, counter = 1;

  S21Matrix m1(rows, cols);
  S21Matrix m2(cols, rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1[i][j] = counter;
      m2[j][i] = counter;
    }
  }

  m1 = m1.Transpose();
  EXPECT_TRUE(m1 == m2);
}

TEST(test_operations, test_calccomplements_1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[0][2] = 3;
  m1[1][0] = 0;
  m1[1][1] = 4;
  m1[1][2] = 2;
  m1[2][0] = 5;
  m1[2][1] = 2;
  m1[2][2] = 1;

  S21Matrix res = m1.CalcComplements();

  m2[0][0] = 0;
  m2[0][1] = 10;
  m2[0][2] = -20;
  m2[1][0] = 4;
  m2[1][1] = -14;
  m2[1][2] = 8;
  m2[2][0] = -8;
  m2[2][1] = -2;
  m2[2][2] = 4;

  EXPECT_TRUE(res == m2);
}

TEST(test_operations, test_calccomplements_2) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1[0][0] = 5;
  m1[0][1] = -1;
  m1[0][2] = 1;
  m1[1][0] = 2;
  m1[1][1] = 3;
  m1[1][2] = 4;
  m1[2][0] = 1;
  m1[2][1] = 0;
  m1[2][2] = 3;

  S21Matrix res = m1.CalcComplements();

  m2[0][0] = 9;
  m2[0][1] = -2;
  m2[0][2] = -3;
  m2[1][0] = 3;
  m2[1][1] = 14;
  m2[1][2] = -1;
  m2[2][0] = -7;
  m2[2][1] = -18;
  m2[2][2] = 17;

  EXPECT_TRUE(res == m2);
}

TEST(test_operations, test_calccomplements_3) {
  S21Matrix m1(3, 2);

  EXPECT_THROW(m1.CalcComplements(), std::logic_error);
}

TEST(test_operations, test_determinant_1) {
  S21Matrix m1(3, 4);

  EXPECT_ANY_THROW(m1.Determinant());
}

TEST(test_operations, test_determinant_2) {
  double expect = 18;

  S21Matrix m1(4, 4);

  m1[0][0] = 3;
  m1[0][1] = -3;
  m1[0][2] = -5;
  m1[0][3] = 8;
  m1[1][0] = -3;
  m1[1][1] = 2;
  m1[1][2] = 4;
  m1[1][3] = -6;
  m1[2][0] = 2;
  m1[2][1] = -5;
  m1[2][2] = -7;
  m1[2][3] = 5;
  m1[3][0] = -4;
  m1[3][1] = 3;
  m1[3][2] = 5;
  m1[3][3] = -6;

  EXPECT_NEAR(m1.Determinant(), expect, PRECISION);
}

TEST(test_operations, test_determinant_3) {
  double expect = 2480;

  S21Matrix m1(5, 5);

  m1[0][1] = 6;
  m1[0][2] = -2;
  m1[0][3] = -1;
  m1[0][4] = 5;
  m1[1][3] = -9;
  m1[1][4] = -7;
  m1[2][1] = 15;
  m1[2][2] = 35;
  m1[3][1] = -1;
  m1[3][2] = -11;
  m1[3][3] = -2;
  m1[3][4] = 1;
  m1[4][0] = -2;
  m1[4][1] = -2;
  m1[4][2] = 3;
  m1[4][4] = -2;

  EXPECT_NEAR(m1.Determinant(), expect, PRECISION);
}

TEST(test_operations, test_inverse_1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m2[0][0] = 44300.0 / 367429.0;
  m2[0][1] = -236300.0 / 367429.0;
  m2[0][2] = 200360.0 / 367429.0;
  m2[1][0] = 20600.0 / 367429.0;
  m2[1][1] = 56000.0 / 367429.0;
  m2[1][2] = -156483.0 / 367429.0;
  m2[2][0] = 30900.0 / 367429.0;
  m2[2][1] = 84000.0 / 367429.0;
  m2[2][2] = -51010.0 / 367429.0;

  m1[0][0] = 2.8;
  m1[0][1] = 1.3;
  m1[0][2] = 7.01;
  m1[1][0] = -1.03;
  m1[1][1] = -2.3;
  m1[1][2] = 3.01;
  m1[2][0] = 0;
  m1[2][1] = -3;
  m1[2][2] = 2;

  EXPECT_TRUE(m1.InverseMatrix() == m2);
}

TEST(test_operations, test_inverse_2) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m2[0][0] = 1.0;
  m2[0][1] = -1.0;
  m2[0][2] = 1.0;
  m2[1][0] = -38.0;
  m2[1][1] = 41.0;
  m2[1][2] = -34.0;
  m2[2][0] = 27.0;
  m2[2][1] = -29.0;
  m2[2][2] = 24.0;

  m1[0][0] = 2.0;
  m1[0][1] = 5.0;
  m1[0][2] = 7.0;
  m1[1][0] = 6.0;
  m1[1][1] = 3.0;
  m1[1][2] = 4.0;
  m1[2][0] = 5.0;
  m1[2][1] = -2.0;
  m1[2][2] = -3.0;

  EXPECT_TRUE(m1.InverseMatrix() == m2);
}

TEST(test_operations, test_inverse_3) {
  S21Matrix m1(3, 1);

  EXPECT_ANY_THROW(m1.InverseMatrix());
}

TEST(test_operations, test_inverse_4) {
  S21Matrix m1(1, 1);
  m1[0][0] = 69.420;

  EXPECT_NEAR(m1.InverseMatrix()[0][0], 1 / 69.420, PRECISION);
}

TEST(test_operators, test_plus_1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  S21Matrix res(3, 3);
  S21Matrix expect(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m1[i][j] = ++counter;
      expect[i][j] = counter * 2;
    }
  }

  m2 = m1;
  res = m2 + m1;

  EXPECT_TRUE(res == expect);
}

TEST(test_operators, test_plus_2) {
  S21Matrix m1(3, 2);
  S21Matrix m2(2, 3);

  EXPECT_ANY_THROW(m1 + m2);
}

TEST(test_operators, test_plusequal) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  S21Matrix expect(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m1[i][j] = ++counter;
      expect[i][j] = counter * 2;
    }
  }

  m2 = m1;
  m2 += m1;

  EXPECT_TRUE(m2 == expect);
}

TEST(test_operators, test_minus_1) {
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m2[i][j] = ++counter;
    }
  }

  S21Matrix m1(m2);
  S21Matrix res = m1 - m2;

  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      EXPECT_NEAR(res[i][j], 0, PRECISION);
    }
  }
}

TEST(test_operators, test_minus_2) {
  S21Matrix m1(3, 2);
  S21Matrix m2(2, 3);

  EXPECT_ANY_THROW(m1 - m2);
}

TEST(test_operators, test_minusequal) {
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m2[i][j] = ++counter;
    }
  }

  S21Matrix m1(m2);
  m1 -= m2;

  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      EXPECT_NEAR(m1[i][j], 0, PRECISION);
    }
  }
}

TEST(test_operators, test_multiply_matrix_number) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m1[i][j] = ++counter;
      m2[i][j] = counter * 2;
    }
  }

  m1 = m1 * 2;

  EXPECT_TRUE(m1 == m2);
}

TEST(test_operators, test_multiply_number_matrix) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m1[i][j] = ++counter;
      m2[i][j] = counter * 2;
    }
  }

  m1 = 2 * m1;

  EXPECT_TRUE(m1 == m2);
}

TEST(test_operators, test_multiplyequal) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  int counter = 0, i = 0, j = 0;
  for (i = 0; i != 3; ++i) {
    for (j = 0; j != 3; ++j) {
      m1[i][j] = ++counter;
      m2[i][j] = counter * 2;
    }
  }

  m1 *= 2;

  EXPECT_TRUE(m1 == m2);
}
