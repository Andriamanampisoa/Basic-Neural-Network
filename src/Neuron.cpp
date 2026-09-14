/*
 * Filename: Basic-Neural-Network/src/Neuron.cpp
 * Created Date: Wednesday, June 21st 2026, 5:18:57 pm
 * Author: Toa
 * Description: Implementation file for the Neuron class
*/

#include "Neuron.hpp"

#include <cmath>
#include <random>
#include <stdexcept>

Neuron::Neuron(unsigned int numOutputs)
    : _outputValue(0.0)
{
    _outputConnections.reserve(numOutputs);
    for (unsigned int i = 0; i < numOutputs; ++i) {
        Connection connection;
        connection.weight = randomWeight();
        connection.deltaWeight = 0.0;
        _outputConnections.push_back(connection);
    }
}

void Neuron::setOutputValue(double value)
{
    _outputValue = value;
}

double Neuron::getOutputValue() const
{
    return (_outputValue);
}

const std::vector<Connection> &Neuron::getOutputConnections() const
{
    return (_outputConnections);
}

void Neuron::setConnectionWeight(unsigned int connectionIndex, double weight)
{
    if (connectionIndex >= _outputConnections.size()) {
        throw std::out_of_range("Neuron::setConnectionWeight: connection index out of range");
    }
    _outputConnections[connectionIndex].weight = weight;
}

void Neuron::feedForward(const std::vector<Neuron> &prevLayer, unsigned int myIndex)
{
    double sum = 0.0;

    for (std::size_t n = 0; n < prevLayer.size(); ++n) {
        const std::vector<Connection> &connections = prevLayer[n].getOutputConnections();

        if (myIndex >= connections.size()) {
            throw std::out_of_range("Neuron::feedForward: myIndex out of range for previous layer connections");
        }
        sum += prevLayer[n].getOutputValue() * connections[myIndex].weight;
    }
    _outputValue = transferFunction(sum);
}

double Neuron::transferFunction(double sum)
{
    return (std::tanh(sum));
}

double Neuron::transferFunctionDerivative(double outputValue)
{
    // d/dx tanh(x) = 1 - tanh(x)^2
    return (1.0 - outputValue * outputValue);
}

double Neuron::randomWeight()
{
    static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    return (distribution(generator));
}
