/*
 * Filename: Basic-Neural-Network/src/NeuralNetwork.cpp
 * Created Date: Wednesday, May 20th 2026, 3:51:28 pm
 * Author: Toa
 * Description: Implementation file for the Neural Network class
*/

#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> &topology)
{
    unsigned int numLayers = topology.size();
    unsigned int numOutputs = 0;

    for (unsigned int layerNum = 0; layerNum < numLayers; layerNum++) {
        _layer.push_back(Layer());
        numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
        for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++) {
            _layer.back().push_back(Neuron(numOutputs));
        }
    }
}
