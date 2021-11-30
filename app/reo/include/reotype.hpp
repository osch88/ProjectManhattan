
#ifndef REOTYPE_HPP_
#define REOTYPE_HPP_
namespace reo_type {
enum class Ignition {
    kStop,
    kStart
};
enum class Gear {
    kPark,
    kNeutral,
    kDrive,
    kReverse
};
enum class DriveMode {
    kEco,
    kSport
};
enum class EngineStatus{
    kOff,
    kOn
};
struct Database {
    Ignition ignition;
    Gear gear;
    DriveMode drive_mode;
    EngineStatus engine_status;
    unsigned int gas;
    unsigned int rpm;
    unsigned int speed;
    unsigned int gear_number;
    mutable std::shared_mutex mtx;
};
}  
#endif  
