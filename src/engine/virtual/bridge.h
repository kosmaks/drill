#pragma once

namespace drill {
  template<class T> class bridge {
  public:
    virtual void compile(T &object) = 0;
    virtual void draw(T &object) = 0;
  };
}
