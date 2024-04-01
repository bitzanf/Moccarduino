#ifndef PROGRAM_MANAGER_HPP
#define PROGRAM_MANAGER_HPP

#include <string>
#include <stdexcept>

class ArduinoEmulator;

class ArduinoProgramManager {
private:

    void (*mArduinoSetup)();
    void (*mArduinoLoop)();

    void* mArduinoProgramHandle;

    /**
     * Only really necessary for Windows, as LoadLibrary doesn't perform reverse
     * linking (and as such the emulator's functions can't be linked to the running instance).
     */
    ArduinoEmulator* mEmulator;

public:
    ArduinoProgramManager(ArduinoEmulator* emulator) :
        mArduinoSetup(nullptr),
        mArduinoLoop(nullptr),
        mArduinoProgramHandle(nullptr),
        mEmulator(emulator)
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
