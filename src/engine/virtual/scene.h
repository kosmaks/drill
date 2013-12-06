#pragma once

namespace drill {
  class scene {
  public:
    scene();
    virtual ~scene();

    virtual void load() = 0;
    virtual void compile() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void update() = 0;
  };
}
