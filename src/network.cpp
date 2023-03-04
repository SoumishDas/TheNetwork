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


double Layer::nodeCost(double outputActivation, double expectedOutput){
    double e = outputActivation - expectedOutput;
    return e*e;
}

double Loss(vector<double> input,vector<double> expectedOutput,Neural_Net NN){
    vector<double> output = NN.computeOutputsofNN(input);
    double cost = 0.0;
    for (int i = 0; i < output.size(); i++)
    {
        cost += NN.layers[NN.layers.size()-1].nodeCost(output[i],expectedOutput[i]);
    }

    return cost;
    
}

double TotalLoss(vector<vector<double>> inputs,vector<vector<double>> expectedOutputs,Neural_Net NN){

    if(inputs.size() != expectedOutputs.size()){
        cout << "DIFFERENT NO OF INPUTS AND EXPECTED OUTPUTS";
        return 0;
    }

    double totalLoss = 0.0;

    for(int i = 0; i < inputs.size(); i++)
    {
        totalLoss += Loss(inputs[i],expectedOutputs[i],NN);
    }
    return totalLoss / inputs.size();
}



//Main Function
int main() {
  
    // Setting random seed as current time
    srand (static_cast <unsigned> (time(0)));

    
    vector<vector<string>> y = readCSV("Data/fake_bills.csv");
    vector<vector<string>> x_temp;
    splitCsvVec(y,x_temp,1);
    vector<vector<string>> tem = {{"1.1","2.2"}};

    vector<vector<double>> x = convertTo2dDoubleVec(x_temp);
    //printCsvVecDoub(x);

    vector<vector<double>> expected_y = calcExpectedOutputs(y);

    vector<int> Size = {6,10,10,2};
    
    Neural_Net BestNN(Size);
    double leastLoss = 10000.0;
    // vector<double> out = NN.computeOutputsofNN(inp);
    // for (int i =0;i<out.size();i++){
    //     cout << out[i] << endl;
    // }
    
    for (int i = 0; i < 300; i++)
    {
        Neural_Net NN(Size);
        double loss = TotalLoss(x,expected_y,NN);
        if ( loss < leastLoss){
            //cout << loss;
            leastLoss = loss;
            BestNN = NN; 
        }
        
    }
    

    cout << TotalLoss(x,expected_y,BestNN);

    
    
}