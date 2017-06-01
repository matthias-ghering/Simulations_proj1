
#include "ConstraintSolver.h"

ConstraintSolver::ConstraintSolver() {}

void ConstraintSolver::init(std::vector<Particle *> particles, std::vector<Constraint *> constraints) {
    // We use n to denote particles.size(), and c for constraints.size()
    for (int i = 0; i < particles.size(); i++) {

        // Set particle index
        particles[i]->setIndex(i);

        // Set position vector (length n, each element with 2 components)
        this->q.push_back(particles[i]->m_Position);

        // Set velocity vector (length n, each element with 2 components)
        this->qdot.push_back(particles[i]->m_Velocity);

        // Set inverse weight vector (length 2n)
        // Since we know only the diagonal of W has values, we represent it using a vector
        float iweight = 1 / particles[i]->m_Mass;
        this->W.push_back(iweight);
        this->W.push_back(iweight);

        // Set force vector (length n, each element with 2 components)
        this->Q.push_back(particles[i]->m_Force);

        // Calculate pre-constraint velocity qdotdot (length n, each element with 2 components)
        this->qddot.push_back(
                Vec2f(this->W[i + 0] * this->Q[i][0], this->W[i + 1] * this->Q[i][1])
        );
    }

    // Initialize matrices with correct sizes and all zeros
    this->J = new SparseMatrix(constraints.size(), particles.size() * 2);
    this->JT = new SparseMatrix(particles.size() * 2, constraints.size());
    this->Jdot = new SparseMatrix(constraints.size(), particles.size() * 2);
    this->C = new SparseMatrix(constraints.size(), 1);
    this->Cdot = new SparseMatrix(constraints.size(), 1);

    for (int i = 0; i < constraints.size(); i++) {
        // Set constraint vectors
        this->C->setValue(i, 0, constraints[i]->getC());
        this->Cdot->setValue(i, 0, constraints[i]->getCdot());

        // Set Jacobian matrices
        for (int j = 0; j < constraints[i]->particles.size(); j++) {
            int pIndex = constraints[i]->particles[j]->index;

            // Set value at J[constraint][particle.x] and J[constraint][particle.y]
            this->J->setValue(i, pIndex * 2 + 0, constraints[i]->getJ()[j][0]);
            this->J->setValue(i, pIndex * 2 + 1, constraints[i]->getJ()[j][1]);

            // Set value at JT[particle.x][constraint] and JT[particle.y][constraint]
            this->JT->setValue(pIndex * 2 + 0, i, constraints[i]->getJ()[j][0]);
            this->JT->setValue(pIndex * 2 + 1, i, constraints[i]->getJ()[j][1]);

            // Set value at Jdot[constraint][particle.x] and Jdot[constraint][particle.y]
            this->Jdot->setValue(i, pIndex * 2 + 0, constraints[i]->getJdot()[j][0]);
            this->Jdot->setValue(i, pIndex * 2 + 1, constraints[i]->getJdot()[j][1]);
        }
    }

}

void ConstraintSolver::reset() {
    this->q.clear();
    this->W.clear();
    this->qddot.clear();
    this->qdot.clear();
    this->Q.clear();

    delete(this->C);
    delete(this->Cdot);
    delete(this->J);
    delete(this->JT);
    delete(this->Jdot);
}

void ConstraintSolver::applyConstraints(std::vector<Particle *> particles, std::vector<Constraint *> constraints, float ks, float kd) {
    if (constraints.size() == 0) {
        // Skip constraint calculation
        return;
    }

    this->init(particles, constraints);

    SparseMatrix* JW = new SparseMatrix(constraints.size(), particles.size() * 2);

    int wIndex = 0;
    /** JW (c rows, 2n cols) = J (c,2n) * W (2n,2n)                                        */
    // Because W only has values in its diagonal, the matrix multiplication can be done more
    // efficient than normal because in every column of W there is only 1 non-zero value
    for (int i = 0; i < this->J->getRowCount(); i++) {
        for (int j = 0; j < this->J->getColCount(); j++) {
            JW->setValue(i, j, this->J->getValue(i, j) * this->W[wIndex++]);
        }
        wIndex = 0;
    }

    /**           (c,1)         (c,2n)         (2n,1)                                       */
    SparseMatrix Jdotqdot = ((*this->Jdot) * this->qdot) * -1;
    /**         (c,1)   (c,1)     (c,2n)   (2n,1)          (c,1)              (c,1)         */
    SparseMatrix rhs = Jdotqdot - ((*JW) * this->Q) - (*this->C * ks) - (*this->Cdot * kd);

    /**          (c,c)  (c,2n)     (2n,c)                                                   */
    SparseMatrix JWJT = (*JW) * (*this->JT);

    int steps = 100;
    double lambdaTarray[constraints.size()];
    double rhsArray[constraints.size()];
    for (int i = 0; i < constraints.size(); i++) {
        rhsArray[i] = rhs.getValue(i, 0);
    }

    /**                          (c,c)      (c)          c                                  */
    ConjGrad(constraints.size(), &JWJT, lambdaTarray, rhsArray, 1e-30f, &steps);

    SparseMatrix* lambdaT = new SparseMatrix(constraints.size(), 1);
    for (int i = 0; i < constraints.size(); i++) {
        lambdaT->setValue(i, 0, lambdaTarray[i]);
    }

    /**          (1,2n)    (2n,c)        (c,1)                                              */
    SparseMatrix QhatT = (*this->JT) * (*lambdaT);
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->m_Force[0] += QhatT.getValue(2 * i + 0, 0);
        particles[i]->m_Force[1] += QhatT.getValue(2 * i + 1, 0);
    }

    delete(JW);
    delete(lambdaT);

    this->reset();
}

