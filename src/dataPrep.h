#ifndef DATAPREP_H
#define DATAPREP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<vector<string>> readCSV(string fname);

vector<double> convertStrVecToDoubVec(const vector<string>& stringVector);

int lenCsvVec(vector<vector<string>> csv);
void printCsvVecStr(vector<vector<string>> csv);
void printCsvVecDoub(vector<vector<double>> csv);
void splitCsvVec(vector<vector<string>> &vec1,vector<vector<string>> &vec2,int numColsToKeepInVec1);
vector<vector<double>> convertTo2dDoubleVec(vector<vector<string>> csv);

vector<vector<double>> calcExpectedOutputs(vector<vector<string>> inp);

#endif