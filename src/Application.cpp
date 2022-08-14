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

void imGuiInit(GLFWwindow *window){
   ImGui::CreateContext();
   ImGui::StyleColorsDark();
   ImGui_ImplGlfwGL3_Init(window, true);
}

void imGuiDraw(float *translationValues, float *rotationsValues) {
   ImGui::Text("Camera controls");
   ImGui::SliderFloat3("translation", translationValues, -10.0f, 10.0f);
   ImGui::SliderFloat3("rotation", rotationsValues, 0.0f, 360.0f);
   ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
               1000.0f / ImGui::GetIO().Framerate,
               ImGui::GetIO().Framerate);
   ImGui::Render();
}


int main(void) {
   GLFWwindow *window;

   /* Initialize the library */
   if (!glfwInit())
      return -1;

   /* Create a windowed mode window and its OpenGL context */
   window = glfwCreateWindow(screenWidth, screenHeight, "Learn OpenGL", nullptr,
                             nullptr);
   if (!window) {
      glfwTerminate();
      return -1;
   }

   /* Make the window's context current */
   glfwMakeContextCurrent(window);

   if (glewInit() != GLEW_OK) {
      std::cerr << "Error glewInit" << std::endl;
      return 0;
   }

   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSetCursorPosCallback(window, mouse_callback);
   glfwSetScrollCallback(window, scroll_callback);
   std::cout << glGetString(GL_VERSION) << std::endl;


   {
      /////////////////////////// SETUP //////////////////////

      const float positions[] = {
         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
      };

      const unsigned int indices[] = {
         // front
         0, 1, 2,
         2, 3, 0,
         // right
         1, 5, 6,
         6, 2, 1,
         // back
         7, 6, 5,
         5, 4, 7,
         // left
         4, 0, 3,
         3, 7, 4,
         // bottom
         4, 5, 1,
         1, 0, 4,
         // top
         3, 2, 6,
         6, 7, 3
      };

      glm::vec3 cubePositions[] = {
         glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3(2.0f, 5.0f, -15.0f),
         glm::vec3(-1.5f, -2.2f, -2.5f),
         glm::vec3(-3.8f, -2.0f, -12.3f),
         glm::vec3(2.4f, -0.4f, -3.5f),
         glm::vec3(-1.7f, 3.0f, -7.5f),
         glm::vec3(1.3f, -2.0f, -2.5f),
         glm::vec3(1.5f, 2.0f, -2.5f),
         glm::vec3(1.5f, 0.2f, -1.5f),
         glm::vec3(-1.3f, 1.0f, -1.5f)
      };

      GLCall(glEnable(GL_DEPTH_TEST));
      GLCall(glEnable(GL_TEXTURE_2D));
      GLCall(glEnable(GL_BLEND));
      GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

      VertexArray va;
      VertexBuffer vb(positions, sizeof(positions));
      VertexBufferLayout layout;
      Texture texture("B:\\Users\\lucac\\Documents\\GitHub\\GameEngine\\res"
                      "\\texture\\texture.png");

      layout.push<float>(3);
      layout.push<float>(2);
      va.addBuffer(vb, layout);

      IndexBuffer ib(indices, 36);





      float translationValues[3] = {0, 0, -3.0f};
      float rotationsValues[3] = {0, 0, 0};

      Shader shader(
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\vertex.glsl)",
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\fragment.glsl)");

      shader.bind();
      texture.bind();
      shader.setInt("ourText", 0);


      VertexArray::unbind();
      Shader::unbind();
      VertexBuffer::unbind();
      IndexBuffer::unbind();

      Renderer renderer;

      imGuiInit(window);
      auto& io = ImGui::GetIO();

      ////////////////////////////////////////////////////////

      // timing
      float deltaTime = 0.0f;	// time between current frame and last frame
      float lastFrame = 0.0f;

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
         glfwPollEvents();
         float currentFrame = static_cast<float>(glfwGetTime());
         deltaTime = currentFrame - lastFrame;
         lastFrame = currentFrame;
         processKeys(window, deltaTime);



         renderer.clear();
         texture.bind();
         shader.bind();

         float timeValue = glfwGetTime();
         float greenValue = sin(timeValue) / 2.0f + 0.5f;
         shader.setFloat("ourColor", greenValue);

         cam.onUpdate(shader);

         for (unsigned int i = 0; i < 10; i++) {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * static_cast<float>(i);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4f("u_model", model);
            renderer.draw(va, shader, 36);
         }
         if(enableIamGui){
            ImGui_ImplGlfwGL3_NewFrame();
            imGuiDraw(translationValues, rotationsValues);
         }



         glfwSwapBuffers(window);
      }
   }

   ImGui_ImplGlfwGL3_Shutdown();
   glfwTerminate();
   return 0;
}