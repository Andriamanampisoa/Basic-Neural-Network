/*
 * Filename: Basic-Neural-Network/src/ArgumentParser.cpp
 * Created Date: Monday, May 25th 2026, 5:36:15 pm
 * Author: Toa
 * Description: Implementation file for command-line argument parsing
*/

#include "ArgumentParser.hpp"

#include <charconv>
#include <cstring>
#include <sstream>

ArgumentParser::ArgumentParser(int argc, char **argv) : _argc(argc),
    _argv(argv), _valid(false)
{
    _parse();
}

bool ArgumentParser::isValid() const
{
    return (_valid);
}

const std::string &ArgumentParser::getErrorMessage() const
{
    return (_errorMessage);
}

const std::vector<unsigned int> &ArgumentParser::getTopology() const
{
    return (_topology);
}

void ArgumentParser::printUsage(std::ostream &os, const char *programName)
{
    const char *name = (programName && programName[0] != '\0') ? programName : "BasicNeuralNetwork";

    os << "Usage: " << name << " <topology...>\n"
       << "  topology: positive integers, neurons per layer (input, hidden..., output)\n"
       << "  Example:  " << name << " 3 3 3 2\n";
}

bool ArgumentParser::_parseLayerSize(const char *arg, unsigned int &value) const
{
    unsigned int parsed = 0;
    std::size_t len = 0;
    std::from_chars_result result;

    if (arg == nullptr || arg[0] == '\0')
        return (false);
    if (arg[0] == '-' || arg[0] == '+')
        return (false);
    len = std::strlen(arg);
    result = std::from_chars(arg, arg + len, parsed);
    if (result.ec != std::errc{} || result.ptr != arg + len)
        return (false);
    if (parsed < MIN_NEURONS_PER_LAYER)
        return (false);
    value = parsed;
    return (true);
}

void ArgumentParser::_parse()
{
    std::ostringstream oss;
    unsigned int argCount = 0;
    unsigned int layerSize = 0;

    _topology.clear();
    _errorMessage.clear();
    _valid = false;

    if (_argc < 2) {
        _errorMessage = "Missing topology: at least one layer size is required.";
        return;
    }
    argCount = static_cast<unsigned int>(_argc - 1);
    if (argCount < MIN_LAYERS) {
        oss << "Topology must contain at least " << MIN_LAYERS << " layers (input and output).";
        _errorMessage = oss.str();
        return;
    }
    if (argCount > MAX_LAYERS) {
        oss << "Too many layers (maximum is " << MAX_LAYERS << ").";
        _errorMessage = oss.str();
        return;
    }
    _topology.reserve(argCount);
    for (unsigned int i = 1; i < _argc; ++i) {
        layerSize = 0;
        if (!_parseLayerSize(_argv[i], layerSize)) {
            oss.str("");
            oss << "Invalid layer size at argument " << i << ": \"" << _argv[i]
                << "\" (expected a positive integer >= " << MIN_NEURONS_PER_LAYER << ").";
            _errorMessage = oss.str();
            return;
        }
        _topology.push_back(layerSize);
    }
    _valid = true;
}
