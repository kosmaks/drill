#pragma once

namespace drill {
  typedef struct {
    float frames_since_start;
    float seconds_since_start;
    float clocks_since_start;
    float instant_fps;
    float average_fps;
  } timeinfo_t;

  class service {
  public:
    virtual ~service() {}

    virtual void init() {}
    virtual void update(const timeinfo_t& timeinfo) {}
    virtual void pause() {}
  };
}
