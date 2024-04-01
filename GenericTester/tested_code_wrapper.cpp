#include "interface.hpp"
#include "funshield.h"

#ifdef _WIN32
extern "C" {
    __declspec(dllexport) void setup();
    __declspec(dllexport) void loop();
}
#else
extern "C" {
    void setup();
    void loop();
}
#endif

#include "solution.ino"
