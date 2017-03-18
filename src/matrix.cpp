#include "matrix.h"

MatrixException::MatrixException(std::string what_happend) : _error(what_happend){}

std::string MatrixException::what() const{
    return _error;
}

Matrix::Matrix() : _rows(0), _cols(0), _data(NULL){}

Matrix::row::row(int* matrix_row, std::size_t matrix_cols) : _matrix_row(matrix_row), _matrix_cols(matrix_cols) {}

Matrix::const_row::const_row(const int* matrix_row, std::size_t matrix_cols) : _matrix_row(matrix_row), _matrix_cols(matrix_cols) {}

int& Matrix::row::operator[](std::size_t col_index) {
    if (_matrix_cols <= col_index) throw MatrixException("ACCESS: bad index.");
    return _matrix_row[col_index];
}

int Matrix::const_row::operator[](std::size_t col_index) const {
    if (_matrix_cols <= col_index) throw MatrixException("ACCESS: bad index.");
    return _matrix_row[col_index];
}

Matrix::Matrix(std::size_t r, std::size_t c) : _rows(r), _cols(c), _data(new int*[r]) {
    for (std::size_t i = 0; i < r; i++) {
        _data[i] = new int[c];
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols), _data(new int*[m._rows]) {
    for (std::size_t i = 0; i < _rows; i++) {
        _data[i] = new int[_cols];
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] = m._data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (std::size_t i = 0; i < _rows; i++) {
        delete(_data[i]);
    }
    delete(_data);
}

std::size_t Matrix::get_rows() const { return _rows; }

std::size_t Matrix::get_cols() const { return _cols; }

Matrix::row Matrix::operator[](std::size_t row_index) {
    if (row_index >= _rows) throw MatrixException("ACCESS: bad index.");
    return row(_data[row_index], _cols);
}

Matrix::const_row Matrix::operator[](std::size_t row_index) const{
    return const_row(_data[row_index], _cols);
}

bool Matrix::operator==(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols) return false;
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            if (_data[i][j] != m._data[i][j]) return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}

Matrix& Matrix::operator=(Matrix m) {
    std::swap(_data, m._data);
    std::swap(_rows, m._rows);
    std::swap(_cols, m._cols);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    if (_rows != m._rows || _cols != m._cols) throw MatrixException("ADD: dimensions do not match.");
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] += m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    if (_rows != m._rows || _cols != m._cols) throw MatrixException("ADD: dimensions do not match.");
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++) {
            _data[i][j] -= m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    *this = *this * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    Matrix res(m);
    res += (*this);
    return res;
}

Matrix Matrix::operator-(const Matrix& m) const {
    Matrix res(m);
    res -= (*this);
    return res;
}

Matrix Matrix::operator*(const Matrix& m) const {
    if (_cols != m._rows) throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix ans(_rows, m._cols);
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < m._cols; j++) {
            int res = 0;
            for (std::size_t k = 0; k < _cols; k++) {
                res += _data[i][k] * m._data[k][j];
            }
            ans._data[i][j] = res;
        }
    }
    return ans;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (std::size_t i = 0; i < m.get_rows(); i++) {
        for (std::size_t j = 0; j < m.get_cols(); j++)
            os << m[i][j] << " ";
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
    for (std::size_t i = 0; i < m.get_rows(); i++)
        for (std::size_t j = 0; j < m.get_cols(); j++)
            is >> m[i][j];
    return is;
}
