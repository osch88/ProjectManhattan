#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "mainloop.hpp"
#include "writecan.hpp"

void MainLoop::hal() {
    while(true) {
        if (hal_monitor_.ReadFromCan(socket_can_)) {
            std::unique_lock<std::shared_timed_mutex> lock(mutex_);
            hal_monitor_.GetCanData(data_);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(5));
    }
};

void MainLoop::emulator() {
    while (true) {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        engine.set_inpVal(data_);
        engine.print();
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
};

void MainLoop::canSend() {
    bool write_status = true;
    int DELAY = 0;
    while (true)
    {
        {
            std::unique_lock<std::shared_timed_mutex> lock(mutex_);
            engine.getData(data_);
        }
        {
            std::shared_lock<std::shared_timed_mutex> lock(mutex_);
            write_status = WriteCanFrameEmulator(socket_can_, data_, DELAY);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
}

void MainLoop::run() {
    if (socket_can_.Open(canName) == kStatusOk) {
        std::thread t1_(&MainLoop::hal, this);
        std::thread t2_(&MainLoop::emulator, this);
        std::thread t3_(&MainLoop::canSend, this);
        while (true);
        // std::cout << "Working!" << std::endl;
    } else {
        std::cout << "No socket available" << std::endl;
    }
};
