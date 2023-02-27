
#include <cstdlib>

double getRandDoub(double from,double to){
    if (from>=0){
        return from+(to-from)*((double)rand())/RAND_MAX;
    } else{
        return from+(to-from)*((double)rand())/RAND_MAX;
    }
}