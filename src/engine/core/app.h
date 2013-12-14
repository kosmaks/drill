#pragma once

#include <ctime>
#include <iostream>
#include <functional>
#include <list>

#include "engine/core/types.h"
#include "engine/core/errors.h"
#include "engine/virtual/service.h"

#define LOG_DEBUG(x) (std::cout << __FILE__ << ":" << __LINE__ << " [.] " << x << std::endl)
#define LOG_INFO(x)  (std::cout << __FILE__ << ":" << __LINE__ << " [-] " << x << std::endl)
#define LOG_WARN(x)  (std::cerr << __FILE__ << ":" << __LINE__ << " [!] " << x << std::endl)
#define LOG_ERROR(x) (std::cerr << __FILE__ << ":" << __LINE__ << " [#] " << x << std::endl)

namespace drill {

  class application {
  public:
    application();
    ~application();

    void add_service(service &serv);

    void run();
    void freeze();
    void kill();

    void set_max_fps(uint32_t fps);
    uint32_t get_max_fps() { return max_fps; }

  private:
    bool _running;
    bool _frozen;

    uint32_t max_fps, 
             min_clocks_per_frame,
             clocks_at_last_update;

    timeinfo_t _timeinfo;
    clock_t clocks_at_start;
    uint32_t last_second, 
             current_second;
    float last_frames;

    std::list<service*> _services;
  };
}
