#include "socketcan.hpp"
#include <string>
#include <iostream>

int main (){
    scpp::SocketCan sockat_can;
    if (sockat_can.Open("vcan0") == scpp::STATUS_OK)
    {
    for (int j = 0; j < 20000; ++j)
    {
        scpp::CanFrame fr;
        scpp::CanFrame cf_to_write;
        
        
        //scpp::CanFrame cf_to_write;
        
        cf_to_write.id = 123;
        cf_to_write.len = 8;
        for (int i = 0; i < 8; ++i)
            cf_to_write.data[i] = j & (254);
        auto write_sc_status = sockat_can.WriteToCan(cf_to_write);
        if (write_sc_status != scpp::STATUS_OK)
            printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
        else
            printf("Message was written to the socket \n");


        while(sockat_can.ReadFromCan(cf_to_write) == scpp::STATUS_OK)
        {
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x %02x %02x %02x  \n", fr.len, fr.id, 
                fr.data[0], fr.data[1], fr.data[2], fr.data[3],
                fr.data[4], fr.data[5], fr.data[6], fr.data[7]);
        }

    }
    }
    else
    {
        printf("Cannot open can socket!");
    }
    return 0;

}