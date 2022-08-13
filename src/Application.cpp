#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Renderer.hpp>
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <VertexArray.hpp>
#include <cmath>
#include <Texture.hpp>


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
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
         -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
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

      ////////////////////////////////////////////////////////

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
         glfwPollEvents();

         renderer.clear();
         texture.bind();
         shader.bind();

         float timeValue = glfwGetTime();
         float greenValue = sin(timeValue) / 2.0f + 0.5f;
         shader.setFloat("ourColor", greenValue);

         renderer.draw(va, ib, shader);

         glfwSwapBuffers(window);
      }
   }

   glfwTerminate();
   return 0;
}