#pragma once
#define FMT_HEADER_ONLY 
#include "fmt/core.h"
#include "fmt/color.h"
#include <cstdio>

#ifdef DEBUG
#define debug(...) fmt::print(fg(fmt::color::pink),__VA_ARGS__);
#else
#define debug(...) 
#endif


class Logger {
  public:
    /* log if input log level is equal or bigger to log level set */
    template <typename... Args>
    static void log(unsigned int logLevel, Args ... args) {
      if (logLevel >= mLogLevel) {
        switch (logLevel){
        case 0:
          fmt::print(fg(fmt::color::pink),args...);
          break;
        case 1:
          fmt::print(fg(fmt::color::gold),args...);
          break;
        case 2:
          fmt::print(fg(fmt::color::lime_green),args...);
          break;
        case 8:
          fmt::print(fg(fmt::color::red),args...);
          break;
        default:
          break;
        }
        fmt::print("\n");
      }
    }


  private:
    static const unsigned int mLogLevel=1;

// #include "Logger.h"
// unsigned int Logger::mLogLevel = 1;
};
    