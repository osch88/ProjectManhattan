#ifndef HAL_MONITOR_H
#define HAL_MONITOR_H

#include "can_data.hpp"
#include "reotype.hpp"
#include "socketcan.hpp"

class HalMonitor{
    private:
        reo_type::Database latest_received_data_;
        void UpdateDataForGearPosition(const CanFrame &frame);
        void UpdateDataForPedalPosition(const CanFrame &frame);
        void UpdateDataForStartButton(const CanFrame &frame);
        void UpdateDataForDriveMode(const CanFrame &frame);
    public:
        HalMonitor();
        bool ReadFromCan(SocketCan &socket_can);  //returns true if new frame is read from CAN.
        void GetCanData(reo_type::Database &data);
};
#endif