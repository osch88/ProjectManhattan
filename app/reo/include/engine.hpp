#ifndef ENGINE_H
#define ENGINE_H

const unsigned int MAX = 6000;
const unsigned int MIN = 800;

class Engine {
private:
    bool engineStatus;
    unsigned int RPM;
    unsigned int throttle;

public:
    Engine() = default;
    void runEngine();
    bool getEngineStatus();
    void setEngineStatus(bool _state);
    unsigned int getRPM();
    void setThrottle(unsigned int _gas);
    ~Engine() = default;
};

#endif
