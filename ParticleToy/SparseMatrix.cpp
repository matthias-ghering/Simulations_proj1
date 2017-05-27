//
// Created by woute on 27/05/2017.
//

#include "SparseMatrix.h"

/*
 * TODO create an actual sparse matrix implementation
 */

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