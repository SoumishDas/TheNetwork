#include <cstdlib>

double getRandDoub(double from,double to){
    if (from>=0){
        return from+(to-from)*((double)rand())/RAND_MAX;
    } else{
        return from+(to-from)*((double)rand())/RAND_MAX;
    }
}

string isTrue(double a, double b){
    if(a>b){
        return "True";
    }else if (a==b){
        return "True/False";
    }else {
        return "False";
    }
}