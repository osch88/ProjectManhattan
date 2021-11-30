#ifndef WRITE_CAN_H
#define WRITE_CAN_H

#include "socketcan.hpp"
#include "can_data.hpp"

template <typename T1, typename T2>
void ConvertToCanFrame(CanFrame &frame, const T1 &data_to_write, const T2 &can_db){
    frame.id = can_db.frame_id;
    frame.len = can_db.frame_length;
    int frame_data = static_cast<int>(data_to_write);
    for (int i = can_db.position; i < (can_db.position + can_db.data_length) ; ++i){
        frame.data[i] = (frame_data >> (i-can_db.position)*8) & (255);
    }
}
#endif
