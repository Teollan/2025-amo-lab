// vector.h
#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  int length;
  double *data;
} Vector;

Vector createVector(int length, double *data);
Vector cloneVector(Vector vector);
void destroyVector(Vector vector);

double getVectorElement(Vector vector, int index);
void setVectorElement(Vector vector, int index, double value);

char *vectorToString(Vector vector);

#endif
