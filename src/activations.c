#include "activations.h>"

double basicActivationFunc(double weightedInput){
    if (weightedInput>0){
        return 1;
    } else {
        return 0;
    }
}