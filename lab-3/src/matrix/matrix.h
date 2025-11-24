// matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
  int rows;
  int cols;
  Vector* data;
} Matrix;

Matrix createMatrix(int rows, int cols, double* data);
Matrix cloneMatrix(Matrix matrix);
void destroyMatrix(Matrix matrix);

double getMatrixElement(Matrix matrix, int rowIndex, int colIndex);
void setMatrixElement(Matrix matrix, int rowIndex, int colIndex, double value);

Vector getMatrixRow(Matrix matrix, int rowIndex);
void setMatrixRow(Matrix matrix, int rowIndex, Vector rowData);

Matrix getInverseMatrix(Matrix matrix); // Not implemented yet
Matrix multiplyMatrices(Matrix A, Matrix B);

char* matrixToString(Matrix matrix);

#endif
