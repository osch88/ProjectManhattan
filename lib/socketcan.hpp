#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#include <cstdint>
#include <linux/can.h>
#include <string>

namespace scpp{

    struct CanFrame{
        uint32_t id = 0;
        uint8_t len = 0;
        uint8_t data[8];
    };

    enum SocketCanStatus{
        STATUS_OK = 1 << 0,
        STATUS_SOCKET_CREATE_ERROR = 1 << 2,
        STATUS_INTERFACE_NAME_TO_IDX_ERROR = 1 << 3,
        STATUS_MTU_ERROR = 1 << 4, /// maximum transfer unit
        STATUS_CANFD_NOT_SUPPORTED = 1 << 5, /// Flexible data-rate is not supported on this interface
        STATUS_ENABLE_FD_SUPPORT_ERROR = 1 << 6, /// Error on enabling fexible-data-rate support
        STATUS_WRITE_ERROR = 1 << 7,
        STATUS_READ_ERROR = 1 << 8,
        STATUS_BIND_ERROR = 1 << 9,
    };

    class SocketCan{
        private:
            int m_socket_ = -1;
            int32_t m_read_timeout_ms_ = 3;
            
        public:
            SocketCan();
            SocketCan(const SocketCan &) = delete;
            SocketCan & operator=(const SocketCan &) = delete;
            SocketCanStatus Open(const std::string & can_interface, int32_t read_timeout_ms = 3);
            SocketCanStatus WriteToCan(const CanFrame & msg);
            SocketCanStatus ReadFromCan(CanFrame & msg);
            SocketCanStatus Close(); //put in destructor directly?
            ~SocketCan();
    };
}
#endif