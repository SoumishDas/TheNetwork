//Header Files
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;




//Classes
class Node{

    private:

        //IMP Vars
        double input1[10] = {2,2,2,2,2};
        double weight1[10] = {2,2,2,2,2};
        double bias[10] = {2,2,2,2,2};

    public:

        //Creating Vectors for weights and biases
        vector<double> weights;
        
        double biasN;

        //Constructor
        Node(int numNodeIn){

            //The Loop enters all the inputs and weights from the array into their respective vectors
            for (int i = 0; i < numNodeIn; i++)
            {
                double z = (double)(rand() % 100) /100;;
                cout << z<<"##"<<endl;
                weights.push_back(z);
                
                
            }
            
            //The bias value of a particular Node
            biasN = (double)(rand() % 1000) /100;
            cout << biasN<<"#"<<endl;
        }
};


class Layer{
    public:

        //Vars
        int numNodesIn,numNodesOut;
        vector<Node> nodes;
        
        Layer(int NodesIn,int NodesOut){
            this->numNodesIn = NodesIn;
            this->numNodesOut = NodesOut;

            //Creates and adds Nodes as per requirement
            for (int i = 0; i < numNodesOut; i++)
            {

                //Creates a object of class Node
                Node N(numNodesIn);

                //Adds the object in the vector
                nodes.push_back(N);


            }
            
        }
        double* calcOutput(double inputs[]){
            //Dynamic array for storing weighted inputs after computation
            double *weightedInputs = new double(numNodesOut);

            //For loop to iterate over the Outnodes and compute weighted inputs
            for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
            {
                // Adding Bias to the weighted input
                double weightedInput = nodes[nodeOut].biasN;

                // Adding all the inputs multiplied with weights 
                for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
                {
                    weightedInput += inputs[nodeOut] * nodes[nodeOut].weights[nodeIn];
                }
                weightedInputs[nodeOut] = weightedInput;


            }
            return weightedInputs;
        }
};


//Main Function
int main() {
  
//   long double out =  input[0]*weight[0] + input[1]*weight[1] + input[2]*weight[2] + input[3]*weight[3] + input[4]*weight[4] + bias[0];

    // Setting random seed as current time
    //srand (static_cast <unsigned> (time(0)));

    const int hiddenLayers = 4;

    // Vars for testing
    Layer layer(3,hiddenLayers) ;
    double inp[3] = {2.5,2.5,1.5};
    double *out = layer.calcOutput(inp);

    // Printing the result
    for (int i = 0; i < 1; i++)
    {
        cout << out[i]<< endl;
    }

    delete [] out;
    
}