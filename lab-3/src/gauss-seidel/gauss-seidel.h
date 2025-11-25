// gauss-seidel.h
#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include "../matrix/matrix.h"
#include "../vector/vector.h"

typedef struct {
  Matrix L;
  Matrix U;
} GaussSeidelSplitResult;

Vector solveWithGaussSeidel(Matrix A, Vector B, double eps);

int hasGaussSeidelConverged(Vector X, Vector X_old, double eps);

#endif
