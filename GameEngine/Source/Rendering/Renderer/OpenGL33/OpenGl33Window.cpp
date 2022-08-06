/*
-----------------------------------------------------------------------------------
Nom du fichier  : OpenGl33Window.cpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <stdexcept>
#include <iostream>
#include "Rendering/Renderer/OpenGL33/OpenGl33Window.hpp"

void errorCallback(int error, const char *description) {
   throw std::runtime_error(std::string("Error glfw:") + description);
}

GE::OpenGl33Window::~OpenGl33Window() {
   release();
}

void GE::OpenGl33Window::initialize(const GE::SWindowCreateInfo &windowInfos) {
   std::cout << "Initializing the OpenGl 3.3 window ..." << std::endl;
   if (!glfwInit()) {
      throw std::runtime_error("Failed init glfw !");
   }

   glfwSetErrorCallback(errorCallback);
   glfwWindowHint(GLFW_SAMPLES, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   pWindow = glfwCreateWindow(windowInfos.windowWidth,
                              windowInfos.windowHeight,
                              windowInfos.windowTitle,
                              nullptr, nullptr);

   if (!pWindow) {
      glfwTerminate();
      throw std::runtime_error("Faile to create the window");
   }

   glfwMakeContextCurrent(pWindow);

   glewExperimental = GL_TRUE;

   if (glewInit() != GLEW_OK) {
      throw std::runtime_error("Failed to init Glew 3.3");
   }

   glfwSetInputMode(pWindow, GLFW_STICKY_KEYS, GL_TRUE);
   std::cout << "OpenGL 3.3 window initialized." << std::endl;
}

void GE::OpenGl33Window::release() {
   glfwTerminate();
   pWindow = nullptr;
   std::cout << "OpenGL 3.3 window released." << std::endl;
}
