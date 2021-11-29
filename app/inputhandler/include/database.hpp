#ifndef DATABASE_HPP_
#define DATABASE_HPP_

namespace database_type {

enum class Ignition {
    kStop = 0,
    kStart
};
enum class Gear {
    kPark = 0,
    kNeutral,
    kDrive,
    kReverse
};
enum class DriveMode {
    kEco = 0,
    kSport
};

enum class Indicator {
    kOff = 0,
    kLeft,
    kRight,
    kBoth
};

struct Database {
    Ignition ignition;
    Gear gear;
    DriveMode drivemode;
    unsigned int gas;
    unsigned int RPM;
    Indicator indicator_request;
    Indicator indicator_status;
};
}  //  namespace database_type



#endif  //  PROJECTMANHATTAN_APP_INPUTHANDLER_INCLUDE_DATABASE_HPP_
