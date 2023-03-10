#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include <math.h>

double basicActFunc(double weightedInput);

double SigmoidActFunc(double weightedInput);
double SigmoidActDerv(double weightedInput);

double TanHActFunc(double weightedInput);
double TanHActDerv(double weightedInput);
#endif