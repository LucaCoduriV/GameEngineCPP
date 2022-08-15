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
#include <Events/MouseEvent.hpp>
#include <Events/ApplicationEvent.hpp>
#include <Events/KeyEvent.hpp>
#include <vendor/imgui/imgui_impl_glfw_gl3.h>
#include "Window.hpp"

static void GLFWErrorCallback(int error, const char *description) {
   std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

unsigned int Window::getHeight() const {
   return height;
}

unsigned int Window::getWidth() const {
   return width;
}

Window::Window(std::string title, unsigned int height, unsigned int width) : height
                                                                                (height),
                                                                             width(
                                                                                width),
                                                                             title(
                                                                                move(
                                                                                   title)) {
   data.title = title;
   data.height = height;
   data.width = width;

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

   glfwSetWindowUserPointer(window, &data);

   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetErrorCallback(GLFWErrorCallback);

   glfwSetFramebufferSizeCallback(window,
                                  [](GLFWwindow *window, int width, int height) {
                                     glViewport(0, 0, width, height);
                                     WindowData &_data = *(WindowData *) glfwGetWindowUserPointer(
                                        window);
                                     _data.width = static_cast<unsigned int>(width);
                                     _data.height = static_cast<unsigned int>(height);

                                     WindowResizeEvent event(
                                        static_cast<unsigned int>(width),
                                        static_cast<unsigned int>(height));
                                     _data.eventCallback(event);
                                  });

   glfwSetCursorPosCallback(window, [](GLFWwindow *_window, double xPosIn, double
   yPosIn) {
      const WindowData &_data = *(WindowData *) glfwGetWindowUserPointer(_window);
      MouseMovedEvent event((float) xPosIn, (float) yPosIn);
      _data.eventCallback(event);
   });

   glfwSetWindowCloseCallback(window, [](GLFWwindow *_window) {
      const WindowData &_data = *(WindowData *) glfwGetWindowUserPointer(_window);
      WindowCloseEvent event;
      _data.eventCallback(event);
   });

   glfwSetMouseButtonCallback(window, [](GLFWwindow *_window, int button, int
   action, int mods) {
      ImGui_ImplGlfwGL3_MouseButtonCallback(_window, button, action, mods);
      const WindowData &_data = *(WindowData *) glfwGetWindowUserPointer(_window);

      switch (action) {
         case GLFW_PRESS: {
            MouseButtonPressedEvent event((MouseCode) button);
            _data.eventCallback(event);
            break;
         }
         case GLFW_RELEASE: {
            MouseButtonReleasedEvent event((MouseCode) button);
            _data.eventCallback(event);
            break;
         }
      }
   });

   glfwSetScrollCallback(window, [](GLFWwindow *_window, double xOffset, double
   yOffset) {
      ImGui_ImplGlfwGL3_ScrollCallback(_window, xOffset, yOffset);
      const WindowData &_data = *(WindowData *) glfwGetWindowUserPointer(_window);

      MouseScrolledEvent event((float) xOffset, (float) yOffset);
      _data.eventCallback(event);
   });

   glfwSetKeyCallback(window, [](GLFWwindow *_window, int key, int scancode, int
   action, int mods) {
      ImGui_ImplGlfwGL3_KeyCallback(_window, key, scancode, action, mods);
      const WindowData &_data = *(WindowData *) glfwGetWindowUserPointer(_window);

      switch (action) {
         case GLFW_PRESS: {
            KeyPressedEvent event((KeyCode) key);
            _data.eventCallback(event);
            break;
         }
         case GLFW_RELEASE: {
            KeyReleasedEvent event((KeyCode) key);
            _data.eventCallback(event);
            break;
         }
         case GLFW_REPEAT: {
            KeyPressedEvent event((KeyCode) key, true);
            _data.eventCallback(event);
            break;
         }
      }
   });

   glfwSetCharCallback(window, [](GLFWwindow *_window, unsigned int keycode) {
      ImGui_ImplGlfwGL3_CharCallback(_window, keycode);
      WindowData const &_data = *(WindowData *) glfwGetWindowUserPointer(_window);

      KeyTypedEvent event((KeyCode) keycode);
      _data.eventCallback(event);
   });

}

void Window::onUpdate() {
   glfwSwapBuffers(window);
}

void Window::SetEventCallback(const Window::EventCallbackFn &callback) {
   data.eventCallback = callback;
}

GLFWwindow *Window::getWindowHandler() const {
   return window;
}
