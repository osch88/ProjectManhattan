#include <iostream>
#include <thread>
#include <chrono>

#include "./include/database.hpp"
#include "./include/keyboard_input.hpp"
#include "../../lib/writecan.hpp"


int main(int argc, char *argv[]){

    database_type::Database db;

    keyboardInput key(db);

    SocketCan socket_can;
    if (socket_can.Open("vcan0") == kStatusOk){
        bool run_status = true;
        bool write_status = true;
        bool key_status = true;
        while(run_status){
            //key_status = key.running;
            key.keyReader(db); // borde denna också retunera status? 
            write_status == WriteCanFrameUserInput(socket_can, db);
            
            run_status = key_status && write_status;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    else{
        printf("Cannot open can socket!");
    }
    return 0;


    

    //CANwrite can;

    //while (true) {
    //std::thread t1*/key.keyReader(db);
    //std::thread t2*/(can.sendCAN(db));
    //}
    

    /*
    t1.join();
    t2.join();
    */

   
}