#include <iostream>
#include "../include/engine.hpp"


int main(int argc, char **argv) {

    std::cout << "ENGINE EMULATOR" << std::endl;

    Engine engine;

    engine.setThrottle(50);
    engine.setEngineStatus(true);
    engine.runEngine();
    
    if(engine.getEngineStatus()) {
        std::cout << "Engine is on" << std::endl;
    } else {
        std::cout << "Engine is NOT on" << std::endl;
    }

    std::cout << "RPM: "<< engine.getRPM() << std::endl;


    return 0;
}
