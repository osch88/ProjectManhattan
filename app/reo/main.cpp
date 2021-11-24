<<<<<<< HEAD
#include "mainloop.hpp"

int main(int argc, char **argv) {
    MainLoop loop;
    loop.run();
    return 0;
}
=======
#include <iostream>
#include <chrono>
#include <thread>
#include "socketcan.hpp"
#include "hal_monitor.hpp"
#include "engine.hpp"
#include "writecan.hpp"

bool Run(SocketCan &socket_can, Engine &engine, HalMonitor &hal_monitor, reo_type::Database &data){
    bool return_value = false;
    bool new_can_data = false;
    bool write_status = true;
    int DELAY = 0;
    
    new_can_data = hal_monitor.ReadFromCan(socket_can);
    if (new_can_data == true) {
        hal_monitor.GetCanData(data);
    }
    engine.set_inpVal(data);
    engine.getData(data);
    engine.print();
    write_status = WriteCanFrameEmulator(socket_can, data, DELAY);
    
    return_value = true;
    return return_value;
}   

int main(int argc, char **argv) {
    Engine engine;
    SocketCan socket_can;
    HalMonitor hal_monitor;
    reo_type::Database data;
    auto result = socket_can.Open("vcan0");
    if(result == kStatusOk) {
        while (Run(socket_can, engine, hal_monitor, data)) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
    } else {
        std::cout << ("Cannot open can socket!") << std::endl;
    }
    return 0;
}


>>>>>>> emulator work in progress
