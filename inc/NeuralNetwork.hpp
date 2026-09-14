/*
 * Filename: Basic-Neural-Network/inc/NeuralNetwork.hpp
 * Created Date: Wednesday, May 20th 2026, 3:51:20 pm
 * Author: Toa
 * Description: Header file for the Neural Network class
*/

#pragma once

#include "types.hpp"

/**
 * @file NeuralNetwork.hpp
 * @brief Header file for the Neural Network class
 */
class NeuralNetwork
{
    public:

    /**
     * @brief Constructor for the Neural Network class.
     * @details The topology is a vector of the number of neurons in each layer.
     * The first layer is the input layer, the last layer is the output layer, and the layers in between are the hidden layers.
     * Each layer has a bias neuron whose output is fixed to 1.0.
     * @param topology The topology of the Neural Network
     */
    NeuralNetwork(const std::vector<unsigned int> &topology);

    /**
     * @brief Forward propagation for the Neural Network class
     * @details Sets the input layer from inputValues, then feeds each subsequent
     * layer forward (bias neurons keep output 1.0 and are not updated).
     * @param inputValues Inputs for the first layer (must match input size, without bias)
     */
    void forwardPropagation(const std::vector<double> &inputValues);

    /**
     * @brief Back propagation for the Neural Network class
     * @param expectedValues The expected values for the back propagation
     * @note Not implemented yet
     */
    void backPropagation(const std::vector<double> &expectedValues);

    /**
     * @brief Read the network output values (excluding the bias neuron)
     * @param resultsValues Filled with the output layer activations
     */
    void getResults(std::vector<double> &resultsValues) const;

    /**
     * @brief Number of layers in the network
     * @return Layer count including input and output
     */
    unsigned int getLayerCount() const;

    /**
     * @brief Access a layer by index
     * @param layerIndex Zero-based layer index
     * @return Const reference to the layer
     */
    const Layer &getLayer(unsigned int layerIndex) const;

    /**
     * @brief Access a layer by index (mutable)
     * @param layerIndex Zero-based layer index
     * @return Reference to the layer
     */
    Layer &getLayer(unsigned int layerIndex);

    private:

    std::vector<Layer> _layer;
};
