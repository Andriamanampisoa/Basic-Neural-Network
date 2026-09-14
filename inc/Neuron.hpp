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

    /**
     * @brief Construct a neuron with outgoing connections
     * @param numOutputs Number of neurons in the next layer (excluding bias)
     */
    Neuron(unsigned int numOutputs);

    /**
     * @brief Set the neuron output value
     * @param value Activation / input value to store
     */
    void setOutputValue(double value);

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

    /**
     * @brief Set the weight of an outgoing connection
     * @param connectionIndex Index of the connection (target neuron index)
     * @param weight New weight value
     */
    void setConnectionWeight(unsigned int connectionIndex, double weight);

    /**
     * @brief Compute this neuron's output from the previous layer
     * @details sum = Σ (prevOutput * weight_to_this_neuron), then apply transferFunction
     * @param prevLayer Previous layer (including its bias neuron)
     * @param myIndex Index of this neuron in its own layer (used to select weights)
     */
    void feedForward(const std::vector<Neuron> &prevLayer, unsigned int myIndex);

    /**
     * @brief Activation function (tanh)
     * @param sum Weighted sum of inputs
     * @return Activated output in [-1, 1]
     */
    static double transferFunction(double sum);

    /**
     * @brief Derivative of the activation function
     * @param outputValue Already activated output (tanh(x))
     * @return Derivative value used by back propagation
     */
    static double transferFunctionDerivative(double outputValue);

    private:

    /**
     * @brief Random weight generator
     * @details Generates a random weight between -1 and 1
     * @return A random weight
     */
    static double randomWeight();

    double _outputValue;
    std::vector<Connection> _outputConnections;
};
