#include <iostream>
#include <string>
#include <unistd.h>
#include "../include/keyboard_input.hpp"
#include "../include/database.hpp"

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
    UP=65       for gas pedal increase (acceleration)
    DOWN=66     for gas pedal decrease (deccelration)
    1=49        for drive mode normal (default if non selected)
    2=50        for drive mode sport 
    K=107       accceleration
    L=108       decceleration
    */

keyboardInput::keyboardInput(database_type::Database &_db) {
    _db.ignition = database_type::Ignition::kStop;
    _db.gear = database_type::Gear::kPark;
    _db.drivemode = database_type::DriveMode::kEco;
    _db.gas = 0;
}
void keyboardInput::keyReader(database_type::Database &_db) {
    char input;
    int int_input;

    inputText();
    system("stty raw");
    input = getchar();
    int_input = input;
    //  std::cout << input << std::endl;

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
        this->gasPedalPos += 10;
        if (this->gasPedalPos > 100) {
            this->gasPedalPos = 100;
        }
        std::cout << "Accelerate: " << gasPedalPos << "%" << std::endl;
        _db.gas = gasPedalPos;
        break;
    case 107:
        this->gasPedalPos -= 10;
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
        std::cout << "Gracefully shutting down in: 3 seconds" << std::endl;
        for (auto i = 3; i > 0; i--) {
            std::cout << "Gracefully shutting down in: " << i << " seconds" << std::endl;
            sleep(1);
            system("clear");
        }
        system("stty cooked");
        exit(0);
        break;
    default:
        std::cout << "Please press a valid button, see manual for input" << std::endl;
        break;
    }
}
void keyboardInput::inputText() {
    std::cout << "Keyboard inputs: " << std::endl;
    std::cout << "\rS: start \n \rQ: stop \n\rP: gear position in park \n\rN: gear position neutral \n"
        << "\rD: gear position in drive \n\rR: gear position in reverse \n\rUP-arrow: accelerate \n"
        << "\rDOWN-arrow: decelerate \n\r1: drive mode normal \n\r2: drive mode sport \n\r. : gracefully shutdown" << std::endl;
}
void keyboardInput::printState(database_type::Database &_db) {  //  When called, prints state of input
    std::cout << ignitionToString(_db.ignition) << std::endl;
    std::cout << gearToString(_db.gear) << std::endl;
    std::cout << driveModeToString(_db.drivemode) << std::endl;
    std::cout << "Throttle position: " << _db.gas << " %" << std::endl;
}
std::string keyboardInput::ignitionToString(database_type::Ignition &_e) {
    std::string res;
    switch (_e) {
        case database_type::Ignition::kStart: res = "Engine is on"; break;
        case database_type::Ignition::kStop: res = "Engine is off"; break;
        default: res = "Nothing defined";
    }
    return res;
}
std::string keyboardInput::gearToString(database_type::Gear &_e) {
    std::string res;
    switch (_e) {
        case database_type::Gear::kPark: res = "Gear in park"; break;
        case database_type::Gear::kNeutral: res = "Gear in neutral"; break;
        case database_type::Gear::kDrive: res = "Gear in drive"; break;
        case database_type::Gear::kReverse: res = "Gear in reverse"; break;
        default: res = "Nothing defined";
    }
    return res;
}
std::string keyboardInput::driveModeToString(database_type::DriveMode &_e) {
    std::string res;
    switch (_e) {
        case database_type::DriveMode::kEco: res = "Drive mode: ECO"; break;
        case database_type::DriveMode::kSport: res = "Drive mode: SPORT"; break;
        default: res = "Nothing defined";
    }
    return res;
}
