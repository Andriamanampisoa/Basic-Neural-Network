/*
 * Filename: Basic-Neural-Network/src/NeuralNetwork.cpp
 * Created Date: Wednesday, May 20th 2026, 3:51:28 pm
 * Author: Toa
 * Description: Implementation file for the Neural Network class
*/

#include "NeuralNetwork.hpp"

#include <stdexcept>

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> &topology)
{
    const unsigned int numLayers = topology.size();
    unsigned int numOutputs = 0;

    for (unsigned int layerNum = 0; layerNum < numLayers; ++layerNum) {
        _layer.push_back(Layer());
        numOutputs = (layerNum == numLayers - 1) ? 0 : topology[layerNum + 1];

        // topology[layerNum] neurons + 1 bias neuron
        for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
            _layer.back().push_back(Neuron(numOutputs));
        }

        // Bias neuron is the last neuron of the layer; its output is always 1.0
        _layer.back().back().setOutputValue(1.0);
    }
}

void NeuralNetwork::forwardPropagation(const std::vector<double> & /*inputValues*/)
{
    // TODO: implement in the Forward Propagation step
}

void NeuralNetwork::backPropagation(const std::vector<double> & /*expectedValues*/)
{
    // TODO: implement after Forward Propagation
}

void NeuralNetwork::getResults(std::vector<double> &resultsValues) const
{
    resultsValues.clear();

    if (_layer.empty()) {
        return;
    }

    const Layer &outputLayer = _layer.back();

    // Exclude the bias neuron (last neuron of the layer)
    for (std::size_t n = 0; n + 1 < outputLayer.size(); ++n) {
        resultsValues.push_back(outputLayer[n].getOutputValue());
    }
}

unsigned int NeuralNetwork::getLayerCount() const
{
    return (static_cast<unsigned int>(_layer.size()));
}

const Layer &NeuralNetwork::getLayer(unsigned int layerIndex) const
{
    if (layerIndex >= _layer.size()) {
        throw std::out_of_range("NeuralNetwork::getLayer: layer index out of range");
    }
    return (_layer[layerIndex]);
}
