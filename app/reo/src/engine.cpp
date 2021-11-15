#include "../include/engine.hpp"

bool Engine::get_EngineStatus() {
    return engineStatus;
}

void Engine::set_EngineStatus(bool _state) {
    engineStatus = _state;
}

unsigned int Engine::get_RPM() {
    return RPM;
}

void Engine::set_inputValues(unsigned int _gas, bool _engineStatus) {
    throttle = _gas;
    engineStatus = _engineStatus;
    targetRPM = static_cast<float>( throttle / 100.0f * MAX );
}

unsigned int Engine::get_Throttle() {
    return throttle;
}

void Engine::runEngine() {
    
    // unsigned int targetRPM = 4000;
    
    if( RPM < targetRPM ) {
        // RPM = static_cast<float>(throttle / 100.0f * MAX);
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
        std::cout << "Engine:\t\ton" << std::endl;
    } else {
        std::cout << "Engine:\t\toff" << std::endl;
    }

    std::cout << "Throttle:\t"  << this->get_Throttle() <<  "%"    << std::endl;
    std::cout << "RPM:\t\t"       << this->get_RPM()      << std::endl;
}