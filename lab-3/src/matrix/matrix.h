// matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include "../vector/vector.h"

typedef struct {
  int rows;
  int cols;
  double *data;
} Matrix;

Matrix createMatrix(int rows, int cols, double *data);
Matrix cloneMatrix(Matrix matrix);
void destroyMatrix(Matrix matrix);

double getMatrixElement(Matrix matrix, int i, int j);
void setMatrixElement(Matrix matrix, int i, int j, double value);

Vector getMatrixColumn(Matrix matrix, int j);
Matrix getMatrixSubmatrix(Matrix matrix, int i_start, int j_start, int rows, int cols);

void performRowScaling(Matrix matrix, int i, double scalar);
void performRowTransformation(Matrix matrix, int i, int k, double scalar);

char *matrixToString(Matrix matrix);

#endif
