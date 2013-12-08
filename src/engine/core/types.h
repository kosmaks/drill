#pragma once

namespace drill {

  typedef float coord_t;

  typedef char      int8_t;
  typedef short     int16_t;
  typedef int       int32_t;
  typedef long long int64_t;

  typedef unsigned char      uint8_t;
  typedef unsigned short     uint16_t;
  typedef unsigned int       uint32_t;
  typedef unsigned long long uint64_t;

  typedef struct {
    coord_t x, y;
    coord_t operator[](int i) { return ((coord_t*)this)[i]; }
  } vector2_t;

  typedef struct {
    coord_t x, y, z;
    coord_t operator[](int i) { return ((coord_t*)this)[i]; }
  } vector3_t;

  typedef struct {
    coord_t x, y, z, w;
    coord_t operator[](int i) { return ((coord_t*)this)[i]; }
  } vector4_t;

  typedef struct {
    vector3_t *vertices, *normals;
    vector2_t *textures;
    uint32_t count;

    void try_delete() {
      if (vertices) delete vertices;
      if (normals) delete vertices;
      if (textures) delete vertices;
    }
  } coordset_t;

}
