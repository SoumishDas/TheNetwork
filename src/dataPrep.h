#ifndef DATAPREP_H
#define DATAPREP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<string>> readCSV(string fname);

int lenCsvVec(vector<vector<string>> csv);
void printCsvVec(vector<vector<string>> csv);
void splitCsvVec(vector<vector<string>> &vec1,vector<vector<string>> &vec2,int numColsToKeepInVec1);
vector<vector<double>> convertToDoubleVec(vector<vector<string>> csv);
#endif