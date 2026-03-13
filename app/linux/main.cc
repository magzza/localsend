#include "my_application.h"
#include <stdlib.h>
#include <stdio.h>

__attribute__((constructor))
static void setup_environment() {
    printf("[LocalSend-Hisi-Fix] 正在强制注入海思兼容性补丁 (Softpipe 最终模式)...\n");

    // 1. 锁定 X11 协议
    setenv("GDK_BACKEND", "x11", 1);
    
    // 2. 强制开启软件渲染
    setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);
    
    // 3. 核心改动：使用 softpipe 代替 llvmpipe
    // softpipe 是纯 C 编写的渲染器，不依赖 LLVM，虽然慢一点，但在任何乱七八糟的环境下都能出图
    setenv("GALLIUM_DRIVER", "softpipe", 1);
    
    // 4. 强制 GTK 的 GL 环境也走软件路径，防止黑屏
    setenv("GDK_GL", "software", 1);

    // 5. 降低 GL 版本需求到 3.3 (对 Flutter 绰绰有余)，提高初始化成功率
    setenv("MESA_GL_VERSION_OVERRIDE", "3.3", 1);
    setenv("MESA_GLSL_VERSION_OVERRIDE", "330", 1);
    
    // 6. 屏蔽海思私有驱动的干扰
    setenv("__GLX_VENDOR_LIBRARY_NAME", "mesa", 1);
}


int main(int argc, char** argv) {
  
  g_autoptr(MyApplication) app = my_application_new();
  return g_application_run(G_APPLICATION(app), argc, argv);
}
