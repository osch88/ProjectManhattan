#ifndef PARSER
#define PARSER

struct InputData {
    unsigned int gasPedal;
    unsigned int gearPos;
    unsigned int driveMode;
    bool engineOn;

}typedef InputData_t;

struct OutputData {
    unsigned int gasPedal;
    unsigned int RPM;
    unsigned int gearPos;
    unsigned int driveMode;
    bool engineOn;
    unsigned int speed;

}typedef OutputData_t;

#endif