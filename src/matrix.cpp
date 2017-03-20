#include "matrix.h"

MatrixException::MatrixException(const std::string& what_happend) 
    : _error(what_happend){}

std::string MatrixException::what() const{
    return _error;
}

Matrix::Matrix() 
    : _rows(0)
    , _cols(0)
    , _data(NULL){}

Matrix::row::row(int* matrix_row, std::size_t matrix_cols) 
    : _matrix_row(matrix_row)
    , _matrix_cols(matrix_cols) {}

Matrix::const_row::const_row(const int* matrix_row, std::size_t matrix_cols) 
    : _matrix_row(matrix_row)
    , _matrix_cols(matrix_cols) {}

int& Matrix::row::operator[](std::size_t col_index) {
    if (_matrix_cols <= col_index) 
        throw MatrixException("ACCESS: bad index.");
    return _matrix_row[col_index];
}

int Matrix::const_row::operator[](std::size_t col_index) const {
    if (_matrix_cols <= col_index) 
        throw MatrixException("ACCESS: bad index.");
    return _matrix_row[col_index];
}

Matrix::Matrix(std::size_t rows, std::size_t cols) 
    : _rows(rows)
    , _cols(cols)
    , _data(new int*[rows]) {
    for (std::size_t row_ind = 0; row_ind < rows; row_ind++) {
        _data[row_ind] = new int[cols];
        for (std::size_t col_ind = 0; col_ind < cols; col_ind++) {
            _data[row_ind][col_ind] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& other) 
    : _rows(other._rows)
    , _cols(other._cols)
    , _data(new int*[other._rows]) {
    for (std::size_t row_ind = 0; row_ind < _rows; row_ind++) {
        _data[row_ind] = new int[_cols];
        for (std::size_t col_ind = 0; col_ind < _cols; col_ind++) {
            _data[row_ind][col_ind] = other._data[row_ind][col_ind];
        }
    }
}

Matrix::~Matrix() {
    for (std::size_t row_ind = 0; row_ind < _rows; row_ind++) {
        delete[] _data[row_ind];
    }
    delete[] _data;
}

std::size_t Matrix::rows() const { return _rows; }

std::size_t Matrix::cols() const { return _cols; }

Matrix::row Matrix::operator[](std::size_t row_index) {
    if (row_index >= _rows) 
        throw MatrixException("ACCESS: bad index.");
    return row(_data[row_index], _cols);
}

Matrix::const_row Matrix::operator[](std::size_t row_index) const {
    if (row_index >= _rows)
        throw MatrixException("ACCESS: bad index.");
    return const_row(_data[row_index], _cols);
}

Matrix& Matrix::operator=(Matrix other) {
    std::swap(_data, other._data);
    std::swap(_rows, other._rows);
    std::swap(_cols, other._cols);
    return *this;
}

Matrix& operator+=(Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) 
        throw MatrixException("ADD: dimensions do not match.");
    for (std::size_t row_ind = 0; row_ind < lhs.rows(); row_ind++) {
        for (std::size_t col_ind = 0; col_ind < lhs.cols(); col_ind++) {
            lhs[row_ind][col_ind] += rhs[row_ind][col_ind];
        }
    }
    return lhs;
}

Matrix& operator-=(Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
        throw MatrixException("ADD: dimensions do not match.");
    for (std::size_t row_ind = 0; row_ind < lhs.rows(); row_ind++) {
        for (std::size_t col_ind = 0; col_ind < lhs.cols(); col_ind++) {
            lhs[row_ind][col_ind] -= rhs[row_ind][col_ind];
        }
    }
    return lhs;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs){
    if (lhs.cols() != rhs.rows()) 
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix ans(lhs.rows(), rhs.cols());
    for (std::size_t row_ind = 0; row_ind < lhs.rows(); row_ind++) {
        for (std::size_t col_ind = 0; col_ind < rhs.cols(); col_ind++) {
            int res = 0;
            for (std::size_t i = 0; i < lhs.cols(); i++) {
                res += lhs[row_ind][i] * rhs[i][col_ind];
            }
            ans[row_ind][col_ind] = res;
        }
    }
    return ans;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mtx) {
    for (std::size_t row_ind = 0; row_ind < mtx.rows(); row_ind++) {
        for (std::size_t col_ind = 0; col_ind < mtx.cols(); col_ind++)
            os << mtx[row_ind][col_ind] << " ";
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& mtx) {
    for (std::size_t row_ind = 0; row_ind < mtx.rows(); row_ind++)
        for (std::size_t col_ind = 0; col_ind < mtx.cols(); col_ind++)
            is >> mtx[row_ind][col_ind];
    return is;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
        return false;
    for (std::size_t row_ind = 0; row_ind < lhs.rows(); row_ind++) {
        for (std::size_t col_ind = 0; col_ind < lhs.cols(); col_ind++) {
            if (lhs[row_ind][col_ind] != rhs[row_ind][col_ind]) 
                return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) {
    return !(lhs == rhs);
}

Matrix& operator*=(Matrix& lhs, const Matrix& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs);
    res += rhs;
    return res;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs);
    res -= rhs;
    return res;
}