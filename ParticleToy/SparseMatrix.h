//
// Created by woute on 27/05/2017.
//

#ifndef SIMULATION_1_SPARSEMATRIX_H
#define SIMULATION_1_SPARSEMATRIX_H


#include <vector>
#include <gfx/vec2.h>
#include "linearSolver.h"

/*
 * TODO create an actual sparse matrix implementation
 */
class SparseMatrix : public implicitMatrix{
public:
    SparseMatrix();
    SparseMatrix(size_t rows, size_t columns);

    float getValue(int row, int column);
    void setValue(int row, int column, float data);
    int getRowCount();
    int getColCount();

    void matVecMult(double x[], double r[]);

    friend SparseMatrix operator- (SparseMatrix left, SparseMatrix right);
    friend SparseMatrix operator* (SparseMatrix m, float f);
    friend SparseMatrix operator* (SparseMatrix m, std::vector<Vec2f> v);
    friend SparseMatrix operator* (SparseMatrix left, SparseMatrix right);
private:

    std::vector<std::vector<float>> data;
};


#endif //SIMULATION_1_SPARSEMATRIX_H
