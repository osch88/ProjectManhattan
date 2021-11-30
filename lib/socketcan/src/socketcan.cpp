#include "socketcan.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <iostream>
#include <linux/can/raw.h>

SocketCan::SocketCan(){}

SocketCanStatus SocketCan::Open(const std::string &can_interface, const int32_t &read_timeout_ms){
    /* open socket */
    if ((m_socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) 
    {
        std::cerr << "socket create error\n";
        return SocketCanStatus::kStatusSocketCreateError;
    }
    struct sockaddr_can addr;
    struct ifreq ifr;
    strncpy(ifr.ifr_name, can_interface.c_str(), IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (!ifr.ifr_ifindex) {
        std::cerr << "if_nametoindex\n";
        return SocketCanStatus::kStatusInterfaceNameToIdxError;
    }
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    struct timeval time_value;
    time_value.tv_sec = 0; 
    time_value.tv_usec = read_timeout_ms * 1000;
    setsockopt(m_socket_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&time_value,sizeof(struct timeval));
    if (bind(m_socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error in socket bind\n";
        return SocketCanStatus::kStatusBindError;
    }
    return SocketCanStatus::kStatusOk;
}

SocketCanStatus SocketCan::WriteToCan(const CanFrame &msg){
    struct can_frame frame;
    memset(&frame, 0, sizeof(frame));
    frame.can_id = msg.id;
    frame.can_dlc = msg.len;
    memcpy(frame.data, msg.data, msg.len);
    int frame_size = sizeof(frame);
    int number_of_bytes = ::write(m_socket_, &frame, frame_size);
    //std::cout << "framesize: " << frame_size << " return from readfunc: " << number_of_bytes << std::endl;
    if (number_of_bytes != frame_size) {
        std::cerr << "write error, written bytes not as expected\n";
        return SocketCanStatus::kStatusWriteError;
    }
    return SocketCanStatus::kStatusOk;
}

SocketCanStatus SocketCan::ReadFromCan(CanFrame &msg){
    struct can_frame frame;
    auto frame_size = sizeof(frame);
    auto number_of_bytes = ::read(m_socket_, &frame, frame_size);
    if (number_of_bytes == 0 or number_of_bytes == -1){
        return SocketCanStatus::kNothingToRead;
    } else if (number_of_bytes != frame_size){
        std::cerr << "Can read error or incomplete CAN frame\n";
        return SocketCanStatus::kStatusReadError;
    }
    msg.id = frame.can_id;
    msg.len = frame.can_dlc;
    memcpy(msg.data, frame.data, frame.can_dlc);
    return SocketCanStatus::kStatusOk;
}

SocketCan::~SocketCan(){
    ::close(m_socket_);
}
