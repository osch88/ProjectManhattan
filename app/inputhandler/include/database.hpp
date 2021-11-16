#ifndef DATABASE
#define DATABASE

namespace database_type{

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
}



#endif