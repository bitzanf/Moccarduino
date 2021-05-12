#include "simulation_funshield.hpp"
#include "simulation.hpp"
#include "emulator.hpp"
#include "led_display.hpp"
#include "helpers.hpp"

#include <iostream>

// a declaration of a method from interface that will give us the emulator instance
ArduinoEmulator& get_arduino_emulator_instance();

using display_state_t = FunshieldSimulationController::seg_display_t::state_t;

bool checkEventTime(const TimeSeries<display_state_t>& events, std::size_t idx, logtime_t expectedTime, logtime_t tolerance = 200000)
{
    if (!almostEquals(events[idx].time, expectedTime, tolerance)) {
        std::cerr << "Event #" << idx << " was expected at " << expectedTime / 1000000 << "s, but it occured at " << events[idx].time / 1000000 << "s" << std::endl;
        return false;
    }
    return true;
}

bool checkEventValue(const TimeSeries<display_state_t>& events, std::size_t idx, const std::string& expectedContent)
{
    Led7SegInterpreter<4> interpreter(events[idx].value);
    auto content = interpreter.getText();
    if (content != expectedContent) {
        std::cerr << "Event #" << idx << " reported display change to '" << content << "'s, but '" << expectedContent << "' content was expected" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    // initialize simulation
    ArduinoSimulationController arduino(get_arduino_emulator_instance());
    FunshieldSimulationController funshield(arduino);

    try {
        // prepare testing data
        funshield.buttonClick(0, 100000, 3000000);
        funshield.buttonClick(0, 100000, 4000000);
        funshield.buttonClick(1, 100000, 5000000);
        funshield.buttonClick(1, 100000, 6000000);
        funshield.buttonClick(2, 100000, 7000000);
        logtime_t time = 8000000;

        // assemble the components
        LedsEventsDemultiplexer<32> demuxer(10000);
        LedsEventsAggregator<32> aggregator(50000);
        TimeSeries<display_state_t> events;
        funshield.getSegDisplay().attachSproutConsumer(demuxer);
        demuxer.attachNextConsumer(aggregator);
        aggregator.attachNextConsumer(events);

        arduino.runSetup();

        // simulate the run until all buttons are pressed
        std::cout << "Running the simulation (" << time / 1000000 << "s) ..." << std::endl;
        std::size_t loopCount = 0;
        arduino.runLoopsForPeriod(time, 100, [&](logtime_t)
            {
                ++loopCount;
                return true;
            }
        );

        std::cout << "Total " << loopCount << " loops executed." << std::endl;

        for (std::size_t i = 0; i < events.size(); ++i) {
            //std::cout << events[i].time / 1000 << " " << events[i].value << std::endl;
        }

        // analyze output pin history
        if (events.empty()) {
            std::cerr << "No display changes recorded whatsoever." << std::endl;
            return 1;
        }

        if (events.size() != 5) {
            std::cerr << "Total 3 state changes expected, but " << events.size() << " events reported." << std::endl;
            return 1;
        }

        bool ok = true;
        for (std::size_t i = 0; i < 5; ++i) {
            ok = ok && checkEventTime(events, i, (i + 3) * 1000000);
        }
        ok = ok && checkEventValue(events, 0, "abcd");
        ok = ok && checkEventValue(events, 1, "    ");
        ok = ok && checkEventValue(events, 2, "efgh");
        ok = ok && checkEventValue(events, 3, "    ");
        ok = ok && checkEventValue(events, 4, "ijkl");

        if (!ok) {
            std::cerr << "Test failed!" << std::endl;
            return 1;
        }

        std::cout << "Simulation ended successfully." << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
