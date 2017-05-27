//
// Created by woute on 27/05/2017.
//

#ifndef SIMULATION_1_SPARSEMATRIX_H
#define SIMULATION_1_SPARSEMATRIX_H


#include <vector>
#include "linearSolver.h"

/*
 * TODO create an actual sparse matrix implementation
 */
class SparseMatrix : implicitMatrix{
public:
    SparseMatrix(size_t rows, size_t columns);

    float getValue(int row, int column);
    void setValue(int row, int column, float data);
    int getRowCount();
    int getColCount();

    void matVecMult(double x[], double r[]);
private:

    std::vector<std::vector<float>> data;
};


#endif //SIMULATION_1_SPARSEMATRIX_H
