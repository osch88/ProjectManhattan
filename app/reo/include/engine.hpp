#ifndef ENGINE
#define ENGINE

#include <iostream>
#include "./parser.hpp"

const unsigned int MAX = 6000;
const unsigned int MIN = 800;

class Engine {
private:
    bool engineStatus = false;
    unsigned int RPM;
    unsigned int throttle;
    unsigned int targetRPM;

public:
    Engine() = default;
    void set_inpVal(const InputData_t _input);
    unsigned int get_Throttle();
    bool get_EngineStatus();
    unsigned int get_RPM();
    void runEngine();
    void print();
    void getData();
    ~Engine() = default;
};

#endif
