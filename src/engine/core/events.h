#pragma once
#include <functional>
#include <list>

namespace drill {

  class ehandler;
  class event {
  public:

    void trigger();

    void on(ehandler *callback);
    void once(ehandler *callback);

    void off(ehandler *callback);
    void clear();

  private:
    std::list<ehandler*> _callbacks;
    std::list<ehandler*> _once_callbacks;
  };

  class ehandler {
  public:
    typedef std::function<void()> callback_t;

    callback_t operator=(callback_t cb) { return _cb = cb; }
    void operator()() { _cb(); } 

  private:
    callback_t _cb;
  };
}
