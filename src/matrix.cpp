#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = new int* [r];
  for(std::size_t i = 0; i < r; i++){
    _data[i] = new int [c];
    for(std::size_t j = 0; j < _cols; j++){
      _data[i][j] = 0;
    }
  }
}

Matrix::Matrix(const Matrix& m) {
  _rows = m._rows;
  _cols = m._cols;
  _data = new int* [_rows];
  for(std::size_t i = 0; i < _rows; i++){
    _data[i] = new int [_cols];
    for(std::size_t j = 0; j < _cols; j++){
      _data[i][j] = m._data[i][j];
    }
  }
}

Matrix::~Matrix(){
  for(std::size_t i = 0; i < _rows; i++){
    delete(_data[i]);
  }
  delete(_data);
}

std::size_t Matrix::get_rows() { return _rows; }

std::size_t Matrix::get_cols() { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) {
  return _data[i][j];
}

void Matrix::print(FILE* f) {
  for(std::size_t i = 0; i < _rows; i++){
    for(std::size_t j = 0; j < _cols; j++){
      fprintf(f, "%d ", _data[i][j]);
    }
    fprintf(f, "\n");
  }
}

bool Matrix::operator==(const Matrix& m) {
  if(_rows != m._rows || _cols != m._cols) return false;
  for(std::size_t i = 0; i < _rows; i++){
    for(size_t j = 0; j < _cols; j++){
      if(!(_data[i][j] == m._data[i][j])) return false;
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& m) {
  return !(*this == m);
}

Matrix& Matrix::operator=(const Matrix& m){
  Matrix tmp(m);
  std::swap(_data, tmp._data);
  std::swap(_rows, tmp._rows);
  std::swap(_cols, tmp._cols);
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
  for(std::size_t i = 0; i < _rows; i++){
    for(std::size_t j = 0; j < _cols; j++){
      _data[i][j] += m._data[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  for(std::size_t i = 0; i < _rows; i++){
    for(std::size_t j = 0; j < _cols; j++){
      _data[i][j] -= m._data[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  *this = *this * m;
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) {
  Matrix res(m);
  res += (*this);
  return res;
}

Matrix Matrix::operator-(const Matrix& m) {
  Matrix res(m);
  res -= (*this);
  return res;
}

Matrix Matrix::operator*(const Matrix& m) {
  Matrix ans(_rows, m._cols);
    for(std::size_t i = 0; i < _rows; i++){
      for(std::size_t j = 0; j < m._cols; j++){
        int res = 0;
        for(std::size_t k = 0; k < _cols; k++){
          res += _data[i][k] * m._data[k][j];
        }
      ans._data[i][j] = res;
    }
  }
  return ans;
}
