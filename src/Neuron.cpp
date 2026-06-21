/*
 * Filename: Basic-Neural-Network/src/Neuron.cpp
 * Created Date: Wednesday, June 21st 2026, 5:18:57 pm
 * Author: Toa
 * Description: Implementation file for the Neuron class
*/

#include <random>

#include "Neuron.hpp"

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

double Neuron::randomWeight()
{
    static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    return (distribution(generator));
}

double Neuron::getOutputValue() const
{
    return (_outputValue);
}

const std::vector<Connection> &Neuron::getOutputConnections() const
{
    return (_outputConnections);
}
