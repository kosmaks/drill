#pragma once

namespace drill {
  class Scene {
  public:
    Scene();
    virtual ~Scene();

    virtual void load() = 0;
    virtual void compile() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void update() = 0;
  };
}
