#include <sstream>
#include <fstream>
#include "file_system.h"

using namespace drill;

std::string file_system::read_text_file(const std::string &path) {
  std::stringstream dest;
  std::ifstream src(path.c_str());
  std::string temp;

  while (src.good()) {
    getline(src, temp);
    dest << temp << std::endl;
  }

  src.close();
  return dest.str();
}
