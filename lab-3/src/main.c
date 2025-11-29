// main.c
#include <stdio.h>
#include <stdlib.h>

#include "gauss-seidel/gauss-seidel.h"
#include "gauss/gauss.h"
#include "matrix/matrix.h"
#include "vector/vector.h"

void testGaussElimination() {
  // clang-format off
  double a_b[] = {
    14, 19, 15,  4, 180,
    17, 33,  5, 10, 208,
    11,  6, 28, 10, 230,
     6, 19,  3, 13, 149,
  };
  // clang-format on

  printf("Testing Gaussian Elimination:\n");

  Matrix A_B = createMatrix(4, 5, a_b);
  char *A_B_str = matrixToString(A_B);
  printf("Original Matrix A augmented with B:\n%s\n", A_B_str);
  free(A_B_str);

  Vector X = solveWithGaussianElimination(A_B);
  char *X_str = vectorToString(X);
  printf("Solution with Gaussian Elimination:\n%s\n", X_str);
  free(X_str);

  destroyMatrix(A_B);
  destroyVector(X);
}

void testGaussSeidel() {
  // clang-format off
  double a_b[] = {
    14, 19, 15,  4, 180, // 14 < 19 + 15 + 4 = 38 (not diagonally dominant)
    17, 33,  5, 10, 208, // 33 > 17 + 5 + 10 = 32
    11,  6, 28, 10, 230, // 28 > 11 + 6 + 10 = 27
     6, 19,  3, 13, 149, // 13 < 6 + 19 + 3 = 28 (not diagonally dominant)
  };
  // clang-format on

  printf("Testing Gauss-Seidel Method:\n");

  Matrix A_B = createMatrix(4, 5, a_b);

  char *A_B_str = matrixToString(A_B);
  printf("Original Matrix A augmented with B:\n%s\n", A_B_str);
  free(A_B_str);

  // Make row (4) diagonally dominant
  // (4) = (4) - 3*(1) + (2) + 2*(3)
  performRowTransformation(A_B, 3, 0, -3.0);
  performRowTransformation(A_B, 3, 1, 1.0);
  performRowTransformation(A_B, 3, 2, 2.0);

  // Make row (1) diagonally dominant
  // (1) = 100*(1) - 55*(2) - 60*(3) - 24*(4)
  performRowScaling(A_B, 0, 100);
  performRowTransformation(A_B, 0, 1, -55.0);
  performRowTransformation(A_B, 0, 2, -60.0);
  performRowTransformation(A_B, 0, 3, 24.0);

  char *A_B_diagonal_str = matrixToString(A_B);
  printf("Diagonally dominant Matrix A augmented with B:\n%s\n", A_B_diagonal_str);
  free(A_B_diagonal_str);

  Matrix A = getMatrixSubmatrix(A_B, 0, 0, 4, 4);
  Vector B = getMatrixColumn(A_B, 4);
  printf("Is matrix A diagonally dominant? %s\n\n", isMatrixDiagonallyDominant(A) ? "Yes" : "No");

  Vector X = solveWithGaussSeidel(A, B, 0.00001);  // 10^-5
  char *X_str = vectorToString(X);
  printf("Solution with Gauss-Seidel:\n%s\n", X_str);
  free(X_str);

  destroyMatrix(A_B);
  destroyMatrix(A);
  destroyVector(B);
  destroyVector(X);
}

int main() {
  printf("\n\n");

  testGaussElimination();

  printf("\n-----------------------\n\n");

  testGaussSeidel();

  printf("\n\n");

  return 0;
}