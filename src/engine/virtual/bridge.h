#pragma once

namespace drill {
  template<class T> class bridge {
  public:
    bridge(T &target) : current_target(&target) {}
    virtual void compile() = 0;
    virtual void draw() = 0;

  protected:
    T *current_target;
  };
}
