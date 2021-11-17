#ifndef CAN_DATA_H
#define CAN_DATA_H

#include <cstdint>


namespace can_data_base{

    struct GearPosition{
        uint32_t frame_id = 3;
        uint8_t length = 1;
        uint8_t position = 0;
        /* Data interpretation: 
         * 1 = Park
         * 2 = Reverse
         * 3 = Drive
         * 4 = Neutral
        */
    }gear;

    struct PedalPosition{
        uint32_t frame_id = 2;
        uint8_t length = 1;
        uint8_t position = 0;
    }pedal;

    struct StartButton{
        uint32_t frame_id = 1;
        uint8_t length = 1;
        uint8_t position = 0;
        /* Data interpretation: 
         * 1 = Stop
         * 2 = Start
        */
    }start_button;

    struct DriveMode{
        uint32_t frame_id = 1;
        uint8_t length = 1;
        uint8_t position = 1;
        /* Data interpretation: 
         * 1 = Eco
         * 2 = Sport
        */
    }drive_mode;

    struct Speed{
        uint32_t frame_id = 4;
        uint8_t length = 1;
        uint8_t position = 2;
        /* Data interpretation: 
         * 1 : 1 conversion
        */
    }speed;

    struct Rpm{
        uint32_t frame_id = 4;
        uint16_t length = 2;
        uint8_t position = 0;
        /* Data interpretation: 
         * 1 : 1 conversion
        */
    }rpm;
}

#endif