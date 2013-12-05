#pragma once

namespace drill {
  class renderer {
  public:
    renderer();
    virtual ~renderer();

    void init_window(const std::string &title);
    void set_fullscreen_enabled(bool enabled);

    void start();
    void pause();
    void stop();

    event on_start;
    event on_pause;
    event on_stop;
    event on_update;
  };
}
