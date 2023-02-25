#ifndef NETWORK_H
#define NETWORK_H

//Header Files
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
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
};

class Neural_Net{

    public:

        //Variables
        vector<Layer> layout;
        int inputSize;
        int numHiddenLayers;
        int outputSize;

        Neural_Net(vector<int> a);

        vector<double> computeOutputsofNN(vector<double> inputs);
};



#endif