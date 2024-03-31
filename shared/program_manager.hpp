#ifndef PROGRAM_MANAGER_HPP
#define PROGRAM_MANAGER_HPP

#include <string>
#include <stdexcept>

#ifdef __linux__
    using LibraryHandle = void*;
#elif _WIN32
    using LibraryHandle = HMODULE;
#else
    #error "Unsupported OS platform!"
#endif

class ArduinoProgramManager {
private:

    void (*mArduinoSetup)();
    void (*mArduinoLoop)();

    LibraryHandle mArduinoProgramHandle;

public:
    ArduinoProgramManager() :
        mArduinoSetup(nullptr),
        mArduinoLoop(nullptr),
        mArduinoProgramHandle(nullptr)
    {}

    ~ArduinoProgramManager();

    /**
     * Loads the arduino program, links any missing symbols (functions from interface.hpp) against
     * our running program and loads the loop and setup symbols. Also automatically performs
     * static and global object initialization (the emulator is fully up and running at this point,
     * so no crash).
     * @param fileName full name of the compiled program that is to be tested
     */
    void loadProgram(const std::string &fileName);

    /**
     * Unloads the tested program and automatically deinitializes its global objects.
     */
    void unloadProgram();

    void runSetup()
    {
        if (mArduinoProgramHandle == nullptr) throw std::runtime_error("The arduino program is not loaded yet!");
        mArduinoSetup();
    }

    void runLoop()
    {
        if (mArduinoProgramHandle == nullptr) throw std::runtime_error("The arduino program is not loaded yet!");
        mArduinoLoop();
    }
};



#endif //PROGRAM_MANAGER_HPP
