#pragma once
#include "Log.h"
#include <chrono>
#define MEASURE_TIME(...)  auto start = std::chrono::high_resolution_clock::now(); \
        __VA_ARGS__ \
        auto end = std::chrono::high_resolution_clock::now(); \
        std::chrono::duration<double> elapsed = end - start; \
        Logger::log(2,"Elapsed time: {}  seconds",elapsed.count() );\


#define MEASURE_TIME2(MSG,...)  do { \
        auto start = std::chrono::high_resolution_clock::now(); \
        __VA_ARGS__; \
        auto end = std::chrono::high_resolution_clock::now(); \
        std::chrono::duration<double> elapsed = end - start; \
        debug(MSG); \
        Logger::log(3," ==> {}  seconds",elapsed.count() ); \
    } while(0)
