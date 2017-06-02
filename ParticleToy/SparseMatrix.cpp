#include "SparseMatrix.h"

/*
 * TODO create an actual sparse matrix implementation
 */

SparseMatrix::SparseMatrix() {
    this->data = std::vector<std::vector<double>> (0);
}

SparseMatrix::SparseMatrix(size_t rows, size_t columns) {
    for (int i = 0; i < rows; i++) {
        std::vector<double> col;
        for (int j = 0; j < columns; j++) {
            col.push_back(0);
        }
        this->data.push_back(col);
    }
    //this->data = std::vector<std::vector<double>> (rows, std::vector<double> (columns, 0));
}

int SparseMatrix::getRowCount() {
    return this->data.size();
}

int SparseMatrix::getColCount() {
    return this->data.size() > 0 ? this->data[0].size() : 0;
}

double SparseMatrix::getValue(int row, int column) {
    return this->data[row][column];
}

void SparseMatrix::setValue(int row, int column, double data) {
    this->data[row][column] = data;
}

void SparseMatrix::matVecMult(double x[], double r[]) {
    for (int i = 0; i < this->data.size(); i++) {
        r[i] = 0;
        for (int j = 0; j < this->data[i].size(); j++) {
            r[i] += this->data[i][j] * x[j];
        }
    }
}

SparseMatrix operator- (SparseMatrix left, SparseMatrix right) {
    if (left.getColCount() != right.getColCount() || left.getRowCount() != right.getRowCount()) {
        return SparseMatrix();
    }

    SparseMatrix* result = new SparseMatrix(
            (size_t) left.getRowCount(), (size_t) left.getColCount()
    );

    for (int i = 0; i < left.getRowCount(); i++) {
        for (int j = 0; j < left.getColCount(); j++) {
            result->setValue(i, j, left.getValue(i, j) - right.getValue(i, j));
        }
    }

    return *result;
}

SparseMatrix operator* (SparseMatrix m, double f) {
    SparseMatrix* result = new SparseMatrix(
            (size_t) m.getRowCount(), (size_t) m.getColCount()
    );

    for (int i = 0; i < m.getRowCount(); i++) {
        for (int j = 0; j < m.getColCount(); j++) {
            result->setValue(i, j, m.getValue(i, j) * f);
        }
    }

    return *result;
}

SparseMatrix operator* (SparseMatrix m, std::vector<Vec2f> v) {
    if (m.getColCount() != v.size() * 2) {
        return SparseMatrix();
    }

    SparseMatrix* result = new SparseMatrix(
            (size_t) m.getRowCount(), 1
    );

    for (int i = 0; i < m.getRowCount(); i++) {
        double x = 0;
        for (int j = 0; j < v.size(); j++) {
            x += m.getValue(i, 2 * j + 0) * v[j][0];
            x += m.getValue(i, 2 * j + 1) * v[j][1];
        }

        result->setValue(i, 0, x);
    }

    return *result;
}

SparseMatrix operator*(SparseMatrix left, SparseMatrix right) {
    if (left.getColCount() != right.getRowCount()) {
        return SparseMatrix();
    }

    SparseMatrix* result = new SparseMatrix(
            (size_t) left.getRowCount(),
            (size_t) right.getColCount()
    );

    for (int i = 0; i < left.getRowCount(); i++)
    {
        for (int j = 0; j < right.getColCount(); j++)
        {
            for (int k = 0; k < right.getRowCount(); k++)
            {
                result->setValue(
                        i, j, result->getValue(i, j) + left.getValue(i, k) * right.getValue(k, j)
                );
            }
        }
    }

    return *result;
}