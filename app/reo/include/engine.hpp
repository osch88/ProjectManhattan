#ifndef APP_REO_INCLUDE_ENGINE_HPP_
#define APP_REO_INCLUDE_ENGINE_HPP_

#include <iostream>
#include "reotype.hpp"
#include "vehiclecharacteristic.hpp"

template <typename VehicleCharacteristics>
class Engine {
 private:
    reo_type::EngineStatus engine_status_ = reo_type::EngineStatus::kOff;
    reo_type::Gear gear_ = reo_type::Gear::kPark;
    reo_type::DriveMode drive_mode_ = reo_type::DriveMode::kEco;
    reo_type::Brake brake_ = reo_type::Brake::kBrakeOff;
    double rpm_ = 0;
    unsigned int throttle_ = 0;
    unsigned int gear_number_ = 1;
    double speed_ = 0;
    float fuel_= 200;
    float oil_temp_ = 0;
    float cool_temp_ = 0;
    VehicleCharacteristics vc;
    void SetEngineStatus(const reo_type::Database &_input);
    void UpdateDriveMode(const reo_type::Database &_input);
    void UpdateGear(const reo_type::Database &_input);
    void UpdateBrake(const reo_type::Database &_input);
    void UpdateRpm(const reo_type::Database &_input);
    void ShiftGear();
    void CalcSpeed();
    double CalcTractionForce();
    double CalcRoadForce();
    double CalcAeroForce();
    double CalcBrakeForce();
    void UpdateFuelAndTemp();
    
 public:
    Engine() = default;
    void set_inpVal(const reo_type::Database &_input);
    //void print();
    void getData(reo_type::Database &_input);
    ~Engine() = default;
};

#include "engine.tpp"


#endif  // APP_REO_INCLUDE_ENGINE_HPP_
