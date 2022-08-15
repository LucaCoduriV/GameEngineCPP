/*
-----------------------------------------------------------------------------------
Nom du fichier  : App.cpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <iostream>
#include "App.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Renderer.hpp>
#include <Texture.hpp>
#include <Camera.hpp>

App::App(): window("Learning OpenGl", 600, 800) {
   window.SetEventCallback(BIND_EVENT_FN(App::onEvent));
   run();
}

[[noreturn]] void App::run() {
   std::cout << "Loop running." << std::endl;
   /////// SETUP /////////
   Camera cam(glm::vec3(0.0f, 0.0f, 0.0f));
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

   // timing
   float deltaTime = 0.0f;	// time between current frame and last frame
   float lastFrame = 0.0f;

   ///////////////////////



   while(running){
      float time = (float)glfwGetTime();
      float timeStep = time - lastFrameTime;
      lastFrameTime = time;

      ///////////////////////

      glfwPollEvents();
      float currentFrame = static_cast<float>(glfwGetTime());
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

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

      ///////////////////////


      window.onUpdate();
   }
}

void App::onEvent(Event &e) {
   std::cout << e.toString() << std::endl;
}
