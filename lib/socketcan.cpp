#include "socketcan.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <iostream>

#include <linux/can/raw.h>

using namespace scpp;

    SocketCan::SocketCan(){
    }

    SocketCanStatus SocketCan::Open(const std::string & can_interface, int32_t read_timeout_ms){
        //m_read_timeout_ms = read_timeout_ms;

        /* open socket */
        if ((m_socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) 
        {
            perror("socket");
            return STATUS_SOCKET_CREATE_ERROR;
        }
        struct sockaddr_can addr;
        struct ifreq ifr;

        strncpy(ifr.ifr_name, can_interface.c_str(), IFNAMSIZ - 1);
        ifr.ifr_name[IFNAMSIZ - 1] = '\0';
        ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
        if (!ifr.ifr_ifindex) {
            perror("if_nametoindex");
            return STATUS_INTERFACE_NAME_TO_IDX_ERROR;
        }

        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        // LINUX
        struct timeval tv;
        tv.tv_sec = 0;  /* 30 Secs Timeout */
        tv.tv_usec = m_read_timeout_ms_ * 1000;  // Not init'ing this can cause strange errors
        setsockopt(m_socket_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));

        if (bind(m_socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0) { //what does it mean?
            perror("Error in socket bind");
            return STATUS_BIND_ERROR;
        }

        return STATUS_OK;
    }


    SocketCanStatus SocketCan::WriteToCan(const CanFrame & msg){
        struct can_frame frame;
        memset(&frame, 0, sizeof(frame)); /* init CAN FD frame, e.g. LEN = 0 */ //what does it mean?
        //convert message to can_frame:
        frame.can_id = msg.id;
        frame.can_dlc = msg.len;
        memcpy(frame.data, msg.data, msg.len);

        /* send frame */
        int frame_size = sizeof(frame);
        int number_of_bytes = ::write(m_socket_, &frame, frame_size);
        //std::cout << "framesize: " << frame_size << " return from readfunc: " << number_of_bytes << std::endl;
        if (number_of_bytes != frame_size) {
            perror("write error, written bytes not as expected");
            return STATUS_WRITE_ERROR;
        }
        return STATUS_OK;
    }


    SocketCanStatus SocketCan::ReadFromCan(CanFrame & msg){
        struct can_frame frame;
        auto frame_size = sizeof(frame);
        // Read in a CAN frame
        auto number_of_bytes = ::read(m_socket_, &frame, frame_size);
        
        std::cout << "framesize: " << frame_size << " return from readfunc: " << number_of_bytes << std::endl;

        if (number_of_bytes != frame_size){
            perror("Can read error or incomplete CAN frame");
            return STATUS_READ_ERROR;
        }

        msg.id = frame.can_id;
        msg.len = frame.can_dlc;
        memcpy(msg.data, frame.data, frame.can_dlc);
        return STATUS_OK;
    }

    SocketCanStatus SocketCan::Close(){
        ::close(m_socket_);
        return STATUS_OK;
    }

    SocketCan::~SocketCan(){
        Close();
    }