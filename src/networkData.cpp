#include "networkData.h"
#include"network.h"



layerLearnData::layerLearnData(const Layer& layer){
    this->weightedInputs.reserve(layer.numNodesOut);
    this->activations.reserve(layer.numNodesOut);
    this->nodeValues.reserve(layer.numNodesOut);
}

networkLearnData::networkLearnData(const vector<Layer>& layers){
    this->layerData.reserve(layers.size());

    for (int i = 0; i < layers.size(); i++)
    {
        layerLearnData lLD(layers[i]);
        this->layerData.push_back(lLD);
    }
    
}