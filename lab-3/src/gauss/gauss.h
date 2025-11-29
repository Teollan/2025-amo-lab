// gauss.h
#ifndef GAUSS_H
#define GAUSS_H

#include "../matrix/matrix.h"
#include "../vector/vector.h"

Vector solveWithGaussianElimination(Matrix augmentedMatrix);

void performForwardElimination(Matrix augmentedMatrix);

Vector performBackwardSubstitution(Matrix upperTriangularMatrix);

#endif
