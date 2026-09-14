include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ArgumentParserTests
    ArgumentParser_test.cpp
    ${CMAKE_SOURCE_DIR}/src/ArgumentParser.cpp
)

target_include_directories(ArgumentParserTests PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(ArgumentParserTests GTest::gtest_main)
target_compile_features(ArgumentParserTests PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(ArgumentParserTests)

add_executable(NeuronTests
    Neuron_test.cpp
    ${CMAKE_SOURCE_DIR}/src/Neuron.cpp
)

target_include_directories(NeuronTests PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(NeuronTests GTest::gtest_main)
target_compile_features(NeuronTests PRIVATE cxx_std_17)

gtest_discover_tests(NeuronTests)

add_executable(NeuralNetworkTests
    NeuralNetwork_test.cpp
    ${CMAKE_SOURCE_DIR}/src/NeuralNetwork.cpp
    ${CMAKE_SOURCE_DIR}/src/Neuron.cpp
)

target_include_directories(NeuralNetworkTests PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(NeuralNetworkTests GTest::gtest_main)
target_compile_features(NeuralNetworkTests PRIVATE cxx_std_17)

gtest_discover_tests(NeuralNetworkTests)
