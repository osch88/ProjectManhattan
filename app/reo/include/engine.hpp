#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>

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
    void set_EngineStatus(bool _state);
    void set_inputValues(unsigned int _gas, bool _engineStatus);
    unsigned int get_Throttle();
    bool get_EngineStatus();
    unsigned int get_RPM();
    void runEngine();
    void print();
    ~Engine() = default;
};

#endif
