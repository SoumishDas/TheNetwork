#ifndef NETWORK_H
#define NETWORK_H

//Header Files
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <array>

using namespace std;




//Classes
class Node{

    public:

        //Creating Vectors for weights and biases
        vector<double> weights;
        
        double biasN;

        //Constructor
        Node(int numNodeIn);
};


class Layer{
    public:

        //Vars
        int numNodesIn,numNodesOut;
        vector<Node> nodes;
        
        Layer(int NodesIn,int NodesOut);
        vector<double> calcOutput(vector<double> inputs);
        double (*activationFunc)(double weightedInput);
        double nodeCost(double outputActivation, double expectedOutput);
};

class Neural_Net{

    public:

        //Variables
        vector<Layer> layers;
        int inputSize;
        int numHiddenLayers;
        vector<int> layerSizes;
        int outputSize;

        Neural_Net(vector<int> a);

        vector<double> computeOutputsofNN(vector<double> inputs);
        void saveNNtoFile(string fileName);
        void loadNNfromFile(string fileName);
};



double Loss(vector<double> input,vector<double> expectedOutput,Neural_Net NN);
double TotalLoss(vector<vector<double>> inputs,vector<vector<double>> expectedOutputs,Neural_Net NN);

#endif