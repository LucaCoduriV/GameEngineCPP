/*
-----------------------------------------------------------------------------------
Nom du fichier  : Window.cpp
Auteur(s)       : lucac
Date creation   : 14.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <stdexcept>
#include <iostream>
#include "Window.hpp"

static void GLFWErrorCallback(int error, const char* description)
{
   std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

unsigned int Window::getHeight() const {
   return height;
}

unsigned int Window::getWidth() const {
   return width;
}

Window::Window(std::string title, unsigned int height, unsigned int width) : height
(height), width(width), title(move(title)) {
/* Initialize the library */
   if (!glfwInit())
      throw std::runtime_error("Error on glfw init.");

   /* Create a windowed mode window and its OpenGL context */
   window = glfwCreateWindow((int) width, (int) height, this->title.c_str(),
                             nullptr, nullptr);
   if (!window) {
      glfwTerminate();
      throw std::runtime_error("Error on window creation.");
   }

   /* Make the window's context current */
   glfwMakeContextCurrent(window);

   if (glewInit() != GLEW_OK) {
      throw std::runtime_error("Error on glewInit.");
   }

   std::cout << "Window successfully created. Running on OpenGL version : "
             << glGetString(GL_VERSION) << std::endl;

   glfwSetErrorCallback(GLFWErrorCallback);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
   glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPosIn, double
   yPosIn){

   });
   glfwSetScrollCallback(window, scrollCallback);

}

void Window::mouseCallback(GLFWwindow *window, double xPosIn, double yPosIn) {

}

void Window::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {

}

void Window::keyboardCallback(GLFWwindow *window, float deltaTime) {

}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
   glViewport(0, 0, width, height);
}

void Window::onUpdate() {
   glfwSwapBuffers(window);
}

void Window::SetEventCallback(const Window::EventCallbackFn &callback) {
   eventCallback = callback;
}
