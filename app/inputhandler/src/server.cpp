#include <iostream>
#include "server.hpp"
#include "writecan.hpp"

Server::Server() {
    data_.drivemode = database_type::DriveMode::kEco;
    data_.gas = 0;
    data_.gear = database_type::Gear::kPark;
    data_.ignition = database_type::Ignition::kStop;
}

void Server::Run() {
    if (socket_can_.Open(CAN_NAME) == kStatusOk){
        std::thread t1_(&Server::KeyBoard, this);
        std::thread t2_(&Server::CanWriter, this);
        while (true){
            //std::cout << "Main thread halted here!" << std::endl;
        }
    } else {
        std::cout << "Cannot open can socket!" << std::endl;
    }
}

void Server::KeyBoard() {
    while (true){
        database_type::Database temp_data;
        key_board_.keyReader(temp_data);
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        data_ = temp_data;
    }
}
        
void Server::CanWriter() {
    while (true){
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        bool write_result = WriteUserInputToCan(socket_can_, data_, DELAY_BETWEEN_FRAMES_);
        if(write_result == false) {
            std::cout << "error writing to CAN" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}