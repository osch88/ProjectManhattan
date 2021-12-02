#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <shared_mutex>
#include "mainloop.hpp"
#include "writecan.hpp"

//dödsbud, timer på motagna meddelanden

void MainLoop::hal() {
    while(this->isRunning_) {
        if (hal_monitor_.ReadFromCan()) {
            std::unique_lock<std::shared_mutex> lock(this->mtx_);
            hal_monitor_.GetCanData(data_);
            this->deathCounter_ = 0;
        }
        else if (this->deathCounter_ > 100) {
            this->isRunning_.exchange(false);
        }
        
        this->deathCounter_++;
        
        std::this_thread::sleep_for(std::chrono::microseconds(5));
    }
}

void MainLoop::emulator() {
    while (this->isRunning_) {
        {
            std::unique_lock<std::shared_mutex> lock(this->mtx_);
            engine.set_inpVal(data_);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}

void MainLoop::canSend() {
    int DELAY = 0;
    while (this->isRunning_) {
        {
            std::unique_lock<std::shared_mutex> lock(this->mtx_);
            engine.getData(data_);
        }
        {
            std::shared_lock<std::shared_mutex> lock(this->mtx_);
            hal_monitor_.WriteCanFrameEmulator(data_, DELAY);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}

void MainLoop::run() {
    std::thread t1_(&MainLoop::hal, this);
    std::thread t2_(&MainLoop::emulator, this);
    canSend();
    t1_.join();
    t2_.join();
}
