#include <iostream>
#include "server.hpp"
#include "writecan.hpp"
#include <iostream>

Server::Server() {
    data_.drivemode = database_type::DriveMode::kEco;
    data_.gas = 0;
    data_.gear = database_type::Gear::kPark;
    data_.ignition = database_type::Ignition::kStop;
    data_.indicator_request = database_type::Indicator::kOff;
    data_.indicator_status = database_type::Indicator::kOff;
}

void Server::Run() {
    if (socket_can_.Open(CAN_NAME) == kStatusOk){
        std::thread t1_(&Server::KeyBoard, this);
        CanWriter();
    } else {
        std::cout << "Cannot open can socket!" << std::endl;
    }
}

void Server::KeyBoard() {
    database_type::Database temp_data;
    temp_data.drivemode = database_type::DriveMode::kEco;
    temp_data.gas = 0;
    temp_data.gear = database_type::Gear::kPark;
    temp_data.ignition = database_type::Ignition::kStop;
    temp_data.indicator_request = database_type::Indicator::kOff;
    temp_data.indicator_status = database_type::Indicator::kOff;
    while (true){
        key_board_.keyReader(temp_data);
        {
            std::unique_lock<std::shared_timed_mutex> lock(mutex_);
            data_ = temp_data;
        }
    }
}
        
void Server::CanWriter() {
    database_type::Indicator indicator_status = database_type::Indicator::kOff;
    while (true){
        bool write_result = true;
        {
            std::shared_lock<std::shared_timed_mutex> lock(mutex_);
            turn_indicator_.UpdateIndicator(data_);
            indicator_status = turn_indicator_.GetIndicatorStatus();
            data_.indicator_status = indicator_status;
            write_result = WriteUserInputToCan(socket_can_, data_, DELAY_BETWEEN_FRAMES_);
        }
        if(write_result == false) {
            std::cout << "error writing to CAN" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
Server::~Server(){
    t1_.join();
}