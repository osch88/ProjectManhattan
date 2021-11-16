#include <iostream>
#include <thread>

#include "./include/database.hpp"
#include "./include/keyReader.hpp"
#include "./include/sendCAN.hpp"




int main(int argc, char *argv[]){

    struct Database *db;

    /*std::thread t1*/(keyReader(*db));
    /*std::thread t2*/(sendCAN(*db));

    /*
    t1.join();
    t2.join();
    */

    return 0;
}
