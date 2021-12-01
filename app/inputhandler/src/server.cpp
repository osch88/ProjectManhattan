#include <iostream>
#include "server.hpp"

Server::Server() {
    data_.drivemode = database_type::DriveMode::kEco;
    data_.gas = 0;
    data_.gear = database_type::Gear::kPark;
    data_.ignition = database_type::Ignition::kStop;
    data_.indicator_request = database_type::Indicator::kOff;
    data_.indicator_status = database_type::Indicator::kOff;
    data_.seat_belt = database_type::SeatBelt::kNotApplied;
    data_.high_beam = database_type::HighBeam::kHighBeamOff;
    data_.brake = database_type::Brake::kHandBrakeOff;
}

int Server::Run() {
    int return_value = 0;
    if (socket_can_.Open(CAN_NAME) == SocketCanStatus::kStatusOk){
        t1_ = std::thread(&Server::RunKeyBoard, this);
        RunIndicatorAndCAN();
        t1_.join();
    } else {
        std::cout << "Cannot open can socket!" << std::endl;
        return_value = 1;
    }
    return return_value;
}

void Server::RunKeyBoard() {
    database_type::Database temp_data;
    temp_data.drivemode = database_type::DriveMode::kEco;
    temp_data.gas = 0;
    temp_data.gear = database_type::Gear::kPark;
    temp_data.ignition = database_type::Ignition::kStop;
    temp_data.indicator_request = database_type::Indicator::kOff;
    temp_data.indicator_status = database_type::Indicator::kOff;
    temp_data.seat_belt = database_type::SeatBelt::kNotApplied;
    temp_data.high_beam = database_type::HighBeam::kHighBeamOff;
    temp_data.brake = database_type::Brake::kHandBrakeOff;
    while (key_board_.running){
        key_board_.keyReader(temp_data);
        {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            data_ = temp_data;
        }
    }
}
        
void Server::RunIndicatorAndCAN() {
    database_type::Indicator indicator_status = database_type::Indicator::kOff;
    while (key_board_.running){
        bool write_result = true;
        {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            turn_indicator_.UpdateIndicator(data_);
            indicator_status = turn_indicator_.GetIndicatorStatus();
            data_.indicator_status = indicator_status;
            write_result = WriteUserInputToCan(data_, DELAY_BETWEEN_FRAMES_);
        }
        if(write_result == false) {
            std::cout << "error writing to CAN" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
}

bool Server::WriteUserInputToCan(database_type::Database &db, const int &msdelay){
    bool ret = true;

    database_type::Ignition db_ignition = db.ignition; 
    CanFrame ignition_drivemode_indicator;
    ConvertToCanFrame(ignition_drivemode_indicator, db_ignition, can_data_base::start_button);

    database_type::DriveMode db_drivemode = db.drivemode; 
    ConvertToCanFrame(ignition_drivemode_indicator, db_drivemode, can_data_base::drive_mode);

    database_type::Indicator db_indicator = db.indicator_status; 
    ConvertToCanFrame(ignition_drivemode_indicator, db_indicator, can_data_base::turn_indicator);

    database_type::SeatBelt db_seat_belt = db.seat_belt; 
    ConvertToCanFrame(ignition_drivemode_indicator, db_seat_belt, can_data_base::seat_belt);

    database_type::HighBeam db_high_beam = db.high_beam; 
    ConvertToCanFrame(ignition_drivemode_indicator, db_high_beam, can_data_base::high_beam);

    database_type::Brake db_brake = db.brake; 
    ConvertToCanFrame(ignition_drivemode_indicator, db_brake, can_data_base::brake);

    database_type::Gear db_gear = db.gear; 
    CanFrame gear; 
    ConvertToCanFrame(gear, db_gear, can_data_base::gear_position);

    unsigned int db_gas = db.gas; 
    CanFrame gas;
    ConvertToCanFrame(gas, db_gas, can_data_base::pedal_position);

    auto write_ignition_status = socket_can_.WriteToCan(ignition_drivemode_indicator);
    std::this_thread::sleep_for(std::chrono::milliseconds(msdelay));
    auto write_gear_status = socket_can_.WriteToCan(gear);
    std::this_thread::sleep_for(std::chrono::milliseconds(msdelay));
    auto write_gas_status = socket_can_.WriteToCan(gas);
    
    if (write_ignition_status != SocketCanStatus::kStatusOk){
        std::cout << "Something went wrong on socket write for ignition, error code: "<< static_cast<int>(write_ignition_status) << std::endl;
        ret = false;
    }
    else if(write_gear_status != SocketCanStatus::kStatusOk){
        std::cout << "Something went wrong on socket write for gear, error code : " << static_cast<int>(write_gear_status) << std::endl;
        ret = false;
    }
    else if(write_gas_status != SocketCanStatus::kStatusOk){
        std::cout << "Something went wrong on socket write for gas, error code : " << static_cast<int>(write_gas_status)  << std::endl;
        ret = false;
    }
    return ret; 
}

Server::~Server(){
}
