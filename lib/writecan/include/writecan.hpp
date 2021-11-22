#ifndef WRITE_CAN_H
#define WRITE_CAN_H

#include "socketcan.hpp"
#include "can_data.hpp"
#include "database.hpp"

template <typename T1, typename T2>
CanFrame ConvertToCanFrame(T1 &data_to_write, T2 &can_db){
    CanFrame frame;
    frame.id = can_db.frame_id;
    frame.len = can_db.length;
    int frame_data = static_cast<int>(data_to_write); // convert enum to int

    for (int i = 0; i < frame.len; ++i){
        frame.data[i] = frame_data;
    }
    return frame;
}

bool WriteUserInputToCan(SocketCan &socket, database_type::Database &db, const int &msdelay);
bool WriteCanFrameEmulator(SocketCan &socket, database_type::Database &db, const int &msdelay);


#endif


