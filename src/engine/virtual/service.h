#pragma once

namespace drill {
  class service {
  public:
    virtual ~service() {}

    virtual void init() {}
    virtual void update() {}
    virtual void pause() {}
  };
}
