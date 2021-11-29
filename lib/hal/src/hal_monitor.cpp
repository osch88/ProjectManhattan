#include "hal_monitor.hpp"
#include <iostream>

HalMonitor::HalMonitor() {
    latest_received_data_.drive_mode = reo_type::DriveMode::kEco;
    latest_received_data_.gas = 0;
    latest_received_data_.gear = reo_type::Gear::kPark;
    latest_received_data_.ignition = reo_type::Ignition::kStop;
}

bool HalMonitor::ReadFromCan(SocketCan &socket_can) {
    bool return_value = true;
    CanFrame frame;
    if (socket_can.ReadFromCan(frame) == SocketCanStatus::kStatusOk) {
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