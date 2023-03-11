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



#include "bits/stdc++.h"
using namespace std;
 
// Function to slice a given vector
// from range X to Y
vector<vector<double>> slicing(vector<vector<double>>& arr,
                    int X, int Y)
{
 
    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;
 
    // To store the sliced vector
    vector<vector<double>> result(Y - X + 1);
 
    // Copy vector using copy function()
    copy(start, end, result.begin());
 
    // Return the final sliced vector
    return result;
}