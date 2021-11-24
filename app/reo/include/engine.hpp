#ifndef APP_REO_INCLUDE_ENGINE_HPP_
#define APP_REO_INCLUDE_ENGINE_HPP_

#include <iostream>
#include <map>
#include "reotype.hpp"

class Engine {
 private:
    reo_type::EngineStatus engine_status_ = reo_type::EngineStatus::kOff;
    reo_type::Gear gear_ = reo_type::Gear::kPark;
    unsigned int rpm_ = 0;
    unsigned int throttle_ = 0;
    unsigned int gear_number_ = 1;
    //unsigned int target_rpm_;
    const unsigned int MAX_RPM = 6000;
    const unsigned int MIN_RPM = 800;
    void SetEngineStaus(const reo_type::Database &_input);
    void UpdateGear(const reo_type::Database &_input);
    void UpdateRpm(const reo_type::Database &_input);
    const double gear_ratio_[10] = {6, 5.25, 3.029, 1.95, 1.457, 1.221, 1, 0.809, 0.673, 4.015};
    const std::map<unsigned int, double> coefficients_ = {{800, 3.2}, {2000, 3.2}, {2000, 2.5}, {5000, 2.5}, {5000, 1}, {6100, 0.85}};
 public:
    Engine() = default;
    void set_inpVal(const reo_type::Database &_input);
    void runEngine();
    void print();
    void getData(reo_type::Database &_input);
    ~Engine() = default;
};

#endif  // APP_REO_INCLUDE_ENGINE_HPP_
