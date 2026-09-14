/*
 * Filename: Basic-Neural-Network/tests/Neuron_test.cpp
 * Created Date: Monday, June 21st 2026, 5:45:04 am
 * Author: Toa
 * Description: Unit tests for the Neuron class
*/

#include "Neuron.hpp"

#include <gtest/gtest.h>

#include <cmath>
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

TEST(NeuronTest, Constructor_EachConnectionHasIndependentWeight)
{
    Neuron neuron(30);
    std::set<double> weights;

    for (const Connection &connection : neuron.getOutputConnections()) {
        weights.insert(connection.weight);
    }

    EXPECT_GT(weights.size(), 1u);
}

TEST(NeuronTest, SetOutputValue_UpdatesStoredValue)
{
    Neuron neuron(0);

    neuron.setOutputValue(0.42);
    EXPECT_DOUBLE_EQ(neuron.getOutputValue(), 0.42);

    neuron.setOutputValue(-0.75);
    EXPECT_DOUBLE_EQ(neuron.getOutputValue(), -0.75);
}

TEST(NeuronTest, TransferFunction_ZeroIsZero)
{
    EXPECT_DOUBLE_EQ(Neuron::transferFunction(0.0), 0.0);
}

TEST(NeuronTest, TransferFunction_MatchesTanh)
{
    EXPECT_NEAR(Neuron::transferFunction(1.0), std::tanh(1.0), 1e-12);
    EXPECT_NEAR(Neuron::transferFunction(-2.0), std::tanh(-2.0), 1e-12);
}

TEST(NeuronTest, TransferFunction_IsBounded)
{
    EXPECT_LE(Neuron::transferFunction(100.0), 1.0);
    EXPECT_GE(Neuron::transferFunction(100.0), 0.0);
    EXPECT_GE(Neuron::transferFunction(-100.0), -1.0);
    EXPECT_LE(Neuron::transferFunction(-100.0), 0.0);
}

TEST(NeuronTest, TransferFunctionDerivative_AtZero)
{
    EXPECT_DOUBLE_EQ(Neuron::transferFunctionDerivative(0.0), 1.0);
}

TEST(NeuronTest, TransferFunctionDerivative_MatchesFormula)
{
    const double output = Neuron::transferFunction(0.5);
    const double expected = 1.0 - output * output;

    EXPECT_NEAR(Neuron::transferFunctionDerivative(output), expected, 1e-12);
}
