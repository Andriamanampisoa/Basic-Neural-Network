/*
 * Filename: Basic-Neural-Network/tests/Neuron_test.cpp
 * Created Date: Monday, June 21st 2026, 5:45:04 am
 * Author: Toa
 * Description: Unit tests for the Neuron class
*/

#include "Neuron.hpp"

#include <gtest/gtest.h>

#include <set>

namespace {

bool isWeightInRange(double weight)
{
    return (weight >= -1.0 && weight <= 1.0);
}

} // namespace

TEST(NeuronTest, Constructor_ZeroOutputsHasNoConnections)
{
    Neuron neuron(0);

    EXPECT_EQ(neuron.getOutputValue(), 0.0);
    EXPECT_TRUE(neuron.getOutputConnections().empty());
}

TEST(NeuronTest, Constructor_CreatesExpectedConnectionCount)
{
    Neuron neuron(4);

    EXPECT_EQ(neuron.getOutputConnections().size(), 4u);
}

TEST(NeuronTest, Constructor_OutputValueIsZero)
{
    Neuron neuron(3);

    EXPECT_DOUBLE_EQ(neuron.getOutputValue(), 0.0);
}

TEST(NeuronTest, Constructor_DeltaWeightsAreZero)
{
    Neuron neuron(5);

    for (const Connection &connection : neuron.getOutputConnections()) {
        EXPECT_DOUBLE_EQ(connection.deltaWeight, 0.0);
    }
}

TEST(NeuronTest, Constructor_WeightsAreInRange)
{
    Neuron neuron(20);

    for (const Connection &connection : neuron.getOutputConnections()) {
        EXPECT_TRUE(isWeightInRange(connection.weight));
    }
}

TEST(NeuronTest, RandomWeight_ReturnsValuesInRange)
{
    Neuron neuron(0);

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(isWeightInRange(neuron.randomWeight()));
    }
}

TEST(NeuronTest, RandomWeight_ProducesDifferentValues)
{
    Neuron neuron(0);
    std::set<double> values;

    for (int i = 0; i < 20; ++i) {
        values.insert(neuron.randomWeight());
    }

    EXPECT_GT(values.size(), 1u);
}

TEST(NeuronTest, Constructor_EachConnectionHasIndependentWeight)
{
    Neuron neuron(30);
    std::set<double> weights;

    for (const Connection &connection : neuron.getOutputConnections()) {
        weights.insert(connection.weight);
    }

    EXPECT_GT(weights.size(), 1u);
}
