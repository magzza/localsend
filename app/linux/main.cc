#include "my_application.h"
#include <stdlib.h>

int main(int argc, char** argv) {
  
  setenv("GDK_BACKEND", "x11", 1);
  setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);
  setenv("MESA_LOADER_DRIVER_OVERRIDE", "llvmpipe", 1);
  setenv("MESA_GL_VERSION_OVERRIDE", "4.5", 1); 
  setenv("MESA_GLSL_VERSION_OVERRIDE", "450", 1); 
  setenv("__GLX_VENDOR_LIBRARY_NAME", "mesa", 1); 
  
  g_autoptr(MyApplication) app = my_application_new();
  return g_application_run(G_APPLICATION(app), argc, argv);
}
