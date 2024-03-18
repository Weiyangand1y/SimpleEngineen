#define FMT_HEADER_ONLY 
#include "fmt/core.h"
#include "fmt/color.h"

#ifdef DEBUG
#define debug(...) fmt::print(fg(fmt::color::pink),__VA_ARGS__);
#else
#define debug(...) 
#endif
    