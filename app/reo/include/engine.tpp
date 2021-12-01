
template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::SetEngineStatus(const reo_type::Database &_input){
    if (_input.ignition == reo_type::Ignition::kStop){
        engine_status_ = reo_type::EngineStatus::kOff;
    }
    else if (_input.ignition == reo_type::Ignition::kStart && _input.gear == reo_type::Gear::kPark){
        engine_status_ = reo_type::EngineStatus::kOn;
    }
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::UpdateDriveMode(const reo_type::Database &_input){
    if(_input.drive_mode == reo_type::DriveMode::kSport){
        drive_mode_ = reo_type::DriveMode::kSport;
    }
    else{
        drive_mode_ = reo_type::DriveMode::kEco;
    }
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::UpdateGear(const reo_type::Database &_input){
    
    if (engine_status_ == reo_type::EngineStatus::kOff){
        gear_ = reo_type::Gear::kPark;
        gear_number_ = 0;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && _input.gear == reo_type::Gear::kPark && speed_ <0.5f){
        gear_ = reo_type::Gear::kPark;
        gear_number_ = 0;
    }    
    else if (engine_status_ == reo_type::EngineStatus::kOn && _input.gear == reo_type::Gear::kDrive){
        gear_ = reo_type::Gear::kDrive;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && _input.gear == reo_type::Gear::kReverse && speed_ < 0.5f){
        gear_ = reo_type::Gear::kReverse;
        gear_number_ = 9;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && _input.gear == reo_type::Gear::kNeutral){
        gear_ = reo_type::Gear::kNeutral;
        gear_number_ = 0;
    }
    else{} // do nothing if engine is off and any other gear than park is requested
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::UpdateRpm(const reo_type::Database &_input){
    if (engine_status_ == reo_type::EngineStatus::kOff){
        rpm_ = 0; // shutting off engine
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && (gear_ == reo_type::Gear::kDrive || gear_ == reo_type::Gear::kReverse)){
        static const double pi = 3.14;
        rpm_ = 30.0 / pi * speed_ / vc.wheel_radius_* vc.gear_ratio_[gear_number_] * vc.drive_shaft_ratio_;

        if (rpm_ < vc.MIN_RPM){
            rpm_ = vc.MIN_RPM;
        }
        if (rpm_ > vc.MAX_RPM){
            rpm_ = vc.MAX_RPM - 100;
        }
        
        throttle_ = _input.gas;
    }
    else if (engine_status_ == reo_type::EngineStatus::kOn && (gear_ == reo_type::Gear::kNeutral || gear_ == reo_type::Gear::kPark)){
        double acceleration = (double)_input.gas - (double)throttle_;
        const double rpm_increase = 0.05;
        const double rpm_decrease = 1;
        double torquemax = (*(vc.maxtorque_.lower_bound(rpm_))).second; 
        double torque = torquemax * throttle_/100;
        rpm_ += torque*vc.gear_ratio_[gear_number_]*acceleration + (rpm_increase * throttle_) - (!throttle_ * rpm_decrease);
        
        if (rpm_ < vc.MIN_RPM){
            rpm_ = vc.MIN_RPM;
        }
        
        if (rpm_ > vc.MAX_RPM){
            rpm_ = vc.MAX_RPM - 100;
        }
        throttle_ = _input.gas;
    }
}

template <typename VehicleCharacteristics>
double Engine<VehicleCharacteristics>::CalcTractionForce(){
    double torquemax = (*(vc.maxtorque_.lower_bound(rpm_))).second; 
    double torque = torquemax * throttle_/100;
    double traction_force;
    
    if(gear_ == reo_type::Gear::kPark || gear_ == reo_type::Gear::kNeutral){
        traction_force = 0;
    }
    else {
        traction_force = (torque * vc.gear_ratio_[gear_number_] * vc.drive_shaft_ratio_ * vc.efficiency_)/vc.wheel_radius_;
    }

    return traction_force; 
}

template <typename VehicleCharacteristics>
double Engine<VehicleCharacteristics>::CalcRoadForce(){
    static const double gravity = 9.82;
    static const double road_load_coeff = 0.011;
    double road_force; 
    if (speed_ <= 0){
        road_force = 0;
    }
    else{
        road_force = vc.vehicle_mass_ * gravity * road_load_coeff;
    }
    
    return road_force;
}

template <typename VehicleCharacteristics>
double Engine<VehicleCharacteristics>::CalcAeroForce(){
    static const double air_density = 1.225;
    double aero_force;
    if (speed_ <= 0){
        aero_force = 0;
    }
    else {
        aero_force = (air_density * vc.drag_coefficient_ * vc.front_area_ * speed_ * speed_)/2;
    }
         
    return aero_force;
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::CalcSpeed(){
    double traction_force = CalcTractionForce();
    double road_force = CalcRoadForce();
    double aero_force = CalcAeroForce();
    double acceleration = (traction_force - road_force - aero_force) / vc.vehicle_mass_;
    
    if (rpm_ > (vc.MAX_RPM - 500) && gear_ == reo_type::Gear::kReverse ) {        // MAX speed for reverse
        speed_ = 50 / 3.6;
    }
    speed_ +=  acceleration * 0.005; 

    //TODO: replace with sample time variable 
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::ShiftGear(){
    unsigned int gear_shift_mode = static_cast<unsigned int>(drive_mode_);
    if (gear_ == reo_type::Gear::kNeutral || gear_ == reo_type::Gear::kReverse || gear_ == reo_type::Gear::kPark) {}
    else if(rpm_ > vc.gear_shift_up_[gear_shift_mode] && gear_number_ < vc.number_of_gears_){
        gear_number_++;
    }
    else if (rpm_ < vc.gear_shift_down_[gear_shift_mode] && gear_number_ > 1){
        gear_number_--;
    }
    else if (gear_ == reo_type::Gear::kDrive && gear_number_ == 0){
        gear_number_ = 1;
    }
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::set_inpVal(const reo_type::Database &_input) {
    SetEngineStatus(_input);
    UpdateDriveMode(_input);
    UpdateGear(_input);
    CalcSpeed();
    UpdateRpm(_input);
    ShiftGear();
    UpdateFuelAndTemp();
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::getData(reo_type::Database &_input) {
    _input.rpm = rpm_;
    _input.speed = speed_ * 3.6;
    _input.gear_number = gear_number_;
    _input.gear_pindle = gear_;
    _input.fuel = fuel_;
    _input.oil_temp = oil_temp_;
    _input.cooling_temp = cool_temp_;
    _input.engine_status = engine_status_;
    _input.drive_mode_status = drive_mode_;
}

template <typename VehicleCharacteristics>
void Engine<VehicleCharacteristics>::UpdateFuelAndTemp() {
    if (engine_status_ == reo_type::EngineStatus::kOn) {
        fuel_ -= 0.00008;
        if (oil_temp_ < 125) {
            oil_temp_ +=0.001;
        }
        if (cool_temp_ < 125) {
            cool_temp_ +=0.001;
        }
        
    } else {
        if (oil_temp_ > 0) {
            oil_temp_ -=0.001;    
        }
        if (cool_temp_ > 0) {
            cool_temp_ -=0.001;    
        }
    }
}
