#ifndef NETWORK_H
#define NETWORK_H

//Header Files
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
using namespace std;

#include "networkData.h"

class dataPoint{
    public:

        vector<double> inputs;
        vector<double> expected_outputs;

        dataPoint(vector<double> inputs,vector<double> expected_outputs);
};



class Node{

    public:

        //Creating Vectors for weights and biases
        vector<double> weights;
        vector<double> costGradientW;
        vector<double> weightVelocities ;
		

        double biasN;
        double costGradientB;
        double biasVelocity;
        //Constructor
        Node(const int numNodeIn);
        
};

// Forward Declaration to resolve dependency; Actual declaration in networkData.h;
class layerLearnData;

class Layer{
    public:

        //Vars
        int numNodesIn,numNodesOut;
        vector<Node> nodes;
        
        Layer(const int NodesIn,const int NodesOut);

        vector<double> calcOutput(const vector<double> &inputs);
        vector<double> calcOutput(const vector<double> &inputs,layerLearnData& learnData );
        double (*activationFunc)(double weightedInput);

        void applyGradients(const double &learnRate);


        // BackPropagation using Calculus
        void CalculateOutputLayerNodeValues(layerLearnData &layerLearnData, vector<double> &expectedOutputs);
        void CalculateHiddenLayerNodeValues(layerLearnData &layerLearnData, Layer &oldLayer, vector<double> &oldNodeValues);
        void UpdateGradients(layerLearnData layerLearnData);
        void ApplyGradientsCalc(double learnRate, double regularization, double momentum);
};

// Forward Declaration to resolve dependency; Actual declaration in networkData.h;
class networkLearnData;

class Neural_Net{

    public:

        //Variables
        vector<Layer> layers;
        int inputSize;
        int numHiddenLayers;
        vector<int> layerSizes;
        int outputSize;


        Neural_Net(const vector<int>& a);

        vector<double> computeOutputsofNN(const vector<double>& inputs);
        void saveNNtoFile(const string& fileName);
        void loadNNfromFile(const string& fileName);

        // No Calculus Gradient Descent
        void applyAllGradients(const double& learnRate);
        void learnNoCalc(const vector<vector<double>>& inputs,const vector<vector<double>>& expected_out,const double& learnRate);


        // BackPropagation using Calculus
        void LearnCalc(vector<dataPoint> &trainingData, double learnRate, double regularization, double momentum);
        void UpdateGradientsCalc(dataPoint &data,networkLearnData &learnData);

        private:

        vector<networkLearnData> batchLearnData;

};

double Loss(const vector<double>& input,const vector<double>& expectedOutput,Neural_Net& NN);
double TotalLoss(const vector<vector<double>>& inputs,const vector<vector<double>>& expectedOutputs, Neural_Net& NN);

Neural_Net getBestNnRandom(const vector<int>& size,const vector<vector<double>>& x,const vector<vector<double>>& expected_y,int numTries);

void getBestNnGradientDescent(Neural_Net *NN,vector<vector<double>> x,vector<vector<double>> expected_y,int numTries,double learnRate);

double CostDerivative(double predictedOutput, double expectedOutput);

double nodeCost(const double outputActivation,const double expectedOutput);
#endif