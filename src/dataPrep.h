#ifndef DATAPREP_H
#define DATAPREP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<vector<string>> readCSV(const string& fname);

vector<double> convertStrVecToDoubVec(const vector<string>& stringVector);

int lenCsvVec(const vector<vector<string>>& csv);
void printCsvVecStr(const vector<vector<string>>& csv);
void printCsvVecDoub(const vector<vector<double>>& csv);
void splitCsvVec(vector<vector<string>> &vec1,vector<vector<string>> &vec2,int numColsToKeepInVec1);

vector<vector<double>> convertTo2dDoubleVec(const vector<vector<string>>& csv);

vector<vector<double>> calcExpectedOutputs(const vector<vector<string>>& inp);

#endif