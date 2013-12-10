#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
//#include "glbridge_object.h"

using namespace drill;

//void glbridge_object::compile() {
  //LOG_DEBUG("Compiling GL object: " << current_target->triangles.count);
  //vertices = generate_vbo(current_target->triangles.vertices, 
               //sizeof(vector3_t) * current_target->triangles.count);
  //glVertexPointer(3, GL_FLOAT, 0, NULL);
//}

//void glbridge_object::draw() {
  //glRotatef(0.5, 1, 1, 0);
  //glColor3f(current_target->color.x, 
            //current_target->color.y, 
            //current_target->color.z);
  //glBindBuffer(GL_ARRAY_BUFFER, vertices);
  //glEnableClientState(GL_VERTEX_ARRAY);
  //glDrawArrays(GL_TRIANGLES, 0, current_target->triangles.count);
//}

//uint32_t glbridge_object::generate_vbo(void *pointer, uint32_t size) {
  //uint32_t vbo;
  //glGenBuffers(1, &vbo);
  //glBindBuffer(GL_ARRAY_BUFFER, vbo);
  //glBufferData(GL_ARRAY_BUFFER, size, pointer, GL_STATIC_DRAW);
  //return vbo;
//}
