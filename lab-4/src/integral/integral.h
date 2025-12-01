// integral.h
#ifndef INTEGRAL_H
#define INTEGRAL_H

typedef struct {
  double I;
  double h;
} IntegralResult;

double calculateIntegralNewtonLeibniz(double a, double b, double (*F)(double x));

int calculateTrapezoidalStepsForPrecision(double a, double b, double eps, double (*f_dd)(double x));

IntegralResult calculateIntegralTrapezoidal(double a, double b, int n, double (*f)(double x));

IntegralResult calculateIntegralTrapezoidalRunge(double a, double b, double eps, double (*f)(double x));

#endif