#include <iostream>
#include <vector>

using namespace std;


int input[10] = {2,2,2,2,2};
int weight[10] = {2,2,2,2,2};
int bias[10] = {2,2,2,2,2};

class Node{
    public:
        vector<double> weights;
        vector<double> biases;

};


class Layer{
    public:
        int numNodesIn,numNodesOut;
        vector<Node> nodes;
        
        Layer(int NodesIn,int NodesOut){
            this->numNodesIn = NodesIn;
            this->numNodesOut = NodesOut;

            for (int i = 0; i < numNodesOut; i++)
            {
                nodes.insert();
            }
            
        } 
};

int main() {
  
  long double out =  input[0]*weight[0] + input[1]*weight[1] + input[2]*weight[2] + input[3]*weight[3] + input[4]*weight[4] + bias[0];

  cout << out;
}