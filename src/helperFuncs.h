#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include <random>
#include <cstdlib>
#include <string>
#include "bits/stdc++.h"
using namespace std;


double getRandDoub(double from,double to);

int getRandInt(int from,int to);

string isTrue(double a, double b);



 
// Function to slice a given vector
// from range X to Y
vector<vector<double>> slicing(vector<vector<double>>& arr,int X, int Y);


#endif