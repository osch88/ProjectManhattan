#ifndef APP_REO_INCLUDE_ENGINE_HPP_
#define APP_REO_INCLUDE_ENGINE_HPP_

#include <iostream>
#include "database.hpp"

const unsigned int MAX = 6000;
const unsigned int MIN = 800;

class Engine {
 private:
    bool ignition = false;
    unsigned int RPM;
    unsigned int throttle;
    unsigned int targetRPM;

 public:
    Engine() = default;
    void set_inpVal(const database_type::Database &_input);
    void runEngine();
    void print();
    void getData(database_type::Database &_input);
    ~Engine() = default;
};

#endif  // APP_REO_INCLUDE_ENGINE_HPP_
