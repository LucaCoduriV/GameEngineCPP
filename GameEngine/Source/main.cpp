#include <iostream>
#include <cstdlib>
#include "Rendering/Renderer/OpenGL33/OpenGl33Window.hpp"


int main() {

   GE::SWindowCreateInfo windowInfos = {};
   windowInfos.windowTitle = "GameEngine";
   windowInfos.windowHeight = 720;
   windowInfos.windowWidth = 1280;

   GE::OpenGl33Window openGLWindow;

   try{
      openGLWindow.initialize(windowInfos);
   }catch (const std::runtime_error& error){
      std::cerr << "Exception: " << error.what() << std::endl;
      return EXIT_FAILURE;
   }


   auto pWindow = openGLWindow.getHandle();

   while (!glfwWindowShouldClose(pWindow)
          && glfwGetKey(pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

      // Draw Loop

      glfwSwapBuffers(pWindow);
      glfwPollEvents();
   }

   glfwTerminate();

   return EXIT_SUCCESS;
}
