#pragma once
#include <functional>
#include <list>

namespace drill {
  class event {

  public:
    typedef void(*callback_t)(void*);

    void trigger(void *param = nullptr);

    void on(const callback_t &callback);
    void once(const callback_t &callback);

    void off(const callback_t &callback);
    void clear();

  private:
    std::list<callback_t> _callbacks;
    std::list<callback_t> _once_callbacks;
  };
}
