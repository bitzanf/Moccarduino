#include "interface.hpp"
#include "funshield.h"

extern "C" {
    void setup();
    void loop();
}

#include "tested_code.ino"
