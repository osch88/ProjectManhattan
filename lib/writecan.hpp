#ifndef WRITE_CAN_H
#define WRITE_CAN_H

#include "socketcan.hpp"
#include "can_data.hpp"
#include "../app/inputhandler/include/database.hpp"

/*class CanWriter{
    private:
        database_type::Database data_to_write_; // includes the latest data to write to CAN

    public:
        //void GetDataToWrite(database_type::Database &data);
        //CanFrame ConvertToCanFrame(database_type::Database &data);
        CanFrame ConvertIgnitionToCanFrame(database_type::Database &data_to_write);
        CanFrame ConvertGearToCanFrame(database_type::Database &data_to_write);
        CanFrame ConvertGasToCanFrame(database_type::Database &data_to_write);
        bool WriteCanFrame(SocketCan &socket, database_type::Database &db);
        CanWriter();

};*/

//namespace can_writer {
    CanFrame ConvertIgnitionToCanFrame(database_type::Database &data_to_write);
    CanFrame ConvertGearToCanFrame(database_type::Database &data_to_write);
    CanFrame ConvertGasToCanFrame(database_type::Database &data_to_write);
    bool WriteCanFrameUserInput(SocketCan &socket, database_type::Database &db, const int &msdelay);
    bool WriteCanFrameEmulator(SocketCan &socket, database_type::Database &db);

//}

#endif


