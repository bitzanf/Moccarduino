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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <system_error>

void ArduinoProgramManager::loadProgram(const std::string& fileName)
{
    if (mArduinoProgramHandle) throw std::runtime_error("The Arduino program is already loaded!");

    mArduinoProgramHandle = LoadLibraryA(fileName.c_str());
    if (!mArduinoProgramHandle) throw std::system_error(GetLastError(), std::system_category(), "Error opening Arduino program!");

    mArduinoSetup = reinterpret_cast<decltype(mArduinoSetup)>(GetProcAddress((HMODULE)mArduinoProgramHandle, "setup"));
    if (!mArduinoSetup) throw std::system_error(GetLastError(), std::system_category(), "setup");

    mArduinoLoop = reinterpret_cast<decltype(mArduinoLoop)>(GetProcAddress((HMODULE)mArduinoProgramHandle, "loop"));
    if (!mArduinoLoop) throw std::system_error(GetLastError(), std::system_category(), "loop");

    void (*set_arduino_emulator_instance)(ArduinoEmulator*);
    set_arduino_emulator_instance = reinterpret_cast<decltype(set_arduino_emulator_instance)>(GetProcAddress((HMODULE)mArduinoProgramHandle, "set_arduino_emulator_instance"));
    if (!set_arduino_emulator_instance) throw std::system_error(GetLastError(), std::system_category(), "set_arduino_emulator_instance");
    set_arduino_emulator_instance(mEmulator);
}

void ArduinoProgramManager::unloadProgram() {
    if (mArduinoProgramHandle)
    {
        if (FreeLibrary((HMODULE)mArduinoProgramHandle) == 0) throw std::system_error(GetLastError(), std::system_category());
    }

    mArduinoProgramHandle = nullptr;
    mArduinoSetup = nullptr;
    mArduinoLoop = nullptr;
}

#endif

ArduinoProgramManager::~ArduinoProgramManager()
{
    try {
        unloadProgram();
    } catch (std::exception &e) {
        std::cerr << "Arduino program unloading failed: " << e.what() << std::endl;
    }
}
