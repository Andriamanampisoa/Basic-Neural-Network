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
     * Each layer has a bias neuron.
     * @param topology The topology of the Neural Network
     */
    NeuralNetwork(const std::vector<unsigned int> &topology);

    /**
     * @brief Forward propagation for the Neural Network class
     * @param inputValues The input values for the forward propagation
     */
    void forwardPropagation(const std::vector<double> &inputValues);

    /**
     * @brief Back propagation for the Neural Network class
     * @param expectedValues The expected values for the back propagation
     */
    void backPropagation(const std::vector<double> &expectedValues);

    /**
     * @brief Back propagation for the Neural Network class
     * @param resultsValues The results values for the back propagation
     */
    void getResults(std::vector<double> &resultsValues) const;

    private:

    std::vector<Layer> _layer;
};
