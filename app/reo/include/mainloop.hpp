#ifndef APP_REO_INCLUDE_MAINLOOP_HPP_
#define APP_REO_INCLUDE_MAINLOOP_HPP_

#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "hal_monitor.hpp"
#include "engine.hpp"

class MainLoop{
 private:
  reo_type::Database data_;
  HalMonitor hal_monitor_;
  Engine<v60_t> engine;
  mutable std::shared_mutex mtx_;

 public:
  void hal();
  void emulator();
  void canSend();
  void run();
};

#endif  // APP_REO_INCLUDE_MAINLOOP_HPP_
