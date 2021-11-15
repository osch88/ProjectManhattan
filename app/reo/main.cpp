#include <iostream>
#include <chrono>
#include <thread>

#include "./include/engine.hpp"

/* To be replaced with correct inputHandler */
struct inputHandler {
    unsigned int gas = 100;
    bool engineOn = true;
}typedef inputHandler_t;

int main(int argc, char **argv) {

    Engine engine;
    inputHandler_t inp;

    while (true) {
        /* 1st thread, Here -> INPUT HANDLER */
        /*  
            S        for start
            Q        for stop
            P        for gear position Park
            N        for gear position Neutral
            D        for gear position Drive
            R        for gear position Reverse
            UP       for gas pedal increase (acceleration)
            DOWN     for gas pedal decrease (deccelration)
            1        for drive mode normal (default if non selected)
            2        for drive mode sport
        */

        /* 2nd thread, Here -> EMULATOR */

        // This will later be replaced with proper input
        engine.set_inputValues( inp.gas, 
                                inp.engineOn);     
        engine.runEngine();                 // Run with the input
        engine.print();                     // Show output

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

    return 0;
}
