/*
 * Filename: Basic-Neural-Network/src/NeuralNetwork.cpp
 * Created Date: Wednesday, May 20th 2026, 3:51:28 pm
 * Author: Toa
 * Description: Implementation file for the Neural Network class
*/

#include "NeuralNetwork.hpp"

#include <stdexcept>
#include <string>

NeuralNetwork::NeuralNetwork(const std::vector<unsigned int> &topology)
{
    const unsigned int numLayers = topology.size();
    unsigned int numOutputs = 0;

    for (unsigned int layerNum = 0; layerNum < numLayers; ++layerNum) {
        _layer.push_back(Layer());
        numOutputs = (layerNum == numLayers - 1) ? 0 : topology[layerNum + 1];

        // topology[layerNum] neurons + 1 bias neuron (separate push avoids
        // unsigned wraparound if neuronNum ever reached UINT_MAX)
        const unsigned int layerSize = topology[layerNum];

        _layer.back().reserve(static_cast<std::size_t>(layerSize) + 1u);
        for (unsigned int neuronNum = 0; neuronNum < layerSize; ++neuronNum) {
            _layer.back().push_back(Neuron(numOutputs));
        }
        _layer.back().push_back(Neuron(numOutputs));

        // Bias neuron is the last neuron of the layer; its output is always 1.0
        _layer.back().back().setOutputValue(1.0);
    }
}

void NeuralNetwork::forwardPropagation(const std::vector<double> &inputValues)
{
    if (_layer.empty()) {
        throw std::runtime_error("NeuralNetwork::forwardPropagation: network has no layers");
    }

    Layer &inputLayer = _layer.front();
    const std::size_t expectedInputs = inputLayer.size() - 1; // exclude bias

    if (inputValues.size() != expectedInputs) {
        throw std::invalid_argument(
            "NeuralNetwork::forwardPropagation: expected " + std::to_string(expectedInputs)
            + " input value(s), got " + std::to_string(inputValues.size()));
    }

    for (std::size_t i = 0; i < inputValues.size(); ++i) {
        inputLayer[i].setOutputValue(inputValues[i]);
    }

    for (std::size_t layerNum = 1; layerNum < _layer.size(); ++layerNum) {
        const Layer &prevLayer = _layer[layerNum - 1];
        Layer &layer = _layer[layerNum];
        for (std::size_t n = 0; n + 1 < layer.size(); ++n) {
            layer[n].feedForward(prevLayer, static_cast<unsigned int>(n));
        }
    }
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

Layer &NeuralNetwork::getLayer(unsigned int layerIndex)
{
    if (layerIndex >= _layer.size()) {
        throw std::out_of_range("NeuralNetwork::getLayer: layer index out of range");
    }
    return (_layer[layerIndex]);
}
