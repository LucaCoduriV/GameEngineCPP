#include <GL/glew.h>
#include "vendor/imgui/imgui_impl_glfw_gl3.h"
#include "vendor/imgui/imgui.h"



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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

int main(void) {
   GLFWwindow *window;

   /* Initialize the library */
   if (!glfwInit())
      return -1;

   /* Create a windowed mode window and its OpenGL context */
   window = glfwCreateWindow(720, 480, "Hello World", NULL, NULL);
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

      float positions[] = {
         200.0f,  200.0f, 0.0f,   1.0f, 1.0f, // top right
         200.0f, 100.0f, 0.0f,   1.0f, 0.0f, // bottom right
         100.0f, 100.0f, 0.0f,   0.0f, 0.0f, // bottom left
         100.0f,  200.0f, 0.0f,   0.0f, 1.0f  // top left
      };

      unsigned int indices[] = {
         0, 1, 3,
         1, 2, 3
      };

      glEnable(GL_TEXTURE_2D);
      GLCall(glEnable(GL_BLEND));
      GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

      VertexArray va;
      VertexBuffer vb(positions, 5 * 4 * sizeof(float));
      VertexBufferLayout layout;
      Texture texture("B:\\Users\\lucac\\Documents\\GitHub\\GameEngine\\res"
                      "\\texture\\texture.png");

      layout.push<float>(3);
      layout.push<float>(2);
      va.addBuffer(vb, layout);

      IndexBuffer ib(indices, 6);

      glm::mat4 proj = glm::ortho(0.0f, 720.0f, 0.0f, 480.0f, -1.0f, 1.0f);

      Shader shader(
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\vertex.glsl)",
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\fragment.glsl)");

      shader.bind();
      texture.bind();
      shader.setInt("ourText", 0);
      shader.setMat4f("u_mvp", proj);

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

         renderer.clear();
         texture.bind();
         shader.bind();

         float timeValue = glfwGetTime();
         float greenValue = sin(timeValue) / 2.0f + 0.5f;
         shader.setFloat("ourColor", greenValue);

         renderer.draw(va, ib, shader);

         {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
            if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
               show_demo_window ^= 1;
            if (ImGui::Button("Another Window"))
               show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
         }
         if (show_another_window)
         {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            ImGui::End();
         }
         if (show_demo_window)
         {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
            ImGui::ShowDemoWindow(&show_demo_window);
         }


         ImGui::Render();

         glfwSwapBuffers(window);
      }
   }

   ImGui_ImplGlfwGL3_Shutdown();
   glfwTerminate();
   return 0;
}