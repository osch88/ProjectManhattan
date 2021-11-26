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
        gear_number_ = 9;
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
        const double pi = 3.14;
        rpm_ = 30.0 / pi * speed_ / wheel_radius_* gear_ratio_[gear_number_] * drive_shaft_ratio_;

        if (rpm_ < MIN_RPM){
            rpm_ = MIN_RPM;
        }
        if (rpm_ > MAX_RPM){
            rpm_ = MAX_RPM - 100;
        }
        
        throttle_ = _input.gas;
    }
}

double Engine::CalcTractionForce(){
    double torquemax = (*(maxtorque_.lower_bound(rpm_))).second; 
    double torque = torquemax * throttle_/100;
    double traction_force = (torque * gear_ratio_[gear_number_] * drive_shaft_ratio_ *efficiency_)/wheel_radius_;
    
    return traction_force; 
}

double Engine::CalcRoadForce(){
    const double gravity = 9.82;
    const double road_load_coeff = 0.011;
    double road_force; 
    if (speed_ <= 0){
        road_force = 0;
    }
    else{
        road_force = vehicle_mass_ *gravity * road_load_coeff;
    }
    
    return road_force;
}

double Engine::CalcAeroForce(){
    const double air_density = 1.225;
    double aero_force;
    if (speed_ <= 0){
        aero_force = 0;
    }
    else {
        aero_force = (air_density * drag_coefficient_ * front_area_ * speed_ * speed_)/2;
    }
         
    return aero_force;
}

void Engine::CalcSpeed(){
    double traction_force = CalcTractionForce();
    double road_force = CalcRoadForce();
    double aero_force = CalcAeroForce();
    double acceleration = (traction_force - road_force - aero_force) / vehicle_mass_;
    speed_ +=  acceleration * 0.01; 

    //TODO: replace with sample time variable 
}

void Engine::ShiftGear(){
    if(rpm_ > 3000 && gear_number_ < 8){
        gear_number_++;
    }
    else if (rpm_ < 1500 && gear_number_ > 1){
        gear_number_--;
    }
}

void Engine::set_inpVal(const reo_type::Database &_input) {

    SetEngineStaus(_input);
    UpdateGear(_input);
    CalcSpeed();
    UpdateRpm(_input);
    ShiftGear();
}

void Engine::getData(reo_type::Database &_input) {
    _input.rpm = rpm_;
    _input.speed = speed_;
    _input.gear_number = gear_number_;
    _input.gear = gear_;
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
    std::cout << "Speed:\t\t"         << this->speed_ * 3.6    << std::endl;
    std::cout << "Gear number:\t"         << this->gear_number_   << std::endl;
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