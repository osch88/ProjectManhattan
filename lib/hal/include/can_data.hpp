#ifndef CAN_DATA_H
#define CAN_DATA_H

#include <cstdint>
#include <unordered_map>


namespace can_data_base{

    struct GearPosition{
        uint32_t frame_id = 3;
        uint8_t length = 1;
        uint8_t position = 0;
        /* Data interpretation: 
         * 0 = Park
         * 1 = Reverse
         * 2 = Drive
         * 3 = Neutral
        */
    };

    struct PedalPosition{
        uint32_t frame_id = 2;
        uint8_t length = 1;
        uint8_t position = 0;
    };

    struct StartButton{
        uint32_t frame_id = 1;
        uint8_t length = 1;
        uint8_t position = 0;
        /* Data interpretation: 
         * 0 = Stop
         * 1 = Start
        */
    };

    struct DriveMode{
        uint32_t frame_id = 1;
        uint8_t length = 1;
        uint8_t position = 1;
        /* Data interpretation: 
         * 0 = Eco
         * 1 = Sport
        */
    };

    struct Speed{
        uint32_t frame_id = 4;
        uint8_t length = 1;
        uint8_t position = 2;
        /* Data interpretation: 
         * 1 : 1 conversion
        */
    };

    struct Rpm{
        uint32_t frame_id = 4;
        uint16_t length = 2;
        uint8_t position = 0;
        /* Data interpretation: 
         * 1 : 1 conversion
        */
    };

    enum class SignalInfo {
        kGearSignal,
        kStartButtonSignal,
        kDriveModeSignal,
        kGasPedalSignal,
        kRpm,
        kSpeed
    };
    struct FrameInfo {
        uint32_t frame_id;
        uint16_t length;
        uint8_t position;
    };
    namespace config{
        std::unordered_map<can_data_base::SignalInfo, can_data_base::FrameInfo> vcan0 = {
                                                                //id    //length    //position
            {can_data_base::SignalInfo::kStartButtonSignal,     { 1,     2,          0}},
            {can_data_base::SignalInfo::kDriveModeSignal,       { 1,     2,          1}},
            {can_data_base::SignalInfo::kGasPedalSignal,        { 2,     1,          0}},
            {can_data_base::SignalInfo::kGearSignal,            { 3,     1,          0}}
        };
        std::unordered_map<can_data_base::SignalInfo, can_data_base::FrameInfo> vcan1 = {
                                                                //id    //length    //position
            {can_data_base::SignalInfo::kRpm,                   { 1,     2,          0}},
            {can_data_base::SignalInfo::kSpeed,                 { 1,     2,          1}}
        };
    }
}

#endif