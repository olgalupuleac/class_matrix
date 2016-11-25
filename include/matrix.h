#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <cstdio>
#include <cstddef>
#include <algorithm>

class Matrix {
public:
  Matrix(std::size_t r, std::size_t c);
  Matrix(const Matrix& m);
  ~Matrix();
  std::size_t get_rows();
  std::size_t get_cols();
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j);
  void print(FILE *f);
  Matrix& operator=(const Matrix& m);
  Matrix operator+(const Matrix& m);
  Matrix operator-(const Matrix& m);
  Matrix operator*(const Matrix& m);
  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);
  bool operator==(const Matrix& m);
  bool operator!=(const Matrix& m);
private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};


#endif // MATRIX_H_INCLUDED
