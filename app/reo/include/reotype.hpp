
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
enum class Brake {
    kHandBrakeOff = 0,
    kHandBrakeOn
};
struct Database {
    Ignition ignition;
    Gear gear;
    Gear gear_pindle;
    DriveMode drive_mode;
    DriveMode drive_mode_status;
    EngineStatus engine_status;
    unsigned int gas;
    unsigned int rpm;
    unsigned int speed;
    unsigned int gear_number;
    unsigned int fuel;
    unsigned int oil_temp;
    unsigned int cooling_temp;
    Brake brake;
};
}  
#endif  
