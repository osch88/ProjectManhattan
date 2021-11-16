#include <iostream>
#include <thread>

#include "./include/database.hpp"
#include "./include/keyboard_input.hpp"
#include "./include/CANwrite.hpp"


int main(int argc, char *argv[]){

    struct Database db;

    keyboardInput key(db);
    

    CANwrite can;

    while (true) {
    /*std::thread t1*/key.keyReader(db);
    /*std::thread t2*/(can.sendCAN(db));
    }
    

    /*
    t1.join();
    t2.join();
    */

    return 0;
}
