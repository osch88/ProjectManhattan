#include <iostream>
#include <string>
#include <unistd.h>
#include "keyboard_input.hpp"
#include "database.hpp"


//  ToDo: class
//  ToDo: define keyinputs

/* - keyboard inputs are: 
    CHR=DEC
    S=115        for start
    Q=113        for stop
    P=112        for gear position Park
    N=110        for gear position Neutral
    D=100        for gear position Drive
    R=114        for gear position Reverse
    1=49         for drive mode normal (default if non selected)
    2=50         for drive mode sport 
    K=107        accceleration
    L=108        decceleration
    '7'=55       left blinker
    '8'=56       hazard light
    '9'=57       right blinker
    '0'=48       light off
    */

void keyboardInput::keyReader(database_type::Database &_db) {
    char input;
    int int_input;

    inputText();
    system("stty raw");
        input = getchar();
    int_input = input;

    system("stty cooked");
    system("clear");
    system("");
    switchCaseInput(_db, int_input);
}
void keyboardInput::switchCaseInput(database_type::Database &_db, const int &_in) {
    switch (_in) {
    case 115:
        std::cout << "Start button was pressed" << std::endl;
        _db.ignition = database_type::Ignition::kStart;
        break;
    case 113:
        std::cout << "Stop button was pressed" << std::endl;
        _db.ignition = database_type::Ignition::kStop;
        break;
    case 112:
        std::cout << "Gear position in park" << std::endl;
        _db.gear = database_type::Gear::kPark;
        break;
    case 110:
        std::cout << "Gear position in neutral" << std::endl;
        _db.gear = database_type::Gear::kNeutral;
        break;
    case 100:
        std::cout << "Gear position in drive" << std::endl;
        _db.gear = database_type::Gear::kDrive;
        break;
    case 114:
        std::cout << "Gear position in reverse" << std::endl;
        _db.gear = database_type::Gear::kReverse;
        break;
    case 108:
        this->gasPedalPos += 1;
        if (this->gasPedalPos > 100) {
            this->gasPedalPos = 100;
        }
        std::cout << "Accelerate: " << gasPedalPos << "%" << std::endl;
        _db.gas = gasPedalPos;
        break;
    case 107:
        this->gasPedalPos -= 1;
        if (this->gasPedalPos < 0) {
            this->gasPedalPos = 0;
        }
        std::cout << "Decelerate: " << gasPedalPos << "%" << std::endl;
        _db.gas = gasPedalPos;
        break;
    case 49:
        std::cout << "Drive mode ECO selected" << std::endl;
        _db.drivemode = database_type::DriveMode::kEco;
        break;
    case 50:
        std::cout << "Drive mode DYNAMIC selected" << std::endl;
        _db.drivemode = database_type::DriveMode::kSport;
        break;
    case 46:
        this->running = false;
        for (auto i = 3; i > 0; i--) {
            std::cout << "Gracefully shutting down in: " << i << " seconds" << std::endl;
            sleep(1);
            system("clear");
        }
        system("stty cooked");
        exit(0);
        break;
    case 55:
        std::cout << "Left blinker was pressed" << std::endl;
        _db.indicator_request = database_type::Indicator::kLeft;
        break;
    case 56:
        std::cout << "Hazard was pressed" << std::endl;
        _db.indicator_request = database_type::Indicator::kBoth;
        break;
    case 57:
        std::cout << "Right blinker was pressed" << std::endl;
        _db.indicator_request = database_type::Indicator::kRight;
        break;
    case 48:
        std::cout << "Light Off Request was pressed" << std::endl;
        _db.indicator_request = database_type::Indicator::kOff;
        break;
    default:
        std::cout << "Please press a valid button, see manual for input" << std::endl;
        break;
    }
}
void keyboardInput::inputText() {
    std::cout << "Keyboard inputs: " << std::endl;
    std::cout << "\rS: start \n \rQ: stop \n\rP: gear position in park \n\rN: gear position neutral \n"
        << "\rD: gear position in drive \n\rR: gear position in reverse \n\rL: accelerate \n"
        << "\rK: decelerate \n\r1: drive mode normal \n\r2: drive mode sport \n\r7: Left blinker \n\r8: Hazard \n\r9: Right blinker \n\r0: Lights Off \n\r. : gracefully shutdown" << std::endl;
}
