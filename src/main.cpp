/*
 * Filename: Basic-Neural-Network/src/main.cpp
 * Created Date: Wednesday, May 20th 2026, 3:38:28 pm
 * Author: Toa
 * Description: Main entry point for the neural network application
*/

#include "ArgumentParser.hpp"
#include "NeuralNetwork.hpp"

#include <iostream>

/**
 * @file main.cpp
 * @brief Main entry point for the neural network application
 */
int main(int argc, char **argv)
{
    ArgumentParser parser(argc, argv);
    std::vector<unsigned int> topology;

    if (!parser.isValid()) {
        std::cerr << "Error: " << parser.getErrorMessage() << '\n';
        ArgumentParser::printUsage(std::cerr, argv[0]);
        return (1);
    }
    topology = parser.getTopology();
    NeuralNetwork network(topology);
    return (0);
}
