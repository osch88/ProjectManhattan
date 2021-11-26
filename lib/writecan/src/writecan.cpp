#include "socketcan.hpp"
#include "writecan.hpp"
#include <iostream>
#include <thread>
#include <chrono>


bool WriteUserInputToCan(SocketCan &socket, database_type::Database &db, const int &msdelay){
    bool ret = true;

    can_data_base::StartButton cb_ignition; 
    database_type::Ignition db_ignition = db.ignition; 
    CanFrame ignition_drivemode;
    ConvertToCanFrame(ignition_drivemode, db_ignition, cb_ignition);

    can_data_base::DriveMode cb_drivemode; 
    database_type::DriveMode db_drivemode = db.drivemode; 
    ConvertToCanFrame(ignition_drivemode, db_drivemode, cb_drivemode);

    can_data_base::GearPosition cb_gear; 
    database_type::Gear db_gear = db.gear; 
    CanFrame gear; 
    ConvertToCanFrame(gear, db_gear, cb_gear);

    can_data_base::PedalPosition cb_gas; 
    unsigned int db_gas = db.gas; 
    CanFrame gas;
    ConvertToCanFrame(gas, db_gas, cb_gas);                                                                                                                                             

    auto write_ignition_status = socket.WriteToCan(ignition_drivemode);
    std::this_thread::sleep_for(std::chrono::milliseconds(msdelay));
    auto write_gear_status = socket.WriteToCan(gear);
    std::this_thread::sleep_for(std::chrono::milliseconds(msdelay));
    auto write_gas_status = socket.WriteToCan(gas);
    
    if (write_ignition_status != kStatusOk){
        std::cout << "Something went wrong on socket write for ignition, error code: "<< write_ignition_status << std::endl;
        ret = false;
    }
    else if(write_gear_status != kStatusOk){
        std::cout << "Something went wrong on socket write for gear, error code : " << write_gear_status << std::endl;
        ret = false;
    }
    else if(write_gas_status != kStatusOk){
        std::cout << "Something went wrong on socket write for gas, error code : " << write_gas_status  << std::endl;
        ret = false;
    }
    return ret; 
}

bool WriteCanFrameEmulator(SocketCan &socket, reo_type::Database &db, const int &msdelay){
    bool ret = true;

    can_data_base::Rpm cb_rpm;
    unsigned int db_rpm = db.rpm;
    CanFrame emulator;
    ConvertToCanFrame(emulator, db_rpm, cb_rpm);

    can_data_base::Speed cb_speed;
    unsigned int db_speed = db.speed;
    ConvertToCanFrame(emulator, db_speed, cb_speed);

    can_data_base::GearPindle cb_gear_pindle;
    reo_type::Gear db_gear_pindle = db.gear;
    ConvertToCanFrame(emulator, db_gear_pindle, cb_gear_pindle);

    can_data_base::GearNumber cb_gear_number;
    unsigned int db_gear_number = db.gear_number;
    ConvertToCanFrame(emulator, db_gear_number, cb_gear_number);
    
    auto write_emulator_status = socket.WriteToCan(emulator);
  
    if (write_emulator_status != kStatusOk || write_emulator_status != kStatusOk){
        std::cout << "Something went wrong on socket write"  << std::endl;
        ret = false;
    }
    return ret;
}

