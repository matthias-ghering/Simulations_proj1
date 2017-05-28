//
// Created by woute on 27/05/2017.
//

#include "SparseMatrix.h"

/*
 * TODO create an actual sparse matrix implementation
 */

SparseMatrix::SparseMatrix() {
    this->data = std::vector<std::vector<float>> (0, std::vector<float> (0));
}

SparseMatrix::SparseMatrix(size_t rows, size_t columns) {
    this->data = std::vector<std::vector<float>> (rows, std::vector<float> (columns));
}

int SparseMatrix::getRowCount() {
    return this->data.size();
}

int SparseMatrix::getColCount() {
    return this->data[0].size();
}

float SparseMatrix::getValue(int row, int column) {
    return this->data[row][column];
}

void SparseMatrix::setValue(int row, int column, float data) {
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

SparseMatrix operator* (SparseMatrix m, float f) {
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
            v.size() * 2, 1
    );

    for (int i = 0; i < m.getRowCount(); i++) {
        float x = 0, y = 0;
        int j;
        for (j = 0; j < v.size(); j++) {
            x += m.getValue(i, 2 * j + 0) * v[j][0];
            y += m.getValue(i, 2 * j + 1) * v[j][1];
        }

        result->setValue(2 * j + 0, 0, x);
        result->setValue(2 * j + 1, 0, y);
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