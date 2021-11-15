#include "../include/engine.hpp"

bool Engine::getEngineStatus() {
    return engineStatus;
}

void Engine::setEngineStatus(bool _state) {
    engineStatus = _state;
}

unsigned int Engine::getRPM() {
    return RPM;
}

void Engine::setThrottle(unsigned int _gas) {
    throttle = _gas;
}

void Engine::runEngine() {
    RPM = static_cast<float>(throttle / 100.0f * MAX);
}