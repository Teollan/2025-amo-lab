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
  char* A_B_str = matrixToString(A_B);

  printf("Original Matrix A augmented with B:\n%s\n", A_B_str);

  Vector X = solveWithGaussianElimination(A_B);
  char* X_str = vectorToString(X);

  printf("Solution with Gaussian Elimination:\n%s\n", X_str);

  destroyMatrix(A_B);
  free(A_B_str);

  destroyVector(X);
  free(X_str);
}

void testGaussSeidel() {
  // clang-format off
  double a[] = {
    14, 19, 15,  4,
    17, 33,  5, 10,
    11,  6, 28, 10,
     6, 19,  3, 13,
  };

  double b[] = {
    180,
    208,
    230,
    149,
  };
  // clang-format on

  printf("Testing Gauss-Seidel Method:\n");

  Matrix A = createMatrix(4, 4, a);
  char* A_str = matrixToString(A);

  printf("Matrix A:\n%s\n", A_str);

  Vector B = createVector(4, b);
  char* B_str = vectorToString(B);

  printf("Vector B:\n%s\n", B_str);

  Vector X = solveWithGaussSeidel(A, B, 0.0001);
  char* X_str = vectorToString(X);

  printf("Solution with Gauss-Seidel:\n%s\n", X_str);

  destroyMatrix(A);
  free(A_str);

  destroyVector(B);
  free(B_str);

  destroyVector(X);
  free(X_str);
}

int main() {
  testGaussElimination();

  testGaussSeidel();

  return 0;
}