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

    for (unsigned int layerNum = 0; layerNum < numLayers; layerNum++) {
        _layer.push_back(Layer());
        for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++) {
            _layer.back().push_back(0.0);
        }
    }
}
