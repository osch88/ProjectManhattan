#include "../include/engine.hpp"

bool Engine::get_EngineStatus() {
    return engineStatus;
}

unsigned int Engine::get_RPM() {
    return RPM;
}

void Engine::set_inpVal(const InputData_t _input) {
    throttle = _input.gasPedal;
    engineStatus = _input.engineOn;
    if(engineStatus && RPM == 0) RPM = MIN;
    targetRPM = static_cast<float>( throttle / 100.0f * MAX );
    //TODO: adjust so that minimal gas response does not give a lower RPM than MIN
    this->runEngine();
}

unsigned int Engine::get_Throttle() {
    return throttle;
}

void Engine::runEngine() {
    
    if( RPM < targetRPM ) {
        RPM += 100;
    } else {
        RPM -= 300;
    }
}

void Engine::print() {

    std::cout << "\033[H\033[2J\033[3J";    // Clear screen

    std::cout   << 
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
                << std::endl;

    if(this->get_EngineStatus()) {
        std::cout << "Engine:\t\ton"    << std::endl;
    } else {
        std::cout << "Engine:\t\toff"   << std::endl;
    }

    std::cout << "Throttle:\t"      << this->get_Throttle() <<  "%"    << std::endl;
    std::cout << "RPM:\t\t"         << this->get_RPM()      << std::endl;
}