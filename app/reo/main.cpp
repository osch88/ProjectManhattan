#include <iostream>
#include <chrono>
#include <thread>
#include "../../lib/socketcan.hpp"
#include "../../lib/hal_monitor.hpp"
#include "./include/engine.hpp"

bool Run(SocketCan &socket_can, Engine &engine){
    bool return_value = false;
    bool new_can_data = false;
    database_type::Database data;
    HalMonitor hal_monitor;
    new_can_data = hal_monitor.ReadFromCan(socket_can);
    if (new_can_data == true) {
        hal_monitor.GetCanData(data);
        //data.gas=50;
        engine.set_inpVal(data);
        //engine.print();
        std::cout << data.gas << std::endl;
        exit(1);
    }
    return_value = true;
    //engine.set_inpVal(*inp);
    
    
    return return_value;
}

int main(int argc, char **argv) {

    
    //InputData_t *inp;
    Engine engine;
    SocketCan socket_can;
    auto result = socket_can.Open("vcan0");
    if(result == kStatusOk) {
        while (Run(socket_can, engine)) {
            /* 1st thread, here -> CAN Parser */
            // CAN_reader(*inp);
            //inp->engineOn = true;
            //inp->gasPedal = 30;
            /* 2nd thread, here -> EMULATOR */
            // Show output
            // CAN_out(OutputData);
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
    } else {
        printf("Cannot open can socket!");
    }

    return 0;
}

