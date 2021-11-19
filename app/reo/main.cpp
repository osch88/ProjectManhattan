#include <iostream>
#include <chrono>
#include <thread>
#include "../../lib/socketcan.hpp"
#include "../../lib/hal_monitor.hpp"
#include "./include/engine.hpp"

bool Run(SocketCan &socket_can, Engine &engine, HalMonitor &hal_monitor){
    bool return_value = false;
    bool new_can_data = false;
    database_type::Database data;
    
    new_can_data = hal_monitor.ReadFromCan(socket_can);
    if (new_can_data == true) {
        hal_monitor.GetCanData(data);
        engine.set_inpVal(data);
        engine.print();
    }
    return_value = true;
    return return_value;
}

int main(int argc, char **argv) {
    Engine engine;
    SocketCan socket_can;
    HalMonitor hal_monitor;
    auto result = socket_can.Open("vcan0");
    if(result == kStatusOk) {
        while (Run(socket_can, engine, hal_monitor)) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
    } else {
        std::cout << ("Cannot open can socket!") << std::endl;
    }
    return 0;
}

