// gauss-seidel.h
#ifndef GAUSS_H
#define GAUSS_H

#include "../matrix/matrix.h"
#include "../vector/vector.h"

typedef struct {
  Matrix L;
  Matrix U;
} GaussSeidelSplitResult;

Vector solveWithGaussSeidelMethod(Matrix A, Matrix B);

GaussSeidelSplitResult performGaussSeidelSplit(Matrix matrix);

#endif
