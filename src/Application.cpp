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

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
   glViewport(0, 0, width, height);
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
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   std::cout << glGetString(GL_VERSION) << std::endl;


   {
      /////////////////////////// SETUP //////////////////////

      const float positions[] = {
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_TEXTURE_2D);
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

      glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                    (float) screenWidth / (float) screenHeight,
                                    0.1f, 100.0f);
      Camera cam(projection);


      float translationValues[3] = {0, 0, -3.0f};
      float rotationsValues[3] = {0, 0, 0};

      Shader shader(
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\vertex.glsl)",
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\fragment.glsl)");

      shader.bind();
      texture.bind();
      shader.setInt("ourText", 0);
      cam.init(shader);


      VertexArray::unbind();
      Shader::unbind();
      VertexBuffer::unbind();
      IndexBuffer::unbind();

      Renderer renderer;

      ImGui::CreateContext();
      ImGui::StyleColorsDark();
      ImGui_ImplGlfwGL3_Init(window, true);

      bool show_demo_window = true;
      bool show_another_window = false;
      ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


      ////////////////////////////////////////////////////////

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
         glfwPollEvents();
         ImGui_ImplGlfwGL3_NewFrame();

         glm::mat4 model = glm::mat4(1.0f);
         model = glm::rotate(model, glm::radians(-55.0f),
                             glm::vec3(1.0f, 0.0f, 0.0f));

//         glm::mat4 view = glm::mat4(1.0f);
//         view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));



         renderer.clear();
         texture.bind();
         shader.bind();

         float timeValue = glfwGetTime();
         float greenValue = sin(timeValue) / 2.0f + 0.5f;
         shader.setFloat("ourColor", greenValue);
         shader.setMat4f("u_model", model);

         cam.setXTranslation(translationValues[0]);
         cam.setYTranslation(translationValues[1]);
         cam.setZTranslation(translationValues[2]);
         cam.setXRotation(rotationsValues[0]);
         cam.setYRotation(rotationsValues[1]);
         cam.setZRotation(rotationsValues[2]);
         cam.onUpdate(shader);

         //renderer.draw(va, ib, shader);
         renderer.draw(va, shader);

         {
            ImGui::Text("Camera controls");
            ImGui::SliderFloat3("translation", translationValues, -10.0f, 10.0f);
            ImGui::SliderFloat3("rotation", rotationsValues, 0.0f, 360.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
         }


         ImGui::Render();

         glfwSwapBuffers(window);
      }
   }

   ImGui_ImplGlfwGL3_Shutdown();
   glfwTerminate();
   return 0;
}