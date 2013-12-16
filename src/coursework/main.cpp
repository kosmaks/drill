#include "engine/core.h"
#include "engine/world.h"
#include "engine/views.h"
#include "engine/resources.h"

#include "scenes/workbench.h"

int main(int argc, char **argv) {

  // Init application
  drill::application app;
  drill::field<drill::platform> platform;

  // Setting up platform
  if (argc >= 2 && std::string(argv[1]) == "opengl") {
#ifdef OPENGL
    drill::glplatform *gl = new drill::glplatform();
    platform = gl;
#endif
  } else {
#ifdef DIRECTX
    drill::dxplatform *dx = new drill::dxplatform();
    platform = dx;
#endif
  }

  // Init renderer
  drill::renderer &renderer = platform().require<drill::renderer>();
  app.add_service(renderer);
  
  // Set first scene
  workbench_scene scene(platform());
  renderer.use_scene(scene);

  // Running
  app.run();

  // Cleaning up
  delete &platform();
  return 0;
}
