#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <vector>
using namespace std;


// Forward Declaration to resolve dependency; Actual declaration in network.h;
class Layer;


class layerLearnData
{
    public:

	vector<double> inputs;
	vector<double> weightedInputs;
	vector<double> activations;
	vector<double> nodeValues;

	layerLearnData(const Layer& layer);
	
};

class networkLearnData
{
    public:
    
	vector<layerLearnData> layerData;

	networkLearnData(const vector<Layer>& layers);
	
};



#endif