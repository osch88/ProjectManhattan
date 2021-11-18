#include "socketcan.hpp"
#include "writecan.hpp"
#include <iostream>
#include <thread>
#include <chrono>

/*CanWriter::CanWriter(){
    data_to_write_.ignition = database_type::Ignition::kStop;
    data_to_write_.gear = database_type::Gear::kPark;
    data_to_write_.gas  = 0;
    data_to_write_.drivemode = database_type::DriveMode::kEco;
} */ // kanske inte behövs

/*void GetDataToWrite(database_type::Database &db){
   database_type::Database data_to_write = db 
}*/


CanFrame ConvertIgnitionToCanFrame(database_type::Database &data_to_write){
    CanFrame ignition;
    can_data_base::StartButton start_button;
    ignition.id = start_button.frame_id;
    ignition.len = start_button.length;
    int ignition_data = static_cast<int>(data_to_write.ignition); // convert enum to int
 
    for (int i = 0; i < ignition.len; ++i){
        ignition.data[i] = ignition_data;
    }
    return ignition;
}

CanFrame ConvertGearToCanFrame(database_type::Database &data_to_write){
    CanFrame gear;
    can_data_base::GearPosition gear_position;
    gear.id = gear_position.frame_id;
    gear.len = gear_position.length;
    int gear_data = static_cast<int>(data_to_write.gear); // convert enum to int

    for (int i = 0; i < gear.len; ++i){
        gear.data[i] = gear_data;
    }
    return gear;
}

CanFrame ConvertGasToCanFrame(database_type::Database &data_to_write){
    CanFrame gas;
    can_data_base::PedalPosition pedal_position;
    gas.id = pedal_position.frame_id;
    gas.len = pedal_position.length;
    int gas_data = static_cast<int>(data_to_write.gas); // convert enum to int

    for (int i = 0; i < gas.len; ++i){
        gas.data[i] = gas_data;
    }
    return gas;
}


/*CanFrame ConvertToCanFrame(database_type::Database &data_to_write, can_data_base::CanData &can_db){
    CanFrame frame;
    //can_data_base::PedalPosition pedal_position;
    frame.id = can_db.frame_id;
    gas.len = pedal_position.length;
    int gas_data = static_cast<int>(data_to_write.gas); // convert enum to int

    for (int i = 0; i < gas.len; ++i){
        gas.data[i] = gas_data;
    }
    return gas;
}*/

bool WriteCanFrameUserInput(SocketCan &socket, database_type::Database &db, const int &msdelay){
    //SocketCan socket_can;
    //if (socket == kStatusOk) Vart ska vi kolla att socket var ok? i main? om inte går vi inte vidare?

    bool ret = true;
    const CanFrame ignition = ConvertIgnitionToCanFrame(db);
    const CanFrame gear = ConvertGearToCanFrame(db);
    const CanFrame gas = ConvertGasToCanFrame(db);
    auto write_ignition_status = socket.WriteToCan(ignition);
    std::this_thread::sleep_for(std::chrono::milliseconds(msdelay)); //delay for frame
    auto write_gear_status = socket.WriteToCan(gear);
    std::this_thread::sleep_for(std::chrono::milliseconds(msdelay)); //delay for frame
    auto write_gas_status = socket.WriteToCan(gas);
    if (write_ignition_status != kStatusOk){ //kolla alla samtidigt och return false om någon misslyckas?
        printf("something went wrong on socket write for ignition, error code : %d \n", int32_t(write_ignition_status));
        ret = false;
    }
    else if(write_gear_status != kStatusOk){
        printf("something went wrong on socket write for gear, error code : %d \n", int32_t(write_gear_status));
        ret = false;
    }
    else if(write_gas_status != kStatusOk){
        printf("something went wrong on socket write for gas, error code : %d \n", int32_t(write_gas_status));
        ret = false;
    }
    else{
        printf("Message was written to the socket for all frames \n");
    }
    return ret; 
}
