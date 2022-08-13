#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Renderer.hpp>
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <VertexArray.hpp>
#include <cmath>


int main(void) {
   GLFWwindow *window;

   /* Initialize the library */
   if (!glfwInit())
      return -1;

   /* Create a windowed mode window and its OpenGL context */
   window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

   std::cout << glGetString(GL_VERSION) << std::endl;



   {
      /////////////////////////// SETUP //////////////////////

      float positions[] = {
         -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f, 0.5f, 0.0f,
         -0.5f, 0.5f, 0.0f
      };

      unsigned int indices[] = {
         0, 1, 2,
         2, 3, 0
      };

      VertexArray va;
      VertexBuffer vb(positions, 3 * 4 * sizeof(float));
      VertexBufferLayout layout;

      layout.push<float>(3);
      va.addBuffer(vb, layout);

      IndexBuffer ib(indices, 6);

      Shader shader(
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\vertex.glsl)",
         R"(B:\Users\lucac\Documents\GitHub\GameEngine\res\shaders\fragment.glsl)");

      VertexArray::unbind();
      Shader::unbind();
      VertexBuffer::unbind();
      IndexBuffer::unbind();

      ////////////////////////////////////////////////////////

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
         glfwPollEvents();
         GLCall(glClear(GL_COLOR_BUFFER_BIT));

         shader.bind();

         float timeValue = glfwGetTime();
         float greenValue = sin(timeValue) / 2.0f + 0.5f;
         shader.setFloat("ourColor", greenValue);

         va.bind();
         ib.bind();

         GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

         glfwSwapBuffers(window);
      }
   }

   glfwTerminate();
   return 0;
}