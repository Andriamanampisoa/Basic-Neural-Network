/*
 * Filename: Basic-Neural-Network/src/ArgumentParser.cpp
 * Created Date: Monday, May 26th 2026, 4:25:14 pm
 * Author: Toa
 * Description: Unit tests for the ArgumentParser class.
*/

#include "ArgumentParser.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

namespace {

    class ArgvBuilder
    {
        public:

        explicit ArgvBuilder(std::initializer_list<std::string> args)
        {
            _build(args.begin(), args.end());
        }

        explicit ArgvBuilder(const std::vector<std::string> &args)
        {
            _build(args.begin(), args.end());
        }

        template<typename Iterator>
        void _build(Iterator begin, Iterator end)
        {
            for (Iterator it = begin; it != end; ++it) {
                _storage.push_back(*it);
            }
            _argv.reserve(_storage.size());
            for (auto &stored : _storage) {
                _argv.push_back(stored.data());
            }
        }

        int argc() const
        {
            return (static_cast<int>(_argv.size()));
        }

        char **argv()
        {
            return (_argv.data());
        }

        private:

        std::vector<std::string> _storage;
        std::vector<char *> _argv;
    };

    ArgumentParser makeParser(std::initializer_list<std::string> args)
    {
        ArgvBuilder builder(args);
        return (ArgumentParser(builder.argc(), builder.argv()));
    }

}

TEST(ArgumentParserTest, ValidTopology_TwoLayers)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "3", "2"});

    ASSERT_TRUE(parser.isValid());
    EXPECT_EQ(parser.getErrorMessage(), "");
    ASSERT_EQ(parser.getTopology().size(), 2u);
    EXPECT_EQ(parser.getTopology()[0], 3u);
    EXPECT_EQ(parser.getTopology()[1], 2u);
}

TEST(ArgumentParserTest, ValidTopology_MultipleLayers)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "3", "3", "3", "2"});

    ASSERT_TRUE(parser.isValid());
    const std::vector<unsigned int> expected = {3, 3, 3, 2};
    EXPECT_EQ(parser.getTopology(), expected);
}

TEST(ArgumentParserTest, ValidTopology_LargeLayerSizes)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "1024", "512"});

    ASSERT_TRUE(parser.isValid());
    EXPECT_EQ(parser.getTopology()[0], 1024u);
    EXPECT_EQ(parser.getTopology()[1], 512u);
}

TEST(ArgumentParserTest, ValidTopology_MaxLayerCount)
{
    std::vector<std::string> args = {"BasicNeuralNetwork"};

    for (unsigned int i = 0; i < 256; ++i) {
        args.push_back("1");
    }
    ArgvBuilder builder(args);
    ArgumentParser parser(builder.argc(), builder.argv());

    ASSERT_TRUE(parser.isValid());
    EXPECT_EQ(parser.getTopology().size(), 256u);
}

TEST(ArgumentParserTest, MissingArguments_OnlyProgramName)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getTopology().size(), 0u);
    EXPECT_EQ(parser.getErrorMessage(),
              "Missing topology: at least one layer size is required.");
}

TEST(ArgumentParserTest, TooFewLayers_SingleLayerSize)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "3"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getTopology().size(), 0u);
    EXPECT_EQ(parser.getErrorMessage(),
              "Topology must contain at least 2 layers (input and output).");
}

TEST(ArgumentParserTest, TooManyLayers_ExceedsMaximum)
{
    std::vector<std::string> args = {"BasicNeuralNetwork"};

    for (unsigned int i = 0; i < 257; ++i) {
        args.push_back("1");
    }

    ArgvBuilder builder(args);
    ArgumentParser parser(builder.argc(), builder.argv());

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getTopology().size(), 0u);
    EXPECT_EQ(parser.getErrorMessage(),
              "Too many layers (maximum is 256).");
}

TEST(ArgumentParserTest, InvalidLayerSize_NonNumeric)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "3", "abc", "2"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getTopology().size(), 0u);
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 2: \"abc\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, InvalidLayerSize_Zero)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "0", "3"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 1: \"0\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, InvalidLayerSize_Negative)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "-1", "3"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 1: \"-1\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, InvalidLayerSize_PlusSignPrefix)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "+5", "3"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 1: \"+5\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, InvalidLayerSize_Decimal)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "3.5", "2"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 1: \"3.5\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, InvalidLayerSize_TrailingCharacters)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "12abc", "2"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 1: \"12abc\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, InvalidLayerSize_EmptyArgument)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "", "2"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 1: \"\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, InvalidLayerSize_FailsOnFirstInvalidArgument)
{
    ArgumentParser parser = makeParser({"BasicNeuralNetwork", "3", "bad", "4", "2"});

    EXPECT_FALSE(parser.isValid());
    EXPECT_EQ(parser.getTopology().size(), 0u);
    EXPECT_EQ(parser.getErrorMessage(),
              "Invalid layer size at argument 2: \"bad\" (expected a positive integer >= 1).");
}

TEST(ArgumentParserTest, PrintUsage_CustomProgramName)
{
    std::ostringstream output;

    ArgumentParser::printUsage(output, "./BasicNeuralNetwork");

    const std::string usage = output.str();
    EXPECT_NE(usage.find("Usage: ./BasicNeuralNetwork"), std::string::npos);
    EXPECT_NE(usage.find("Example:  ./BasicNeuralNetwork 3 3 3 2"), std::string::npos);
    EXPECT_NE(usage.find("topology: positive integers"), std::string::npos);
}

TEST(ArgumentParserTest, PrintUsage_NullProgramNameUsesDefault)
{
    std::ostringstream output;

    ArgumentParser::printUsage(output, nullptr);

    EXPECT_NE(output.str().find("Usage: BasicNeuralNetwork"), std::string::npos);
}

TEST(ArgumentParserTest, PrintUsage_EmptyProgramNameUsesDefault)
{
    std::ostringstream output;

    ArgumentParser::printUsage(output, "");

    EXPECT_NE(output.str().find("Usage: BasicNeuralNetwork"), std::string::npos);
}
