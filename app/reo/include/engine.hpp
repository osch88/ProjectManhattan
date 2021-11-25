#ifndef APP_REO_INCLUDE_ENGINE_HPP_
#define APP_REO_INCLUDE_ENGINE_HPP_

#include <iostream>
#include <map>
#include "reotype.hpp"

class Engine {
 private:
    reo_type::EngineStatus engine_status_ = reo_type::EngineStatus::kOff;
    reo_type::Gear gear_ = reo_type::Gear::kPark;
    double rpm_ = 0;
    unsigned int throttle_ = 0;
    unsigned int gear_number_ = 1;
    //double traction_force_ = 0;
    double speed_ = 0;
    const unsigned int MAX_RPM = 6000;
    const unsigned int MIN_RPM = 875;
    void SetEngineStaus(const reo_type::Database &_input);
    void UpdateGear(const reo_type::Database &_input);
    void UpdateRpm(const reo_type::Database &_input);
    void ShiftGear();
    void CalcSpeed();
    double CalcTractionForce();
    double CalcRoadForce();
    double CalcAeroForce();
    const double gear_ratio_[10] = {6, 5.25, 3.029, 1.95, 1.457, 1.221, 1, 0.809, 0.673, 4.015};
    const double drive_shaft_ratio_ = 2.955;
    const unsigned int efficiency_ = 1;
    const double wheel_radius_ = 0.3;
    const double vehicle_mass_ = 2250;
    const double drag_coefficient_ = 0.29;
    const double front_area_ = 2.23;
    const std::map<unsigned int, double> maxtorque_ = {{800, 210}, {2000, 280}, {2000, 280}, {3500, 310}, {5000, 300}, {6100, 270}};
 public:
    Engine() = default;
    void set_inpVal(const reo_type::Database &_input);
    void runEngine();
    void print();
    void getData(reo_type::Database &_input);
    ~Engine() = default;
};

#endif  // APP_REO_INCLUDE_ENGINE_HPP_
