#include <GL/glew.h>
#include "vendor/imgui/imgui_impl_glfw_gl3.h"
#include "vendor/imgui/imgui.h"
#include "Camera.hpp"


#include <GLFW/glfw3.h>
#include <iostream>
#include <Renderer.hpp>
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <VertexArray.hpp>
#include <cmath>
#include <Texture.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <App.hpp>
#include <main/TestLayer.hpp>

const int screenWidth = 800;
const int screenHeight = 600;


Camera cam(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;

bool escapePressed = false;
bool enableIamGui = false;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
   glViewport(0, 0, width, height);
}

void processKeys(GLFWwindow *window, float deltaTime){
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      cam.processKeyboard(CameraMovement::FORWARD, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      cam.processKeyboard(CameraMovement::BACKWARD, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      cam.processKeyboard(CameraMovement::LEFT, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      cam.processKeyboard(CameraMovement::RIGHT, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_PRESS)
      escapePressed = true;
   if (escapePressed && glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_RELEASE){
      escapePressed = false;
      enableIamGui = !enableIamGui;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   }

}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
   float xpos = static_cast<float>(xposIn);
   float ypos = static_cast<float>(yposIn);

   if (firstMouse)
   {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
   }

   float xoffset = xpos - lastX;
   float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

   lastX = xpos;
   lastY = ypos;

   cam.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
{
   cam.processMouseScroll(static_cast<float>(yOffset));
}

int main(){
   auto* app = new App();
   TestLayer layer;
   app->pushLayer(&layer);
   app->run();
   delete app;
}