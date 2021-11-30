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
  reo_type::Database data_;
  SocketCan socket_can_;
  HalMonitor hal_monitor_;
  Engine<v60_t> engine;
  // Threads
  mutable std::shared_timed_mutex mutex_;

 public:
  void hal();
  void emulator();
  void canSend();
  void run();
};


#endif  // APP_REO_INCLUDE_MAINLOOP_HPP_
