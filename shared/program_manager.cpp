#include "program_manager.hpp"
#include <iostream>

#ifdef __linux__
#include <dlfcn.h>

void ArduinoProgramManager::loadProgram(const std::string &fileName)
{
    if (mArduinoProgramHandle) throw std::runtime_error("The Arduino program is already loaded!");

    mArduinoProgramHandle = dlopen(fileName.c_str(), RTLD_NOW);
    if (!mArduinoProgramHandle) throw std::runtime_error(dlerror());

    mArduinoSetup = reinterpret_cast<decltype(mArduinoSetup)>(dlsym(mArduinoProgramHandle, "setup"));
    if (const char* error = dlerror()) throw std::runtime_error(error);

    mArduinoLoop = reinterpret_cast<decltype(mArduinoLoop)>(dlsym(mArduinoProgramHandle, "loop"));
    if (const char* error = dlerror()) throw std::runtime_error(error);
}

void ArduinoProgramManager::unloadProgram()
{
    if (mArduinoProgramHandle) dlclose(mArduinoProgramHandle);
    if (const char* error = dlerror()) throw std::runtime_error(error);

    mArduinoProgramHandle = nullptr;
    mArduinoSetup = nullptr;
    mArduinoLoop = nullptr;
}

#elif _WIN32

#endif

ArduinoProgramManager::~ArduinoProgramManager()
{
    try {
        unloadProgram();
    } catch (std::exception &e) {
        std::cerr << "Arduino program unloading failed: " << e.what() << std::endl;
    }
}
