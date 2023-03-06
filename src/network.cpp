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
    this->layerSizes = a;
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
void Neural_Net::saveNNtoFile(string fileName){
    // Create and open a text file
    ofstream file(fileName);
    
    //Loop for iterating through layers and writing layers sizes to file
    for(int i=0;i<this->layerSizes.size();i++)
    {
        //Writing layers sizes to file
        file<<this->layerSizes[i]<<",";
    }
    file <<endl;

    //Loop for iterating through layers
    for(int i=0; i < this->layers.size();i++){

        //Loop for iterating through nodes in each Layer
        for(int j=0;j < this->layers[i].nodes.size();j++){
            
            //Loop for iterating through weights in each node
            for (int k = 0; k < this->layers[i].nodes[j].weights.size(); k++)
            {
                //Writing the weights to the file separated by a comma
                file << this->layers[i].nodes[j].weights[k] << ",";
            }
            //Writing Bias of the Node to the file
            file << this->layers[i].nodes[j].biasN << endl;      
            
        }
    }

    //Closing the file
    file.close();

}

void Neural_Net::loadNNfromFile(string fileName){
    //Initializing some vars
    ifstream file(fileName);
    string lineText;
    string word;
    vector<int> NNsize;

    //Read the first line
    getline(file,lineText);
    
    //Reading each number separated by a comma and putting them into NNsize vector
    stringstream str(lineText);
    while(getline(str, word, ',')){

        NNsize.push_back(stoi(word));
        //cout << stoi(word)<<",";
    }
    //cout <<endl;

    //Initializing Neural Network again
    //Setting Vars    
    layers.clear();
    layerSizes.clear();
    int S = NNsize.size();
    this->layerSizes = NNsize;
    this->inputSize = NNsize[0];
    this->outputSize = NNsize[S-1];
    this->numHiddenLayers = S-2;
    
    //Creating Layers
    for (int i = 0; i < S-1; i++)
    {
        
        //Creates a object of class Layer
        Layer L(NNsize[i],NNsize[i+1]);
        
        //Adds the object in the vector
        this->layers.push_back(L);
    }

    //Index Vars to keep track of which layer and node values we are accessing
    int layer = 0;
    int node = 0;

    //Reading all the lines starting from the 2nd using a while loop and storing the content of each in lineText
    while(getline(file, lineText))
		{
            //Temporary vector to store all values in a line
            vector<double> temp;

            //Reading The numbers(doubles) separated by ccomma in each line
			stringstream str(lineText);
            while(getline(str, word, ',')){
                double val = stod(word);
				temp.push_back(val);
			}

            //If Last node of layer has been reached, node is resset to 0 and layer increassed by 1
			if(node == NNsize[layer+1]){
                node = 0;
                layer += 1;                
            }

            
            //Setting weights from temp vector using current Layer and Node values
            for (int i = 0; i < (temp.size()-1); i++)
            {
                //Setting weights
                this->layers[layer].nodes[node].weights[i] = temp[i];
            }
            //Setting Bias
            this->layers[layer].nodes[node].biasN = temp[temp.size()-1];
            
            //Incrementing node 
            node++;
		}

}


//Main Function
int main() {
  
    // Setting random seed as current time
    srand (static_cast <unsigned> (time(0)));

    
    vector<vector<string>> y = readCSV("Data/fake_bills.csv");
    vector<vector<string>> x_temp;
    splitCsvVec(y,x_temp,1);
    

    vector<vector<double>> x = convertTo2dDoubleVec(x_temp);
    //printCsvVecDoub(x);

    vector<vector<double>> expected_y = calcExpectedOutputs(y);

    vector<int> Size = {6,10,10,2};
    
    Neural_Net BestNN(Size);
    double leastLoss = 10000.0;
    
    
    for (int i = 0; i < 500; i++)
    {
        Neural_Net NN(Size);
        double loss = TotalLoss(x,expected_y,NN);
        if ( loss < leastLoss){
            //cout << loss;
            leastLoss = loss;
            BestNN = NN; 
        }
        
    }
    
    
    cout << TotalLoss(x,expected_y,BestNN) << endl;
    BestNN.saveNNtoFile("best.txt");
    
    Neural_Net h(Size);
    h.loadNNfromFile("best.txt");
    cout << TotalLoss(x,expected_y,h);
}