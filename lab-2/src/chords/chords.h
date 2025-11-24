// chords.h
#ifndef CHORDS_H
#define CHORDS_H

typedef struct {
	int iterations;
	double approximation;
	double residual;
} ChordsMethodResult;

double approximateRootChords(double x, double c);
int hasConvergedChords(double currentApproximation, double epsilon);
ChordsMethodResult performChordsMethod(double initialGuess, double fixedPoint, double epsilon);

#endif
