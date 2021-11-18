#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#include <cstdint>
#include <linux/can.h>
#include <string>

struct CanFrame{
    uint32_t id = 0;
    uint8_t len = 0;
    uint8_t data[8];
};

enum SocketCanStatus{
    kStatusOk = 0,
    kStatusSocketCreateError,
    kStatusInterfaceNameToIdxError,
    kStatusWriteError,
    kStatusReadError,
    kStatusBindError,
    kNothingToRead
};

class SocketCan{
    private:
        int m_socket_ = -1;
        
    public:
        SocketCan();
        SocketCan(const SocketCan &);
        SocketCan & operator=(const SocketCan &) = delete;
        SocketCanStatus Open(const std::string & can_interface, int32_t read_timeout_ms = 3);
        SocketCanStatus WriteToCan(const CanFrame & msg);
        SocketCanStatus ReadFromCan(CanFrame & msg);
        ~SocketCan();
};

#endif