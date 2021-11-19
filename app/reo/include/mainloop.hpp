#ifndef APP_REO_INCLUDE_MAINLOOP_HPP_
#define APP_REO_INCLUDE_MAINLOOP_HPP_

#include "../../../lib/socketcan.hpp"
#include "../../../lib/hal_monitor.hpp"
#include "./engine.hpp"

class MainLoop{
 public:
  static void run();
};

#endif  // APP_REO_INCLUDE_MAINLOOP_HPP_
