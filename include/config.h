#ifndef CONFIG_H
#define CONFIG_H

#ifdef GUI_ON
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif /* defined(GUI_ON) */

#if defined(_WIN32)
#define SHADPATH "C:\\Users\\Will\\source\\gltest\\shaders\\"
#define TEXPATH "C:\\Users\\Will\\source\\gltest\\texture\\"
#define MDLPATH "C:\\Users\\Will\\source\\gltest\\model\\"
#elif defined(linux) /* defined(_WIN32) */
#define SHADPATH "/home/willbonner/Git_Repos/gltest/shaders/"
#define TEXPATH "/home/willbonner/Git_Repos/gltest/texture/"
#define MDLPATH "/home/willbonner/Git_Repos/gltest/model/"
#endif /* defined(linux) */

#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define ASPECT_RATIO (float)SCR_WIDTH/(float)SCR_HEIGHT

#define GL_VERSION_MAJOR 3
#define GL_VERSION_MINOR 3

#endif