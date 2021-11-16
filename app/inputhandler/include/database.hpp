#ifdef DATABASE_H
#define DATABASE_H

namespace database_type {

    enum Ignition {
        kStop = 0,
        kStart
    }
    enum Gear {
        kPark = 0,
        kNeutral,
        kDrive,
        kReverse
    }
    enum DriveMode {
        kEco = 0;
        kSport
    }

    struct Database {
        Ignition ignition;
        Gear gear;
        DriveMode drivemode;
        unsigned int gas;
    }
}


#endif