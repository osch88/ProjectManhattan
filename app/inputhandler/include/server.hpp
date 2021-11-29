#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "keyboard_input.hpp"
#include "socketcan.hpp"
#include "turn_indicator.hpp"

class Server {
    private:
        const char CAN_NAME[6] = "vcan0";
        const int DELAY_BETWEEN_FRAMES_ = 1; // milliseconds
        database_type::Database data_;
        SocketCan socket_can_;
        keyboardInput key_board_;
        TurnIndicator turn_indicator_;
        mutable std::shared_timed_mutex mutex_;
        std::thread t1_;

    public:
        Server();
        void Run();
        void KeyBoard();
        void CanWriter();
        ~Server();
};

#endif