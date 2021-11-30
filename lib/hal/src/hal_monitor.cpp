#include "hal_monitor.hpp"
#include <iostream>

HalMonitor::HalMonitor() {
    latest_received_data_.drive_mode = reo_type::DriveMode::kEco;
    latest_received_data_.gas = 0;
    latest_received_data_.gear = reo_type::Gear::kPark;
    latest_received_data_.ignition = reo_type::Ignition::kStop;
    
    if (socket_can_.Open(canName) != kStatusOk) {
        std::cout << "No socket could be open" << std::endl;
        exit -1;
    }
}

bool HalMonitor::ReadFromCan() {
    bool return_value = true;
    CanFrame frame;
    if (socket_can_.ReadFromCan(frame) == SocketCanStatus::kStatusOk) {
        if (frame.id == (can_data_base::start_button.frame_id or can_data_base::drive_mode.frame_id)) {
            UpdateDataForStartButton(frame);
            UpdateDataForDriveMode(frame);
        } else if (frame.id == can_data_base::pedal_position.frame_id) {
            UpdateDataForPedalPosition(frame);
        } else if (frame.id == can_data_base::gear_position.frame_id) {
            UpdateDataForGearPosition(frame);
        }
    } else {
        return_value = false;
    }
    return return_value;
}

void HalMonitor::UpdateDataForGearPosition(const CanFrame &frame) {
    if (frame.data[0] == 0){
        latest_received_data_.gear = reo_type::Gear::kPark;
    } else if (frame.data[0] == 1){
        latest_received_data_.gear = reo_type::Gear::kNeutral;
    } else if (frame.data[0] == 2){
        latest_received_data_.gear = reo_type::Gear::kDrive;
    } else if (frame.data[0] == 3){
        latest_received_data_.gear = reo_type::Gear::kReverse;
    } else {
        std::cout << "invalid data in Gear position can data, not within valid range. " << std::endl;
    }
}

void HalMonitor::UpdateDataForPedalPosition(const CanFrame &frame) {
    if (frame.data[0] >= 0 and frame.data[0] <= 100){
        latest_received_data_.gas = frame.data[0];
    } else {
        std::cout << "invalid data in Pedal Position can data, not within valid range. " << std::endl;
    }
}

void HalMonitor::UpdateDataForStartButton(const CanFrame &frame){
    if (frame.data[0] == 0){
        latest_received_data_.ignition = reo_type::Ignition::kStop;
    } else if (frame.data[0] == 1){
        latest_received_data_.ignition = reo_type::Ignition::kStart;
    } else {
        std::cout << "invalid data in start button can data, not within valid range. " << std::endl;
    }
}

void HalMonitor::UpdateDataForDriveMode(const CanFrame &frame){
    if (frame.data[1] == 0){
        latest_received_data_.drive_mode = reo_type::DriveMode::kEco;
    } else if (frame.data[1] == 0){
        latest_received_data_.drive_mode = reo_type::DriveMode::kSport;
    } else {
        std::cout << "invalid data in Drive Mode can data, not within valid range. " << std::endl;
    }
}

void HalMonitor::GetCanData(reo_type::Database &data) {
    data = latest_received_data_;
}

bool HalMonitor::WriteCanFrameEmulator(reo_type::Database &db, const int &msdelay){
    bool ret = true;
    unsigned int db_rpm = db.rpm;
    CanFrame emulator;
    ConvertToCanFrame(emulator, db_rpm, can_data_base::rpm);

    unsigned int db_speed = db.speed;
    ConvertToCanFrame(emulator, db_speed, can_data_base::speed);

    reo_type::Gear db_gear_pindle = db.gear;
    ConvertToCanFrame(emulator, db_gear_pindle, can_data_base::gear_pindle);

    unsigned int db_gear_number = db.gear_number;
    ConvertToCanFrame(emulator, db_gear_number, can_data_base::gear_number);
    
    auto write_emulator_status = socket_can_.WriteToCan(emulator);
  
    if (write_emulator_status != kStatusOk || write_emulator_status != kStatusOk){
        std::cout << "Something went wrong on socket write"  << std::endl;
        ret = false;
    }
    return ret;
}
