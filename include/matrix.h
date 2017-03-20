#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <istream>
#include <ostream>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <exception>
#include <string>

class MatrixException {
public:
    MatrixException(const std::string& what_happend);
    std::string what() const;
private:
    std::string _error;
};

class Matrix {
private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;

    class row {
    private:
        int* const _matrix_row;
        const std::size_t _matrix_cols;
    public:
        row(int* matrix_row, std::size_t matrix_cols);
        int& operator[](std::size_t col_index);
    };

    class const_row {
    private:
        const int* const _matrix_row;
        const std::size_t _matrix_cols;
    public:
        const_row(const int* matrix_row, std::size_t matrix_cols);
        int operator[](std::size_t col_index) const;
    };
public:
    Matrix();
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(const Matrix& m);
    ~Matrix();
    std::size_t rows() const;
    std::size_t cols() const;
    Matrix& operator=(Matrix other);
    row operator[](std::size_t row_index);
    const_row operator[](std::size_t row_index) const;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix& operator*=(Matrix& lhs, const Matrix& rhs);
bool operator==(const Matrix& lhs, const Matrix& rhs);
bool operator!=(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Matrix& operator+=(Matrix& lhs, const Matrix& rhs);
Matrix& operator-=(Matrix& lhs, const Matrix& rhs);

std::ostream& operator<<(std::ostream& os, const Matrix& m);
std::istream& operator>>(std::istream& is, Matrix& m);

#endif // MATRIX_H_INCLUDED