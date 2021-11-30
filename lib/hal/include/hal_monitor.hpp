#ifndef HAL_MONITOR_H
#define HAL_MONITOR_H

#include "can_data.hpp"
#include "reotype.hpp"
#include "socketcan.hpp"
#include "writecan.hpp"

class HalMonitor{
    private:
        reo_type::Database latest_received_data_;
        void UpdateDataForGearPosition(const CanFrame &frame);
        void UpdateDataForPedalPosition(const CanFrame &frame);
        void UpdateDataForStartButton(const CanFrame &frame);
        void UpdateDataForDriveMode(const CanFrame &frame);
        SocketCan socket_can_;
        const char canName[6] = "vcan0";
    public:
        HalMonitor();
        bool ReadFromCan();  //returns true if new frame is read from CAN.
        void GetCanData(reo_type::Database &data);
        bool WriteCanFrameEmulator(reo_type::Database &db, const int &msdelay);
};
#endif
