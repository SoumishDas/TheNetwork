//Header Files
#include "network.h"
#include "activations.h"
#include "helperFuncs.h"
#include "dataPrep.h"



dataPoint::dataPoint(vector<double> inputs,vector<double> expected_outputs){
    this->inputs = inputs;
    this->expected_outputs = expected_outputs;
}

Node::Node(int numNodeIn){

    //The Loop enters all the inputs and weights from the array into their respective vectors
    for (int i = 0; i < numNodeIn; i++)
    {
        double z = getRandDoub(-1,1);
        //cout << z<<"##"<<endl;
        this->weights.push_back(z);
        this->costGradientW.push_back(0.0);
        this->weightVelocities.push_back(0.0);
        
    }
    
    //The bias value of a particular Node
    this->biasN = getRandDoub(-1,1);
    this->biasVelocity = 0.0;
    //cout << biasN<<"#"<<endl;
}


Layer::Layer(const int NodesIn,const int NodesOut){
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


vector<double> Layer::calcOutput(const vector<double> &inputs){

    
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

vector<double> Layer::calcOutput(const vector<double> &inputs,layerLearnData& learnData ){

    learnData.inputs = inputs;
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
        learnData.weightedInputs.push_back(weightedInput);
        learnData.activations.push_back(activationFunc(weightedInput));


    }
    return learnData.activations;
}


Neural_Net::Neural_Net(const vector<int>& a){

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

vector<double> Neural_Net::computeOutputsofNN(const vector<double>& inputs){

    vector<double>tempOut = inputs;

    for (int layer=0;layer<this->layers.size();layer++){
        tempOut = layers[layer].calcOutput(tempOut);
    }

    return tempOut;
}


double nodeCost(const double outputActivation,const double expectedOutput){
    double e = outputActivation - expectedOutput;
    return e*e;
}

double Loss(const vector<double>& input,const vector<double>& expectedOutput,Neural_Net& NN){
    vector<double> output = NN.computeOutputsofNN(input);
    double cost = 0.0;

    
    for (int i = 0; i < output.size(); i++)
    {
        cost += nodeCost(output[i],expectedOutput[i]);
    }

    return 0.5 * cost;
    
}

double TotalLoss(const vector<vector<double>>& inputs,const vector<vector<double>>& expectedOutputs, Neural_Net& NN){

    if(inputs.size() != expectedOutputs.size()){
        cout << "DIFFERENT NO OF INPUTS AND EXPECTED OUTPUTS";
        return 0;
    }

    double totalLoss = 0.0;

    //Added Multithreading using OpenMP
    #pragma omp parallel for reduction(+:totalLoss)
    for(int i = 0; i < inputs.size(); i++)
    {
        totalLoss += Loss(inputs[i],expectedOutputs[i],NN);
    }


    return totalLoss / inputs.size();
}


void Neural_Net::saveNNtoFile(const string& fileName){
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

void Neural_Net::loadNNfromFile(const string& fileName){
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

Neural_Net getBestNnRandom(const vector<int>& size,const vector<vector<double>>& x,const vector<vector<double>>& expected_y,int numTries){
    Neural_Net BestNN(size);
    double leastLoss = 10000.0;
    
    
    for (int i = 0; i < numTries; i++)
    {
        Neural_Net NN(size);
        double loss = TotalLoss(x,expected_y,NN);
        if ( loss < leastLoss){
            //cout << loss;
            leastLoss = loss;
            BestNN = NN; 
        }
        
    }
    return BestNN;
}

void Layer::applyGradients(const double &learnRate){

    for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
    {
        // Updating Bias using Cost Gradient
        nodes[nodeOut].biasN -= nodes[nodeOut].costGradientB * learnRate;

        // Updating Weights using Cost Gradient 
        for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
        {
            nodes[nodeOut].weights[nodeIn] -= nodes[nodeOut].costGradientW[nodeIn] * nodes[nodeOut].weights[nodeIn];
        }        
    }
}

void Neural_Net::applyAllGradients(const double& learnRate){
    for (int layer = 0; layer < this->layers.size(); layer++)
    {
        this->layers[layer].applyGradients(learnRate);
    }
    
}

void Neural_Net::learnNoCalc(const vector<vector<double>>& inputs,const vector<vector<double>>& expected_out,const double& learnRate){
    const double h = 0.0001;
    double originalCost = TotalLoss(inputs,expected_out,*this);

    for (int layer = 0; layer < this->layers.size(); layer++)
    {
        for (int nodeIn = 0; nodeIn < this->layers[layer].numNodesIn; nodeIn++){
            for (int nodeOut = 0; nodeOut < this->layers[layer].numNodesOut; nodeOut++)
            {
                this->layers[layer].nodes[nodeOut].weights[nodeIn] += h;
                double deltaCost = TotalLoss(inputs,expected_out,*this) - originalCost;
                this->layers[layer].nodes[nodeOut].weights[nodeIn] -= h;
                this->layers[layer].nodes[nodeOut].costGradientW[nodeIn] = deltaCost / h;
            }
        }

        for (int biasIndex = 0; biasIndex < this->layers[layer].nodes.size(); biasIndex++)
        {
            this->layers[layer].nodes[biasIndex].biasN += h;
            double deltaCost = TotalLoss(inputs,expected_out,*this) - originalCost;
            this->layers[layer].nodes[biasIndex].biasN -= h;
            this->layers[layer].nodes[biasIndex].costGradientB = deltaCost / h;
        }
        
    }
    
    this->applyAllGradients(learnRate);
}

void getBestNnGradientDescent(Neural_Net *NN,vector<vector<double>> x,vector<vector<double>> expected_y,int numTries,double learnRate){
    
    double loss ;
    
    
    for (int i = 0; i < numTries; i++)
    {
        NN->learnNoCalc(x,expected_y,learnRate);
        loss = TotalLoss(x,expected_y,*NN);
        cout << loss <<endl;
        
    }
    
}



void Neural_Net::LearnCalc(vector<dataPoint> &trainingData, double learnRate, double regularization = 0, double momentum = 0){
    if (this->batchLearnData.size() == 0 || this->batchLearnData.size() != trainingData.size())
		{
            this->batchLearnData.clear();
			this->batchLearnData.reserve(trainingData.size());
			for (int i = 0; i < trainingData.size(); i++)
			{
                networkLearnData learnData(layers);
				this->batchLearnData.push_back(learnData);
			}
		}

    //MultiThreaded For loop for updating gradients
    //#pragma omp parallel for
    for (int i = 0; i < trainingData.size(); i++)
    {
        UpdateGradientsCalc(trainingData[i],batchLearnData[i]);
    }
    
    // Update weights and biases based on the calculated gradients
    for (int i = 0; i < this->layers.size(); i++)
    {
        layers[i].ApplyGradientsCalc(learnRate / trainingData.size(), regularization, momentum);
    }
    
}

void Neural_Net::UpdateGradientsCalc(dataPoint &data,networkLearnData &learnData){
    // Feed data through the network to calculate outputs.
    // Save all inputs/weightedinputs/activations along the way to use for backpropagation.
    vector<double> inputsToNextLayer = data.inputs;

    for (int i = 0; i < this->layers.size(); i++)
		{
			inputsToNextLayer = this->layers[i].calcOutput(inputsToNextLayer, learnData.layerData[i]);
		}
    
    // -- Backpropagation --
    int outputLayerIndex = this->layers.size() - 1;
    Layer &outputLayer = this->layers[outputLayerIndex];
    layerLearnData outputLearnData = learnData.layerData[outputLayerIndex];

    // Update output layer gradients
    outputLayer.CalculateOutputLayerNodeValues(outputLearnData, data.expected_outputs);
    outputLayer.UpdateGradients(outputLearnData);

    // Update all hidden layer gradients
    for (int i = outputLayerIndex - 1; i >= 0; i--)
    {
        layerLearnData layerLearnData = learnData.layerData[i];
        Layer hiddenLayer = layers[i];

        hiddenLayer.CalculateHiddenLayerNodeValues(layerLearnData, layers[i + 1], learnData.layerData[i + 1].nodeValues);
        hiddenLayer.UpdateGradients(layerLearnData);
    }
}


// Calculate the "node values" for the output layer. This is an array containing for each node:
// the partial derivative of the cost with respect to the weighted input
void Layer::CalculateOutputLayerNodeValues(layerLearnData &layerLearnData, vector<double> &expectedOutputs){
    layerLearnData.nodeValues.clear();
    for (int i = 0; i < expectedOutputs.size(); i++)
		{
            

			// Evaluate partial derivatives for current node: cost/activation & activation/weightedInput
			double costDerivative = CostDerivative(layerLearnData.activations[i], expectedOutputs[i]);
			double activationDerivative = TanHActDerv(layerLearnData.weightedInputs[i]);
            double nodeValue = costDerivative * activationDerivative;
			layerLearnData.nodeValues.push_back(nodeValue);
		}
}

// Calculate the "node values" for a hidden layer. This is an array containing for each node:
// the partial derivative of the cost with respect to the weighted input
void Layer::CalculateHiddenLayerNodeValues(layerLearnData &layerLearnData, Layer &oldLayer, vector<double> &oldNodeValues)
{
    layerLearnData.nodeValues.clear();
    for (int newNodeIndex = 0; newNodeIndex < this->numNodesOut; newNodeIndex++)
    {
        double newNodeValue = 0;
        for (int oldNodeIndex = 0; oldNodeIndex < oldNodeValues.size(); oldNodeIndex++)
        {
            // Partial derivative of the weighted input with respect to the input
            double weightedInputDerivative = oldLayer.nodes.at(oldNodeIndex).weights.at(newNodeIndex);
            newNodeValue += weightedInputDerivative * oldNodeValues[oldNodeIndex];
        }
        newNodeValue *= TanHActDerv(layerLearnData.weightedInputs.at(newNodeIndex));
        layerLearnData.nodeValues.push_back(newNodeValue);
    }

}


// TBDDDDDDDD :: IMPLEMENT PROPER LOCKING INSTEAD OF OMP CRITICAL

void Layer::UpdateGradients(layerLearnData layerLearnData)
	{
		// Update cost gradient with respect to weights (lock for multithreading)
		//lock (costGradientW)
        #pragma omp critical
		{
			for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
			{
				double nodeValue = layerLearnData.nodeValues.at(nodeOut);
				for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
				{
					// Evaluate the partial derivative: cost / weight of current connection
					double derivativeCostWrtWeight = layerLearnData.inputs[nodeIn] * nodeValue;
					// The costGradientW array stores these partial derivatives for each weight.
					// Note: the derivative is being added to the array here because ultimately we want
					// to calculate the average gradient across all the data in the training batch
                    this->nodes.at(nodeOut).costGradientW.at(nodeIn) += derivativeCostWrtWeight;
				}
			}
		}

		// Update cost gradient with respect to biases (lock for multithreading)
		//lock (costGradientB)
        #pragma omp critical
		{
			for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
			{
				// Evaluate partial derivative: cost / bias
				double derivativeCostWrtBias = 1 * layerLearnData.nodeValues[nodeOut];
				this->nodes.at(nodeOut).costGradientB += derivativeCostWrtBias;
			}
		}
	}


double CostDerivative(double predictedOutput, double expectedOutput)
{
    return predictedOutput - expectedOutput;
}

// Update weights and biases based on previously calculated gradients.
	// Also resets the gradients to zero.
void Layer::ApplyGradientsCalc(double learnRate, double regularization, double momentum)
	{
		double weightDecay = (1 - regularization * learnRate);

        for (int nodeOut = 0; nodeOut < this->numNodesOut; nodeOut++)
        {
            for (int nodeIn = 0; nodeIn < this->numNodesIn; nodeIn++)
            {
                // Updating Weights
                double weight = this->nodes.at(nodeOut).weights.at(nodeIn);
                double velocity = this->nodes.at(nodeOut).weightVelocities.at(nodeIn) * momentum   -   this->nodes.at(nodeOut).costGradientW[nodeIn] * learnRate;
                this->nodes.at(nodeOut).weightVelocities.at(nodeIn) = velocity;
                this->nodes.at(nodeOut).weights.at(nodeIn) = weight * weightDecay + velocity;
                this->nodes.at(nodeOut).costGradientW[nodeIn] = 0;

                //Updating Biases
                velocity = this->nodes.at(nodeOut).biasVelocity * momentum - this->nodes.at(nodeOut).costGradientB * learnRate;
                this->nodes.at(nodeOut).biasVelocity = velocity;
                this->nodes.at(nodeOut).biasN += velocity;
                this->nodes.at(nodeOut).costGradientB = 0;
            }
            
        }
        

	}