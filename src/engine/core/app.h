#pragma once

#include <iostream>
#include <functional>
#include <list>

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

  private:
    bool _running;
    bool _frozen;

    std::list<service*> _services;
  };
}
