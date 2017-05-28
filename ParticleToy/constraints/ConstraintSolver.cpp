
#include "ConstraintSolver.h"

// Extract all required information from particles and constraints
void ConstraintSolver::init(std::vector<Particle *> particles, std::vector<Constraint *> constraints) {
    for (int i = 0; i < particles.size(); i++) {

        // Set particle index
        particles[i]->setIndex(i);

        // Set position vector
        this->q.push_back(particles[i]->m_Position);

        // Set velocity vector
        this->qdot.push_back(particles[i]->m_Velocity);

        // Set inverse weight vector
        float wweight = 1 / particles[i]->m_Mass;
        this->W.push_back(wweight);
        this->W.push_back(wweight);

        // Set force vector
        this->Q.push_back(particles[i]->m_Force);

        // Calculate pre-constraint velocity qdotdot
        this->qddot.push_back(
                Vec2f(this->W[i + 0] * this->Q[i][0], this->W[i + 1] * this->Q[i][1])
        );
    }

    this->J = new SparseMatrix(constraints.size(), particles.size() * 2);
    this->JT = new SparseMatrix(particles.size() * 2, constraints.size());
    this->Jdot = new SparseMatrix(constraints.size(), particles.size() * 2);
    this->C = new SparseMatrix(constraints.size(), 1);
    this->Cdot = new SparseMatrix(constraints.size(), 1);

    for (int i = 0; i < constraints.size(); i++) {
        // Set constraint vectors
        this->C->setValue(i, 0, constraints[i]->getC());
        this->Cdot->setValue(i, 0, constraints[i]->getCdot());

        // Set Jacobians
        for (int j = 0; j < constraints[i]->particles.size(); j++) {
            int pIndex = constraints[i]->particles[j]->index;
            // Set value at J[particle.x][constraint] and JT[particle.y][constraint]
            this->J->setValue(i, pIndex * 2 + 0, constraints[i]->getJ()[j][0]);
            this->J->setValue(i, pIndex * 2 + 1, constraints[i]->getJ()[j][1]);
            // Set value at JT[constraint][particle.x] and J[constraint][particle.y]
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

    //free(this->C);
    //free(this->Cdot);
    //free(this->J);
    //free(this->JT);
    //free(this->Jdot);
}

void ConstraintSolver::applyConstraints(std::vector<Particle *> particles, std::vector<Constraint *> constraints) {
    this->init(particles, constraints);

    // Apply constraints
    SparseMatrix* JW = new SparseMatrix(constraints.size(), particles.size() * 2);

    int wIndex = 0;
    for (int i = 0; i < this->J->getRowCount(); i++) {
        for (int j = 0; j < this->J->getColCount(); j++) {
            JW->setValue(i, j, this->J->getValue(i, j) * this->W[wIndex++]);
        }
        wIndex = 0;
    }

    SparseMatrix Jdotqdot = ((*this->Jdot) * this->qdot) * -1;
    SparseMatrix rhs = Jdotqdot - ((*JW) * this->Q) - (*this->C * this->ks) - (*this->Cdot * this->kd);

    SparseMatrix JWJT = (*JW) * (*this->JT);

    int steps = 100;
    double lambdaTarray[constraints.size()];
    double rhsArray[constraints.size()];
    for (int i = 0; i < constraints.size(); i++) {
        rhsArray[i] = rhs.getValue(i, 0);
    }

    ConjGrad(constraints.size(), &JWJT, lambdaTarray, rhsArray, 1e-30f, &steps);

    SparseMatrix* lambdaT = new SparseMatrix(constraints.size(), 1);
    for (int i = 0; i < constraints.size(); i++) {
        lambdaT->setValue(i, 0, lambdaTarray[i]);
    }

    SparseMatrix QhatT = (*this->JT) * (*lambdaT);

    for (int i = 0; i < particles.size(); i++) {
        particles[i]->m_Force[0] += QhatT.getValue(2 * i + 0, 0);
        particles[i]->m_Force[1] += QhatT.getValue(2 * i + 1, 0);
    }

    free(JW);
    free(lambdaT);
    free(lambdaTarray);

    this->reset();
}

