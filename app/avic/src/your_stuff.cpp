#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include "your_stuff.h"

QString driveModeStr;

void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    static _icons icons = {0,0,0,0,0,0,0,0,0,0,0,0};
    /*icons.hazard=0;
    icons.left_blinker=0;
    icons.right_blinker=0;
    icons.abs=0;
    icons.battery=0;
    icons.doors_open=0;
    icons.engine_check=0;
    icons.hand_break=0;
    icons.high_beam=0;
    icons.oil_check=0;
    icons.seat_belt=0;
    icons._reserved_pad=0;*/
    // double us_rpm;
    static uint8_t speed = 0;
    

    switch (static_cast<int>(_frame->can_id)) {
        case 1:
            {
            if (_frame->data[3]== 0) {
                icons.seat_belt=1;
            } else {
                icons.seat_belt=0;
            }

            if (_frame->data[4]== 1) {
                icons.high_beam=1;
            } else {
                icons.high_beam=0;
            }

            static bool previous_hazard = false;
            if (_frame->data[2] == 0) {
                icons.right_blinker=0;
                icons.left_blinker=0;
                icons.hazard=0;
                previous_hazard=false;
            } else if (_frame->data[2] == 1){
                icons.right_blinker=0;
                icons.left_blinker=1;
                icons.hazard=0;
                previous_hazard=false;
            } else if (_frame->data[2] == 2){
                icons.right_blinker=1;
                icons.left_blinker=0;
                icons.hazard=0;
                previous_hazard=false;
            } else if (_frame->data[2] == 3 && previous_hazard == false){
                icons.right_blinker=1;
                icons.left_blinker=1;
                //icons.hazard=1;
                //previous_hazard=true;
                //this->InstrumentCluster.setIcon(&icons);
            }
            
            this->InstrumentCluster.setIcon(&icons);
            break;
        case 4:
            {
            // from CAN bus
            uint16_t rpm = *((uint16_t*)(_frame->data));
            speed = *((uint8_t*)(_frame->data+2));
            char gearPindle = _frame->data[3];
            char gearNumber = _frame->data[4];
            // Fix for gear pindle indicator
            if (gearPindle == 3) {
                gearPindle = 2;
                gearNumber = 1;
                icons.hand_break = 0;
            } else if (gearPindle == 2) {
                gearPindle = 3;
                icons.hand_break = 0;
            } else if (gearPindle == 0) {
                icons.hand_break = 1;
            } else {
                icons.hand_break = 0;
            }
            
            //double fuel = static_cast<double>(_frame->data[5]);
            uint16_t fuel = _frame->data[5];
            uint16_t oil_temp = _frame->data[6];
            uint16_t cool_temp = _frame->data[7];
            // Init values
            this->InstrumentCluster.setTXT(driveModeStr);
            this->InstrumentCluster.setRPM(rpm);
            this->InstrumentCluster.setSpeed(speed);
            this->InstrumentCluster.setGear(gearNumber);
            this->InstrumentCluster.setGearPindle_int(gearPindle);
            this->InstrumentCluster.setIcon(&icons);
            this->InstrumentCluster.setFuelGauges(fuel);
            this->InstrumentCluster.setOilTemperatureGauges(oil_temp);
            this->InstrumentCluster.setTemperatureGauges(cool_temp);
            }
            break;
        case 5:
            {
            uint8_t driveMode = _frame->data[1];
            if (_frame->data[0]==1){
                this->InstrumentCluster.ignite(1);
                // Sets the drive mode
                if (driveMode == 0) {
                    driveModeStr = "Drive mode:\t COMFORT";
                } else if (driveMode == 1) {
                    driveModeStr = "Drive mode:\t SPORT";
                }
            } else{
                this->InstrumentCluster.ignite(0);
                driveModeStr = "...";
            }
            break;            
            }
            }
        default:
            break;
    }
}

/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();

    this->InstrumentCluster.init(_vs);

    this->startTimer(1);
}

bool yourStuff::run() {
    bool ret = true;
    CANOpener::ReadStatus status = CANOpener::ReadStatus::OK;
    canfd_frame frame;
    this->CANReader.read(&frame);
    /*while*/if (status == CANOpener::ReadStatus::OK) {
        this->YouHaveJustRecievedACANFrame(&frame);
    }
    if (status == CANOpener::ReadStatus::ERROR) ret = false;
    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) this->Counter++;
    else   this->Counter = 0;
    if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
        exit(-1);
    }

}

