#ifndef HAL_MONITOR_H
#define HAL_MONITOR_H

#include "can_data.hpp"
#include "../app/inputhandler/include/database.hpp"
#include "socketcan.hpp"

class HalMonitor{
    private:
        database_type::Database latest_received_data_;
        void UpdateDataForGearPosition(const CanFrame &frame);
        void UpdateDataForPedalPosition(const CanFrame &frame);
        void UpdateDataForStartButton(const CanFrame &frame);
        void UpdateDataForDriveMode(const CanFrame &frame);
    public:
        HalMonitor();
        bool ReadFromCan(SocketCan &socket_can);  //returns true if new frame is read from CAN.
        void GetCanData(database_type::Database &data);
        //void WriteEmulatorDataToCan(const SocketCan &socket_can, const database_type::Database &message) const;
};

#endif