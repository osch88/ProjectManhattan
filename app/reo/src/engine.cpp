#include "engine.hpp"

void Engine::SetEngineStaus(const reo_type::Database &_input){
    if (_input.ignition == reo_type::Ignition::kStop){
        engine_status_ = reo_type::EngineStatus::kOff; // Behöver vi kolla gear? Får vi gå till off om gear = drive?
    }
    else if (_input.ignition == reo_type::Ignition::kStart){
        engine_status_ = reo_type::EngineStatus::kOn;
    }
}

void Engine::UpdateGear(const reo_type::Database &_input){
    //När får vi gå till de olika? Får vi gå till Park om rpm > 0? ska vi printa något om man försöker göra något man inte får? 
    if (engine_status_ == reo_type::EngineStatus::kOff /*&& _input.gear == reo_type::Gear::kPark*/){
        gear_ = reo_type::Gear::kPark;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && _input.gear == reo_type::Gear::kPark && rpm_ == 0){
        gear_ = reo_type::Gear::kPark;
    }    
    else if (engine_status_ == reo_type::EngineStatus::kOn && _input.gear == reo_type::Gear::kDrive){
        gear_ = reo_type::Gear::kDrive;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && _input.gear == reo_type::Gear::kReverse){
        gear_ = reo_type::Gear::kReverse;
    }
    else{} // do nothing if engine is off and any other gear than park is requested?
}

void Engine::UpdateRpm(const reo_type::Database &_input){
    if (engine_status_ == reo_type::EngineStatus::kOff){
        rpm_ = 0; // shutting off engine
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && gear_ == reo_type::Gear::kPark && rpm_ == 0){
        rpm_ = MIN_RPM;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && gear_ != reo_type::Gear::kPark){ // ska denna endast gälla ökning av gas?
        double acceleration = (double)_input.gas - (double)throttle_;
        const int rpm_increase = 5;
        // lower bound points to the first element in map not greater than given key, second gives the coefficient
        double coeff = (*(coefficients_.lower_bound(rpm_))).second; 
        //std::cout << "RPM: " << rpm_ << "Coeff: " << coeff << std::endl;
        rpm_ += coeff*gear_ratio_[gear_number_]*acceleration*rpm_increase;
        if (rpm_ > MAX_RPM){
            rpm_ = MAX_RPM - 100;
        }
        throttle_ = _input.gas;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && gear_ != reo_type::Gear::kPark && throttle_ == 0 && rpm_ > MIN_RPM){
        const int rpm_decrease = 10;
        rpm_ -= gear_ratio_[gear_number_]*rpm_decrease;
        if (rpm_ < MIN_RPM){
            rpm_ = MIN_RPM + 50;
        }

    }


}


void Engine::set_inpVal(const reo_type::Database &_input) {

    SetEngineStaus(_input);
    UpdateGear(_input);
    UpdateRpm(_input);
}

void Engine::getData(reo_type::Database &_input) {
    _input.rpm = rpm_;
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

     if (engine_status_ == reo_type::EngineStatus::kOn) {
         std::cout << "Engine:\t\ton"    << std::endl;
     } else {
         std::cout << "Engine:\t\toff"   << std::endl;
     }
    std::cout << "Throttle:\t"      << this->throttle_ <<  "%"    << std::endl;
    std::cout << "RPM:\t\t"         << this->rpm_      << std::endl;
    if (gear_ == reo_type::Gear::kPark){
        std::cout << "Gear:\t\tPark" << std::endl;
    }
    else if (gear_ == reo_type::Gear::kNeutral){
        std::cout << "Gear:\t\tNeutral" << std::endl;
    }
    else if (gear_ == reo_type::Gear::kDrive){
        std::cout << "Gear:\t\tDrive" << std::endl;
    }
    else if (gear_ == reo_type::Gear::kReverse){
        std::cout << "Gear:\t\tReverse" << std::endl;
    }
    
}