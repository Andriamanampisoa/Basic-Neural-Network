/*
 * Filename: Basic-Neural-Network/inc/Neuron.hpp
 * Created Date: Wednesday, June 21st 2026, 4:58:28 pm
 * Author: Toa
 * Description: Header file for the Neuron class
*/

#pragma once

#include <vector>

/**
 * @brief Connection struct
 * @details A connection between two neurons
 */
struct Connection
{
    double weight;
    double deltaWeight;
};

/**
 * @brief Neuron class
 * @details A neuron in the neural network
 */
class Neuron
{
    public:

    Neuron(unsigned int numOutputs);

    /**
     * @brief Random weight generator
     * @details Generates a random weight between -1 and 1
     * @return A random weight
     */
    double randomWeight();

    /**
     * @brief Output value of the neuron
     * @return Current activation output
     */
    double getOutputValue() const;

    /**
     * @brief Outgoing connections of the neuron
     * @return Connections to neurons in the next layer
     */
    const std::vector<Connection> &getOutputConnections() const;

    private:
    double _outputValue;
    std::vector<Connection> _outputConnections;
};
