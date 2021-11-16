#include <iostream>
#include <string>
#include <unistd.h>
#include "../include/keyboard_input.hpp"
#include "../include/database.hpp"

//ToDo: class
//ToDo: define keyinputs

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
    K=107
    L=108
    */

keyboardInput::keyboardInput(Database &_db){
    _db.gear = Gear::kPark;
}
void keyboardInput::keyReader(Database &_db){
    
    char input;
    int int_input;
    

    inputText();
    system("stty raw");
    input = getchar(); 
    int_input = input;
    std::cout << input << std::endl;
    //sleep(1);
    
    // terminate when "." is pressed
    system("stty cooked");
    system("clear");
    system("");
    switch (int_input){
    case 115:
        std::cout << "Start button was pressed" << std::endl;
        _db.ignition = Ignition::kStart;
        break;
    case 113:
        std::cout << "Stop button was pressed" << std::endl;
        _db.ignition = Ignition::kStop;
        break;
    case 112:
        std::cout << "Gear position in park" << std::endl;
        _db.gear = Gear::kPark;
        break;
    case 110:
        std::cout << "Gear position in neutral" << std::endl;
        _db.gear = Gear::kNeutral;
        break;
    case 100:
        std::cout << "Gear position in drive" << std::endl;
        _db.gear = Gear::kDrive;
        break;
    case 114:
        std::cout << "Gear position in reverse" << std::endl;
        _db.gear = Gear::kReverse;
        break;
    case 108:
        gasPedalPos += 10;
        if (gasPedalPos > 100){
            gasPedalPos = 100;
        }
        std::cout << "Accelerate: " << gasPedalPos << "%" << std::endl;
        _db.gas = gasPedalPos;
        break;
    case 107:
        gasPedalPos -= 10;
        if (gasPedalPos < 0){
            gasPedalPos = 0;
        }
        std::cout << "Decelerate: " << gasPedalPos << "%" << std::endl;
        _db.gas = gasPedalPos;
        break;
    case 49:
        std::cout << "Drive mode ECO selected" << std::endl;
        _db.drivemode = DriveMode::kEco;
        break;
    case 50:
        std::cout << "Drive mode DYNAMIC selected" << std::endl;
        _db.drivemode = DriveMode::kSport;
        break;
    case 46:
        //std::cout << "Gracefully shutting down in: 3 seconds" << std::endl;
        for(auto i=3; i>0; i--){
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
void keyboardInput::inputText(){
    std::cout << "Keyboard inputs: " << std::endl;
    std::cout << "\rS: start \n \rQ: stop \n\rP: gear position in park \n\rN: gear position neutral \n"
        << "\rD: gear position in drive \n\rR: gear position in reverse \n\rUP-arrow: accelerate \n"
        << "\rDOWN-arrow: decelerate \n\r1: drive mode normal \n\r2: drive mode sport \n\r. : gracefully shutdown" << std::endl;
}


