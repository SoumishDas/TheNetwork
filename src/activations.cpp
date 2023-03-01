#include "activations.h"

double basicActFunc(double weightedInput){
    if (weightedInput>0){
        return 1;
    } else {
        return 0;
    }
}

double SigmoidActFunc(double weightedInput){
    return 1 / (1+exp(-weightedInput));
}

double TanHActFunc(double weightedInput){
    return tanh(weightedInput);
}