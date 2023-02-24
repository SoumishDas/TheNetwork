//Header Files
#include <iostream>
#include <vector>
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
        vector<double> inputs;
        double biasN;

        //Constructor
        Node(int i){

            //The Loop enters all the inputs and weights from the array into their respective vectors
            for (int i = 0; i < end(weight1)-begin(weight1); i++)
            {
                weights.at(i-1) = weight1[i-1];
                inputs.at(i-1) = input1[i-1];
                
            }
            
            //The bias value of a particular Node
            biasN = bias[i];

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
                Node N(i);

                //Adds the object in the vector
                nodes.push_back(N);


            }
            
        } 
};


//Main Function
int main() {
  
//   long double out =  input[0]*weight[0] + input[1]*weight[1] + input[2]*weight[2] + input[3]*weight[3] + input[4]*weight[4] + bias[0];

//   cout << out;
}