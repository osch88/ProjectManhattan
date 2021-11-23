#include "engine.hpp"

void Engine::set_inpVal(const database_type::Database &_input) {
    throttle = _input.gas;
    if (_input.ignition == database_type::Ignition::kStart){
        ignition = true;
        //exit(-1);
    } else if (_input.ignition == database_type::Ignition::kStop) {
         ignition = false;
         targetRPM = 0;
         runEngine();
         return;
    }
    
    if (ignition && RPM == 0) RPM = MIN;
    targetRPM = static_cast<float>(throttle / 100.0f * MAX);
    this->runEngine();
}

void Engine::runEngine() {
    RPM = targetRPM;
    // if (RPM = targetRPM) {
    //     RPM += 100;
    // } else {
    //     RPM -= 300;
    // }
}

void Engine::getData(database_type::Database &_input) {
    _input.RPM = RPM;
}


void Engine::print() {
    std::cout   << "\033[H\033[2J\033[3J";    // Clear screen
    std::cout   << "\x1B[32m"
    R"(
                     _            
                    (_)           
     ___ _ __   __ _ _ _ __   ___ 
    / _ \ '_ \ / _` | | '_ \ / _ \
    |  __/ | | | (_| | | | | |  __/
    \___|_| |_|\__, |_|_| |_|\___|
                __/ |             
               |___/               
    )"
                << "\x1B[0m"
                << std::endl;

     if (this->ignition) {
         std::cout << "Engine:\t\ton"    << std::endl;
     } else {
         std::cout << "Engine:\t\toff"   << std::endl;
     }
    std::cout << "Throttle:\t"      << this->throttle <<  "%"    << std::endl;
    std::cout << "RPM:\t\t"         << this->RPM      << std::endl;
}