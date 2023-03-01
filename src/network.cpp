//Header Files
#include "network.h"
#include "activations.h"
#include "helperFuncs.h"
#include "dataPrep.h"

using namespace std;



Node::Node(int numNodeIn){

    //The Loop enters all the inputs and weights from the array into their respective vectors
    for (int i = 0; i < numNodeIn; i++)
    {
        double z = getRandDoub(-1,1);
        //cout << z<<"##"<<endl;
        weights.push_back(z);
        
        
    }
    
    //The bias value of a particular Node
    biasN = getRandDoub(-1,1);
    //cout << biasN<<"#"<<endl;
}






Layer::Layer(int NodesIn,int NodesOut){
    this->numNodesIn = NodesIn;
    this->numNodesOut = NodesOut;
    this->activationFunc = TanHActFunc;
    //Creates and adds Nodes as per requirement
    for (int i = 0; i < numNodesOut; i++)
    {

        //Creates a object of class Node
        Node N(numNodesIn);

        //Adds the object in the vector
        nodes.push_back(N);


    }
    
}


vector<double> Layer::calcOutput(vector<double> inputs){

    
    //Dynamic array for storing weighted inputs after computation
    vector<double> weightedInputs ;

    //For loop to iterate over the Outnodes and compute weighted inputs
    for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
    {
        // Adding Bias to the weighted input
        double weightedInput = nodes[nodeOut].biasN;

        // Adding all the inputs multiplied with weights 
        for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
        {
            weightedInput += inputs[nodeIn] * nodes[nodeOut].weights[nodeIn];
        }
        weightedInputs.push_back(activationFunc(weightedInput));


    }
    return weightedInputs;
}



Neural_Net::Neural_Net(vector<int> a){

    int S = a.size();

    this->inputSize = a[0];
    this->outputSize = a[S-1];
    this->numHiddenLayers = S-2;

    for (int i = 0; i < S-1; i++)
    {
        
        //Creates a object of class Layer
        Layer L(a[i],a[i+1]);
        cout<< L.numNodesIn<<"  --  "<<L.numNodesOut<<endl;
        //Adds the object in the vector
        this->layers.push_back(L);


    }



    //Testing
    // cout<<arraySize<<" ";
    // cout<<outputSize<<" ";
    // cout<<inputSize;

}

vector<double> Neural_Net::computeOutputsofNN(vector<double> inputs){

    vector<double>tempOut = inputs;

    for (int layer=0;layer<this->layers.size();layer++){
        tempOut = layers[layer].calcOutput(tempOut);
    }

    return tempOut;
}

//Main Function
int main() {
  
    // Setting random seed as current time
    srand (static_cast <unsigned> (time(0)));

    
    // double inp[3] = {2.5,2.5,1.5};
    // vector<double> out = layer.calcOutput(inp);
    
    vector<int> a = {2,3,3,3,2};
    vector<double> inp = {2,3};
    Neural_Net NN(a);
    vector<double> out = NN.computeOutputsofNN(inp);
    for (int i =0;i<out.size();i++){
        cout << out[i] << endl;
    }

    vector<vector<string>> csv = readCSV("Data/fake_bills.csv");
    
}