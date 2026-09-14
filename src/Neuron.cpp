/*
 * Filename: Basic-Neural-Network/src/Neuron.cpp
 * Created Date: Wednesday, June 21st 2026, 5:18:57 pm
 * Author: Toa
 * Description: Implementation file for the Neuron class
*/

#include "Neuron.hpp"

#include <cmath>
#include <random>

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
