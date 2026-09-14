/*
 * Filename: Basic-Neural-Network/tests/NeuralNetwork_test.cpp
 * Created Date: Monday, September 14th 2026
 * Author: Toa
 * Description: Unit tests for the NeuralNetwork class foundations
*/

#include "NeuralNetwork.hpp"

#include <gtest/gtest.h>

#include <stdexcept>
#include <vector>

TEST(NeuralNetworkTest, Constructor_CreatesExpectedLayerCount)
{
    NeuralNetwork network({3, 2});

    EXPECT_EQ(network.getLayerCount(), 2u);
}

TEST(NeuralNetworkTest, Constructor_CreatesExpectedNeuronCountsWithBias)
{
    // topology 3-4-2 → layers sizes: 4, 5, 3 (each +1 bias)
    NeuralNetwork network({3, 4, 2});

    ASSERT_EQ(network.getLayerCount(), 3u);
    EXPECT_EQ(network.getLayer(0).size(), 4u);
    EXPECT_EQ(network.getLayer(1).size(), 5u);
    EXPECT_EQ(network.getLayer(2).size(), 3u);
}

TEST(NeuralNetworkTest, Constructor_BiasNeuronOutputIsOne)
{
    NeuralNetwork network({3, 2});

    EXPECT_DOUBLE_EQ(network.getLayer(0).back().getOutputValue(), 1.0);
    EXPECT_DOUBLE_EQ(network.getLayer(1).back().getOutputValue(), 1.0);
}

TEST(NeuralNetworkTest, Constructor_NonBiasNeuronsStartAtZero)
{
    NeuralNetwork network({2, 1});

    const Layer &inputLayer = network.getLayer(0);
    EXPECT_DOUBLE_EQ(inputLayer[0].getOutputValue(), 0.0);
    EXPECT_DOUBLE_EQ(inputLayer[1].getOutputValue(), 0.0);
}

TEST(NeuralNetworkTest, Constructor_HiddenLayerHasConnectionsToNextLayer)
{
    NeuralNetwork network({3, 4, 2});

    // Each neuron in layer 0 connects to 4 neurons of layer 1 (not to bias)
    for (const Neuron &neuron : network.getLayer(0)) {
        EXPECT_EQ(neuron.getOutputConnections().size(), 4u);
    }

    // Each neuron in layer 1 connects to 2 output neurons
    for (const Neuron &neuron : network.getLayer(1)) {
        EXPECT_EQ(neuron.getOutputConnections().size(), 2u);
    }

    // Output layer has no outgoing connections
    for (const Neuron &neuron : network.getLayer(2)) {
        EXPECT_TRUE(neuron.getOutputConnections().empty());
    }
}

TEST(NeuralNetworkTest, GetResults_ExcludesBiasAndMatchesOutputSize)
{
    NeuralNetwork network({3, 2});
    std::vector<double> results;

    network.getResults(results);

    ASSERT_EQ(results.size(), 2u);
    EXPECT_DOUBLE_EQ(results[0], 0.0);
    EXPECT_DOUBLE_EQ(results[1], 0.0);
}

TEST(NeuralNetworkTest, GetLayer_ThrowsOnOutOfRange)
{
    NeuralNetwork network({2, 2});

    EXPECT_THROW(network.getLayer(2), std::out_of_range);
    EXPECT_THROW(network.getLayer(99), std::out_of_range);
}

TEST(NeuralNetworkTest, ForwardPropagation_StubDoesNotThrow)
{
    NeuralNetwork network({2, 2});

    EXPECT_NO_THROW(network.forwardPropagation({0.1, 0.2}));
}

TEST(NeuralNetworkTest, BackPropagation_StubDoesNotThrow)
{
    NeuralNetwork network({2, 2});

    EXPECT_NO_THROW(network.backPropagation({1.0, 0.0}));
}
