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

struct Database {
    Ignition ignition;
    Gear gear;
    DriveMode drivemode;
    unsigned int gas;
};
}  //  namespace database_type



#endif  //  PROJECTMANHATTAN_APP_INPUTHANDLER_INCLUDE_DATABASE_HPP_
