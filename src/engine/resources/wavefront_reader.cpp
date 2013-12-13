#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include <cctype>
#include <locale>
#include <algorithm>
#include "engine/core/types.h"
#include "engine/core/app.h"
#include "wavefront_reader.h"

using namespace drill;

vector3i_t parse_face(std::string &mem) {
  vector3i_t storage = { 0, 0, 0 };
  std::stringstream stream(mem);
  char slash;
  stream >> storage.x;
  if (stream.rdbuf()->in_avail()) {
    stream >> slash;
    stream << '0';
    if (stream.rdbuf()->in_avail()) {
      stream >> storage.y;
      if (stream.rdbuf()->in_avail()) {
        stream >> slash;
        if (stream.rdbuf()->in_avail()) {
          stream >> storage.z;
        }
      }
    }
  }
  return storage;
}

void wavefront_reader::load_from_file(const std::string &path) {
  std::ifstream stream(path.c_str());
  
  std::string mem;
  vector3_t vector3;
  vector2_t vector2;

  typedef enum {
    WAITING,
    SKIP_LINE,
    COMMAND,
    READ_VERTEX,
    READ_TEXTURE,
    READ_NORMAL,
    READ_FACE,
  } state_t;

  state_t state = WAITING;

  _vertices.clear();
  _textures.clear();
  _normals.clear();
  _faces.clear();

  while (stream.good()) {
    switch (state) {
      case WAITING:
        stream >> mem;
        mem.erase(mem.begin(), // trim left
          std::find_if(mem.begin(), mem.end(), [](int x) { return x != ' '; }));
        state = (mem[0] == '#') ? SKIP_LINE : COMMAND;
        break;

      case SKIP_LINE:
        getline(stream, mem);
        state = WAITING;
        break;

      case COMMAND:
        state = (mem == "v")    ? READ_VERTEX :
                (mem == "vt")   ? READ_TEXTURE :
                (mem == "vn")   ? READ_NORMAL :
                (mem == "f")    ? READ_FACE :
                (mem == "\n" || 
                 mem == "\r" || 
                 mem == "\r\n") ? COMMAND :
                                  SKIP_LINE;
        break;

      case READ_VERTEX:
        stream >> vector3.x;
        stream >> vector3.y;
        stream >> vector3.z;
        _vertices.push_back(vector3);
        state = SKIP_LINE;
        break;

      case READ_TEXTURE:
        stream >> vector2.x;
        stream >> vector2.y;
        _textures.push_back(vector2);
        state = SKIP_LINE;
        break;

      case READ_NORMAL:
        stream >> vector3.x;
        stream >> vector3.y;
        stream >> vector3.z;
        _normals.push_back(vector3);
        state = SKIP_LINE;
        break;

      case READ_FACE:
        getline(stream, mem);
        std::stringstream facestr(mem);
        std::string temp;
        std::list<vector3i_t> face;
        while (facestr.rdbuf()->in_avail()) {
          facestr >> temp;
          face.push_back(parse_face(temp));
        }
        _faces.push_back(face);
        state = WAITING;
        break;
    }
  }

  stream.close();
}

object wavefront_reader::to_object() {
  object obj(3 * std::count_if(_faces.begin(), _faces.end(), 
      [](std::list<vector3i_t>& vec) { return vec.size() == 3; }));

  vector2_t zero2 = { 0, 0 };
  vector3_t zero3 = { 0, 0, 0 };
  
  uint32_t i = 0;
  for (std::list<vector3i_t>& vec : _faces) {
    if (vec.size() == 3) {
      for (vector3i_t& descr : vec) {
        obj.get_triangles(i)->vertex = _vertices[descr.x-1];
        obj.get_triangles(i)->texture = (descr.y > 0) ? _textures[descr.y-1] : zero2;
        obj.get_triangles(i)->normal = (descr.z > 0) ? _normals[descr.z-1] : zero3;
        i += 1;
      }
    }
  }
  
  return obj;
}
