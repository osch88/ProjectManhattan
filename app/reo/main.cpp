#include <iostream>
#include <chrono>
#include <thread>

#include "./include/engine.hpp"

int main(int argc, char **argv) {

    Engine engine;
    InputData_t *inp;

    while (true) {
        /* 1st thread, here -> CAN Parser */
        // CAN_reader(*inp);
        inp->engineOn = true;
        inp->gasPedal = 30;
    
        /* 2nd thread, here -> EMULATOR */
        engine.set_inpVal(*inp);

        // Show output
        // CAN_out(OutputData);
        engine.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

    return 0;
}
