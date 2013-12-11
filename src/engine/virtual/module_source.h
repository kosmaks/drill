#pragma once

#include <list>
#include "engine/core/platform.h"
#include "module.h"
#include "modules/object_compiler.h"
#include "modules/camera_controller.h"
#include "modules/transform.h"

namespace drill {
  class module_source : public dependency {
  public:
    virtual void listen() = 0;
    virtual void run() = 0;

    object_compiler *m_object_compiler;
    camera_controller *m_camera_controller;
    transform *m_transform;
  };
}
