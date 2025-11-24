// vector.c
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>

Vector createVector(int length, double* data) {
  Vector vector;
  vector.length = length;
  vector.data = (double*) malloc(length * sizeof(double));

  if (data == NULL) {
    return vector;
  }

  for (int i = 0; i < length; i++) {
    vector.data[i] = data[i];
  }

  return vector;
}

Vector cloneVector(Vector vector) {
  Vector newVector = createVector(vector.length, NULL);

  for (int i = 0; i < vector.length; i++) {
    newVector.data[i] = vector.data[i];
  }

  return newVector;
}

void destroyVector(Vector vector) {
  free(vector.data);
}

double getVectorElement(Vector vector, int index) {
  return vector.data[index];
}

void setVectorElement(Vector vector, int index, double value) {
  vector.data[index] = value;
}

Vector multiplyVectorByScalar(Vector vector, double scalar) {
  Vector clone = cloneVector(vector);

  for (int i = 0; i < clone.length; i++) {
    clone.data[i] *= scalar;
  }

  return clone;
}

Vector addVectors(Vector a, Vector b) {
  Vector result = createVector(a.length, NULL);

  for (int i = 0; i < a.length; i++) {
    result.data[i] = a.data[i] + b.data[i];
  }

  return result;
}

char* vectorToString(Vector vector) {
  char* buffer = (char*) malloc(256 * sizeof(char));
  int offset = 0;

  offset += sprintf(buffer + offset, "[");

  for (int i = 0; i < vector.length; i++) {
    offset += sprintf(buffer + offset, "% 9.4f", vector.data[i]);

    if (i < vector.length - 1) {
      offset += sprintf(buffer + offset, ", ");
    }
  }

  offset += sprintf(buffer + offset, "]");

  return buffer;
}