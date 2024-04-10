#pragma once
#include "Log.h"
#include <chrono>
#define MEASURE_TIME(code) \
    do { \
        auto start = std::chrono::high_resolution_clock::now(); \
        code; \
        auto end = std::chrono::high_resolution_clock::now(); \
        std::chrono::duration<double> elapsed = end - start; \
        Logger::log(2,"Elapsed time: {}  seconds",elapsed.count() );\
    } while(0)