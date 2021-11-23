#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "mainloop.hpp"

void MainLoop::hal() {
    while(true) {
        if (hal_monitor.ReadFromCan(socket_can)) {
            std::unique_lock<std::shared_timed_mutex> lock(mutex_);
            hal_monitor.GetCanData(data);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(5));
    }
};

void MainLoop::emulator() {
    while (true) {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        engine.set_inpVal(data);
        engine.print();
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
};

void MainLoop::canSend() {
    while (true)
    {
        std::cout << "Doing something..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}

void MainLoop::run() {
    if (socket_can.Open(canName) == kStatusOk) {
        std::thread t1_(&MainLoop::hal, this);
        std::thread t2_(&MainLoop::emulator, this);
        // std::thread t3_(&MainLoop::canSend, this);
        while (true);
        // std::cout << "Working!" << std::endl;
    } else {
        std::cout << "No socket available" << std::endl;
    }
};
