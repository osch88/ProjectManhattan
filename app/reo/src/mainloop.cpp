#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <shared_mutex>
#include "mainloop.hpp"
#include "writecan.hpp"

void MainLoop::hal() {
    while(true) {
        if (hal_monitor_.ReadFromCan()) {
            std::unique_lock<std::shared_mutex> lock(this->mtx);
            hal_monitor_.GetCanData(data_);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(5));
    }
};

void MainLoop::emulator() {
    while (true) {
        {
            std::shared_lock<std::shared_mutex> lock(this->mtx);
            engine.set_inpVal(data_);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
};

void MainLoop::canSend() {
    bool write_status = true;
    int DELAY = 0;
    while (true) {
        {
            std::unique_lock<std::shared_mutex> lock(this->mtx);
            engine.getData(data_);
        }
        {
            std::shared_lock<std::shared_mutex> lock(this->mtx);
            write_status = hal_monitor_.WriteCanFrameEmulator(data_, DELAY);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}

void MainLoop::run() {
    std::thread t1_(&MainLoop::hal, this);
    std::thread t2_(&MainLoop::emulator, this);
    canSend();
};
