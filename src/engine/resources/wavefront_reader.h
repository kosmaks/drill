#pragma once

#include <list>
#include <vector>
#include <string>
#include "engine/core/types.h"
#include "engine/world/object.h"

namespace drill {
  class wavefront_reader {
  public:
    void load_from_file(const std::string &path);
    void to_object(object &dest);

  private:
    std::vector<vector3_t> _vertices;
    std::vector<vector3_t> _normals;
    std::vector<vector2_t> _textures;
    std::list<std::list<vector3i_t>> _faces;
  };
}
