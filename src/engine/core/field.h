#pragma once

namespace drill {
  template<class T> class field {
  public: 
    field(T *v = nullptr) : value(v) {}
    inline T& operator=(T& r) { return *(value = &r); }
    inline T& operator()() { return *value; }
  private:
    T *value;
  };

  template<class T> class p_field {
  public: 
    inline T operator=(T r) { return value = r; }
    inline const T& operator()() { return value; }
  private:
    T value;
  };

  template<class T> class c_field {
  public: 
    c_field(T v = nullptr) : value(v) {}
    inline T operator=(T r) { return value = r; }
    inline const T operator()() { return value; }
  private:
    T value;
  };
}
