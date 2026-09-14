/*
 * Filename: Basic-Neural-Network/tests/NeuralNetwork_test.cpp
 * Created Date: Monday, September 14th 2026
 * Author: Toa
 * Description: Unit tests for the NeuralNetwork class foundations
*/

#include "NeuralNetwork.hpp"

#include <gtest/gtest.h>

#include <cmath>
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

TEST(NeuralNetworkTest, BackPropagation_StubDoesNotThrow)
{
    NeuralNetwork network({2, 2});

    EXPECT_NO_THROW(network.backPropagation({1.0, 0.0}));
}

TEST(NeuralNetworkTest, ForwardPropagation_ThrowsOnWrongInputSize)
{
    NeuralNetwork network({3, 2});

    EXPECT_THROW(network.forwardPropagation({0.1, 0.2}), std::invalid_argument);
    EXPECT_THROW(network.forwardPropagation({0.1, 0.2, 0.3, 0.4}), std::invalid_argument);
}

TEST(NeuralNetworkTest, ForwardPropagation_SetsInputLayerValues)
{
    NeuralNetwork network({2, 1});

    network.forwardPropagation({0.3, -0.8});

    EXPECT_DOUBLE_EQ(network.getLayer(0)[0].getOutputValue(), 0.3);
    EXPECT_DOUBLE_EQ(network.getLayer(0)[1].getOutputValue(), -0.8);
    EXPECT_DOUBLE_EQ(network.getLayer(0).back().getOutputValue(), 1.0);
}

TEST(NeuralNetworkTest, ForwardPropagation_KeepsBiasNeuronsAtOne)
{
    NeuralNetwork network({2, 2, 1});

    network.forwardPropagation({0.5, -0.5});

    EXPECT_DOUBLE_EQ(network.getLayer(0).back().getOutputValue(), 1.0);
    EXPECT_DOUBLE_EQ(network.getLayer(1).back().getOutputValue(), 1.0);
    EXPECT_DOUBLE_EQ(network.getLayer(2).back().getOutputValue(), 1.0);
}

TEST(NeuralNetworkTest, ForwardPropagation_OutputsAreInTanhRange)
{
    NeuralNetwork network({2, 3, 2});

    network.forwardPropagation({0.7, -0.2});

    std::vector<double> results;
    network.getResults(results);

    ASSERT_EQ(results.size(), 2u);
    for (double value : results) {
        EXPECT_GE(value, -1.0);
        EXPECT_LE(value, 1.0);
    }
}

TEST(NeuralNetworkTest, ForwardPropagation_MatchesManualComputationWithFixedWeights)
{
    // topology 1 → 1 (plus bias on each layer)
    NeuralNetwork network({1, 1});

    Layer &inputLayer = network.getLayer(0);
    inputLayer[0].setConnectionWeight(0, 0.5);  // input → output
    inputLayer[1].setConnectionWeight(0, -0.25); // bias → output

    network.forwardPropagation({2.0});

    const double expectedSum = 2.0 * 0.5 + 1.0 * (-0.25); // 0.75
    const double expectedOutput = std::tanh(expectedSum);

    std::vector<double> results;
    network.getResults(results);

    ASSERT_EQ(results.size(), 1u);
    EXPECT_NEAR(results[0], expectedOutput, 1e-12);
    EXPECT_DOUBLE_EQ(network.getLayer(1).back().getOutputValue(), 1.0);
}

TEST(NeuralNetworkTest, ForwardPropagation_TwoLayerHiddenMatchesChainedTanh)
{
    // topology 1 → 1 → 1 with fixed weights
    NeuralNetwork network({1, 1, 1});

    Layer &inputLayer = network.getLayer(0);
    Layer &hiddenLayer = network.getLayer(1);

    inputLayer[0].setConnectionWeight(0, 1.0);
    inputLayer[1].setConnectionWeight(0, 0.0);
    hiddenLayer[0].setConnectionWeight(0, 1.0);
    hiddenLayer[1].setConnectionWeight(0, 0.0);

    network.forwardPropagation({0.5});

    const double hidden = std::tanh(0.5 * 1.0 + 1.0 * 0.0);
    const double output = std::tanh(hidden * 1.0 + 1.0 * 0.0);

    std::vector<double> results;
    network.getResults(results);

    ASSERT_EQ(results.size(), 1u);
    EXPECT_NEAR(results[0], output, 1e-12);
}
