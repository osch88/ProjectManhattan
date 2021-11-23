#ifndef APP_REO_INCLUDE_MAINLOOP_HPP_
#define APP_REO_INCLUDE_MAINLOOP_HPP_

#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "socketcan.hpp"
#include "hal_monitor.hpp"
#include "engine.hpp"

class MainLoop{
 private:
  // CONST
  const char canName[6] = "vcan0";
  // INIT
  database_type::Database data;
  SocketCan socket_can;
  HalMonitor hal_monitor;
  Engine engine;
  // Threads
  mutable std::shared_timed_mutex mutex_;

 public:
  void hal();
  void emulator();
  void canSend();
  void run();
};

#endif  // APP_REO_INCLUDE_MAINLOOP_HPP_
