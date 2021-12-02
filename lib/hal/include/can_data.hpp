#ifndef CAN_DATA_H
#define CAN_DATA_H

#include <cstdint>

namespace can_data_base{

    struct GearPosition{
        const uint32_t frame_id = 3;
        const uint8_t frame_length = 1;
        const uint8_t data_length = 1;
        const uint8_t position = 0;
        /* Data interpretation: 
         * 0 = Park
         * 1 = Neutral
         * 2 = Drive
         * 3 = Reverse
        */
    };
    constexpr struct GearPosition gear_position;

    struct PedalPosition{
        const uint32_t frame_id = 2;
        const uint8_t frame_length = 1;
        const uint8_t data_length = 1;
        const uint8_t position = 0;
        /* Data interpretation: 
         * 1 : 1 conversion
        */
    };
    constexpr struct PedalPosition pedal_position;

    struct StartButton{
        const uint32_t frame_id = 1;
        const uint8_t frame_length = 6;
        const uint8_t data_length = 1;
        const uint8_t position = 0;
        /* Data interpretation: 
         * 0 = Stop
         * 1 = Start
        */
    };
    constexpr struct StartButton start_button;

    struct DriveMode{
        const uint32_t frame_id = 1;
        const uint8_t frame_length = 6;
        const uint8_t data_length = 1;
        const uint8_t position = 1;
        /* Data interpretation: 
         * 0 = Eco
         * 1 = Sport
        */
    };
    constexpr struct DriveMode drive_mode;
    struct Speed{
        const uint32_t frame_id = 4;
        const uint8_t frame_length = 8;
        const uint8_t data_length = 1;
        const uint8_t position = 2;
        /* Data interpretation: 
         * 1 : 1 conversion
        */
    };
    constexpr struct Speed speed;

    struct Rpm{
        const uint32_t frame_id = 4;
        const uint8_t frame_length = 8;
        const uint8_t data_length = 2;
        const uint8_t position = 0;
        /* Data interpretation: 
         * 1 : 1 conversion
        */
    };
    constexpr struct Rpm rpm;

     struct GearPindle{
        const uint32_t frame_id = 4;
        const uint8_t frame_length = 8;
        const uint8_t data_length = 1;
        const uint8_t position = 3;
    };
    constexpr struct GearPindle gear_pindle;

    struct GearNumber{
        const uint32_t frame_id = 4;
        const uint8_t frame_length = 8;
        const uint8_t data_length = 1;
        const uint8_t position = 4;
    };
    constexpr struct GearNumber gear_number;

    struct Fuel{
        const uint32_t frame_id = 4;
        const uint8_t frame_length = 8;
        const uint8_t data_length = 1;
        const uint8_t position = 5;
    };
    constexpr struct Fuel fuel;

    struct OilTemp{
        const uint32_t frame_id = 4;
        const uint8_t frame_length = 8;
        const uint8_t data_length = 1;
        const uint8_t position = 6;
    };
    constexpr struct OilTemp oil_temp;

    struct CoolTemp{
        const uint32_t frame_id = 4;
        const uint8_t frame_length = 8;
        const uint8_t data_length = 1;
        const uint8_t position = 7;
    };
    constexpr struct CoolTemp cool_temp;

    struct TurnIndicator{
        const uint32_t frame_id = 1;
        const uint8_t frame_length = 6;
        const uint8_t data_length = 1;
        const uint8_t position = 2;
        /* Data interpretation: 
         * 0 = Off
         * 1 = Left
         * 2 = Right
         * 3 = Both Left and Right
        */
    };
    constexpr struct TurnIndicator turn_indicator;

    struct SeatBelt{
        const uint32_t frame_id = 1;
        const uint8_t frame_length = 6;
        const uint8_t data_length = 1;
        const uint8_t position = 3;
        /* Data interpretation: 
         * 0 = SeatBeltNotApplied
         * 1 = SeatBeltApplied
        */
    };
    constexpr struct SeatBelt seat_belt;

    struct HighBeam{
        const uint32_t frame_id = 1;
        const uint8_t frame_length = 6;
        const uint8_t data_length = 1;
        const uint8_t position = 4;
        /* Data interpretation: 
         * 0 = HighBeamOff
         * 1 = HighBeamOn
        */
    };
    constexpr struct HighBeam high_beam;

    struct Brake{
        const uint32_t frame_id = 1;
        const uint8_t frame_length = 6;
        const uint8_t data_length = 1;
        const uint8_t position = 5;
        /* Data interpretation: 
         * 0 = BrakeNotApplied
         * 1 = BrakeApplied
        */
    };
    constexpr struct Brake brake;

    struct EngineStatus{
        const uint32_t frame_id = 5;
        const uint8_t frame_length = 2;
        const uint8_t data_length = 1;
        const uint8_t position = 0;
    };
    constexpr struct EngineStatus engine_status;

    struct DriveModeStatus{
        const uint32_t frame_id = 5;
        const uint8_t frame_length = 2;
        const uint8_t data_length = 1;
        const uint8_t position = 1;
    };
    constexpr struct DriveModeStatus drive_mode_status;    
}

#endif
