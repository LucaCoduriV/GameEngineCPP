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
#include "Rendering/Renderer/OpenGL33/OpenGL33Window.hpp"


void errorCallback(int error, const char *description) {
   throw std::runtime_error(
      std::string("Error glfw:") + std::to_string(error) + " - "
                                                           "" + description);
}

GE::OpenGL33Window::~OpenGL33Window() {
   release();
}

void GE::OpenGL33Window::initialize(const GE::SWindowCreateInfo &windowInfos) {
   if (isInitialized) release();

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
   isInitialized = true;
   std::cout << "OpenGL 3.3 window initialized." << std::endl;
}

void GE::OpenGL33Window::release() {
   if (!isInitialized) return;

   glfwTerminate();
   pWindow = nullptr;
   isInitialized = false;
   std::cout << "OpenGL 3.3 window released." << std::endl;
}
