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

enum class SeatBelt {
    kNotApplied = 0,
    kApplied
};

enum class HighBeam {
    kHighBeamOff = 0,
    kHighBeamOn
};

enum class Brake {
    kHandBrakeOff = 0,
    kHandBrakeOn
};

struct Database {
    Ignition ignition;
    Gear gear;
    DriveMode drivemode;
    unsigned int gas;
    unsigned int RPM;
    Indicator indicator_request;
    Indicator indicator_status;
    SeatBelt seat_belt;
    HighBeam high_beam;
    Brake brake;
};
}  //  namespace database_type

#endif  //  PROJECTMANHATTAN_APP_INPUTHANDLER_INCLUDE_DATABASE_HPP_
