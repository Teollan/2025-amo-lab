// gauss.h
#ifndef GAUSS_H
#define GAUSS_H

#include "../matrix/matrix.h"
#include "../vector/vector.h"

Vector solveWithGaussianElimination(Matrix augmentedMatrix);

Matrix performForwardSubstitution(Matrix augmentedMatrix);

Vector performBackSubstitution(Matrix upperTriangularMatrix);

#endif
