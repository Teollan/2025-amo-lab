// iteration.h
#ifndef ITERATION_H
#define ITERATION_H

typedef struct {
	int iterations;
	double approximation;
	double residual;
} IterationMethodResult;

double approximateRootIterations(double x);
int hasConvergedIterations(double previousApproximation, double currentApproximation, double epsilon);
IterationMethodResult performIterationMethod(double initialGuess, double epsilon);

#endif
