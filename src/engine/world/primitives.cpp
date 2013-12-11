#include "primitives.h"

using namespace drill;

primitive::~primitive() {
  triangles.try_delete();
}

object_square::object_square() : primitive() {
  triangles.count = 6;
  triangles.vertices = new vector3_t[6] {
    { -0.5,  0.5, -1.0 },
    { -0.5, -0.5, -1.0 },
    {  0.5, -0.5, -1.0 },
    {  0.5,  0.5, -1.0 },
    { -0.5,  0.5, -1.0 },
    {  0.5, -0.5, -1.0 },
  };
}
