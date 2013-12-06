#pragma once

#include <iostream>
#include <functional>

#include "engine/virtual/renderer.h"
#include "engine/virtual/compiler.h"

#define LOG_DEBUG(x) (std::cout << __FILE__ << ":" << __LINE__ << " [.] " << x << std::endl)
#define LOG_INFO(x)  (std::cout << __FILE__ << ":" << __LINE__ << " [-] " << x << std::endl)
#define LOG_WARN(x)  (std::cerr << __FILE__ << ":" << __LINE__ << " [!] " << x << std::endl)
#define LOG_ERROR(x) (std::cerr << __FILE__ << ":" << __LINE__ << " [#] " << x << std::endl)

namespace drill {
  class application final {
  public:
    typedef struct {
      renderer *_renderer;
      compiler *_compiler;
    } config_t;

    application(const config_t &config);
    ~application();

  private:
    template<class T> static void dependency(T *item, const std::string &title="");

    config_t _config;
  };
}
