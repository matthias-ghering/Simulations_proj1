//
// Created by woute on 01/06/2017.
//

#include "ImplicitEulerSolver.h"

ImplicitEulerSolver::ImplicitEulerSolver():Solver(){}

void ImplicitEulerSolver::simulation_step(std::vector<Particle *> pVector, std::vector<Force *> fVector,
                                          std::vector<Constraint *> cVector, float dt) {}

void ImplicitEulerSolver::simulation_step(ParticleSystem *p, float dt) {
    std::vector<float> tmp1(this->getDim(p)), tmp2(this->getDim(p)), tmp3(this->getDim(p));

    this->getState(p, tmp1);
    this->derivEval(p, tmp2);

    SparseMatrix* I = new SparseMatrix(this->getDim(p)/2, this->getDim(p)/2);
    SparseMatrix* fPrime = new SparseMatrix(this->getDim(p)/2, this->getDim(p)/2);
    double f[this->getDim(p)/2];

    for (int i = 0; i < this->getDim(p) / 4; i++) {
        I->setValue(2 * i + 0, 2 * i + 0, 1 / dt);
        I->setValue(2 * i + 1, 2 * i + 1, 1 / dt);

        f[2 * i + 0] = tmp2[4 * i + 0];
        f[2 * i + 1] = tmp2[4 * i + 1];

        fPrime->setValue(2 * i + 0, 2 * i + 0, tmp2[4 * i + 2]);
        fPrime->setValue(2 * i + 1, 2 * i + 1, tmp2[4 * i + 3]);
    }

    SparseMatrix lhs = *I - *fPrime;

    int steps = 100;
    double deltaY[this->getDim(p)/2];
    ConjGrad(this->getDim(p)/2, &lhs, deltaY, f, 1e-30f, &steps);

    for (int i = 0; i < this->getDim(p) / 4; i++) {
        tmp3[4 * i + 0] = (float) deltaY[2 * i + 0];
        tmp3[4 * i + 1] = (float) deltaY[2 * i + 1];
        tmp3[4 * i + 2] = (float) tmp2[4 * i + 0];
        tmp3[4 * i + 3] = (float) tmp2[4 * i + 1];
    }

    this->addVectors(tmp1, tmp3, tmp1);
    this->setState(p, tmp1);
}
