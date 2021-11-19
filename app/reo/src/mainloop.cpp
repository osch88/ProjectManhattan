#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "../include/mainloop.hpp"

// CONST
const char canName[] = "vcan0";
// INIT
database_type::Database data;
HalMonitor hal_monitor;
Engine engine;
SocketCan socket_can;

void MainLoop::run() {
    if (socket_can.Open(canName) == kStatusOk) {
        while (true) {
            if (hal_monitor.ReadFromCan(socket_can)) {
                hal_monitor.GetCanData(data);
                engine.set_inpVal(data);
                engine.print();
                std::this_thread::sleep_for(std::chrono::microseconds(500));
            }
        }
    } else {
        std::cout << ("Cannot open can socket!") << std::endl;
    }
}
