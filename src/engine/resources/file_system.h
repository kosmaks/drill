#pragma once

#include <string>

namespace drill {
  class file_system {
  public:
    static std::string read_text_file(const std::string &path);
  };
}
