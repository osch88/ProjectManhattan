#ifndef APP_REO_INCLUDE_VEHICLECHARACTERISTIC_HPP_
#define APP_REO_INCLUDE_VEHICLECHARACTERISTIC_HPP_

#include <iostream>
#include <map>

typedef struct V60{
    const unsigned int MAX_RPM = 6000;
    const unsigned int MIN_RPM = 875;
    const double gear_ratio_[10] = {6, 5.25, 3.029, 1.95, 1.457, 1.221, 1, 0.809, 0.673, 4.015};
    const double drive_shaft_ratio_ = 2.955;
    const unsigned int efficiency_ = 1;
    const double wheel_radius_ = 0.3;
    const double vehicle_mass_ = 2250;
    const double drag_coefficient_ = 0.29;
    const double front_area_ = 2.23;
    const std::map<unsigned int, double> maxtorque_ = {{800, 210}, {2000, 280}, {2000, 280}, {3500, 310}, {5000, 300}, {6100, 270}};       
}v60_t;


#endif  // APP_REO_INCLUDE_VEHICLECHARACTERISTIC_HPP_