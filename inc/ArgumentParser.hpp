/*
 * Filename: Basic-Neural-Network/inc/ArgumentParser.hpp
 * Created Date: Monday, May 25th 2026, 5:35:42 pm
 * Author: Toa
 * Description: Header file for command-line argument parsing
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * @file ArgumentParser.hpp
 * @brief Parses command-line arguments into a neural network topology
 */
class ArgumentParser
{
    public:

    /**
     * @brief Construct and parse command-line arguments
     * @param argc Argument count from main
     * @param argv Argument vector from main
     */
    ArgumentParser(int argc, char **argv);

    /**
     * @brief Whether parsing succeeded
     * @return true if a valid topology was parsed
     */
    bool isValid() const;

    /**
     * @brief Error message when parsing failed
     * @return Human-readable error description
     */
    const std::string &getErrorMessage() const;

    /**
     * @brief Parsed network topology
     * @return Number of neurons per layer (input, hidden..., output)
     */
    const std::vector<unsigned int> &getTopology() const;

    /**
     * @brief Print usage information
     * @param os Output stream
     * @param programName argv[0] or program name
     */
    static void printUsage(std::ostream &os, const char *programName);

    private:

    static constexpr unsigned int MIN_LAYERS = 2;
    static constexpr unsigned int MIN_NEURONS_PER_LAYER = 1;
    static constexpr unsigned int MAX_LAYERS = 256;

    int _argc;
    char **_argv;
    std::vector<unsigned int> _topology;
    std::string _errorMessage;
    bool _valid;

    void _parse();
    bool _parseLayerSize(const char *arg, unsigned int &value) const;
};
