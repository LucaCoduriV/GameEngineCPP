#include <VertexArray.hpp>
#include <IndexBuffer.hpp>
#include <Renderer.hpp>
#include <Texture.hpp>
#include <GLFW/glfw3.h>
#include "TestLayer.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vendor/imgui/imgui.h>
#include <Events/EventDispatcher.hpp>
#include <Events/MouseEvent.hpp>
#include <functional>

/*
-----------------------------------------------------------------------------------
Nom du fichier  : TestLayer.cpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

TestLayer::TestLayer() : Layer("TestLayer"), cam(glm::vec3(0.0f, 0.0f, 0.0f)) {

}

void TestLayer::onAttach() {
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


   GLCall(glEnable(GL_DEPTH_TEST));
   GLCall(glEnable(GL_TEXTURE_2D));
   GLCall(glEnable(GL_BLEND));
   GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

   va = std::make_shared<VertexArray>();
   vb = std::make_shared<VertexBuffer>(positions, sizeof(positions));
   layout = std::make_shared<VertexBufferLayout>();
   texture = std::make_shared<Texture>(R"(res\texture\texture.png)");

   layout->push<float>(3);
   layout->push<float>(2);
   va->addBuffer(*vb, *layout);

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

   IndexBuffer ib(indices, 36);


   shader = std::make_shared<Shader>(
      R"(res\shaders\vertex.glsl)",
      R"(res\shaders\fragment.glsl)");

   shader->bind();
   texture->bind();
   shader->setInt("ourText", 0);

   VertexArray::unbind();
   Shader::unbind();
   VertexBuffer::unbind();
   IndexBuffer::unbind();

   renderer = std::make_shared<Renderer>();

}

void TestLayer::onDetach() {
   Layer::onDetach();
}

void TestLayer::onEvent(Event &event) {
   EventDispatcher dispatcher(event);
   dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(TestLayer::onMouseMove));
   dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(TestLayer::onKeyPressed));
   dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(TestLayer::onKeyReleased));
   dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(TestLayer::onScroll));
}

void TestLayer::onImGuiRender() {
   ImGui::Text("Camera controls");
   ImGui::SliderFloat3("translation", translationValues, -10.0f, 10.0f);
   ImGui::SliderFloat3("rotation", rotationsValues, 0.0f, 360.0f);
   ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
               1000.0f / ImGui::GetIO().Framerate,
               ImGui::GetIO().Framerate);
   ImGui::Render();
}

void TestLayer::onUpdate(float timeStamp) {

   if(forward){
      cam.processKeyboard(CameraMovement::FORWARD, timeStamp);
   }
   if(backward){
      cam.processKeyboard(CameraMovement::BACKWARD, timeStamp);
   }
   if(left){
      cam.processKeyboard(CameraMovement::LEFT, timeStamp);
   }
   if(right){
      cam.processKeyboard(CameraMovement::RIGHT, timeStamp);
   }

   float currentFrame = static_cast<float>(glfwGetTime());
   deltaTime = currentFrame - lastFrame;
   lastFrame = currentFrame;

   renderer->clear();
   texture->bind();
   shader->bind();

   float timeValue = glfwGetTime();
   float greenValue = sin(timeValue) / 2.0f + 0.5f;
   shader->setFloat("ourColor", greenValue);

   cam.onUpdate(*shader);

   for (unsigned int i = 0; i < 10; i++) {
      auto model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * static_cast<float>(i);
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      shader->setMat4f("u_model", model);
      renderer->draw(*va, *shader, 36);
   }
}

bool TestLayer::onMouseMove(MouseMovedEvent &event) {
   float xpos = static_cast<float>(event.GetX());
   float ypos = static_cast<float>(event.GetY());

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
   return true;
}

bool TestLayer::onKeyPressed(KeyPressedEvent &event) {
   if (event.GetKeyCode() == (KeyCode)Key::W && !event.IsRepeat())
      forward = true;
   if (event.GetKeyCode() == (KeyCode)Key::S && !event.IsRepeat())
      backward = true;
   if (event.GetKeyCode() == (KeyCode)Key::A && !event.IsRepeat())
      left = true;
   if (event.GetKeyCode() == (KeyCode)Key::D && !event.IsRepeat())
      right = true;

   return true;
}

bool TestLayer::onKeyReleased(KeyReleasedEvent &event) {
   if (event.GetKeyCode() == (KeyCode)Key::W)
      forward = false;
   if (event.GetKeyCode() == (KeyCode)Key::S)
      backward = false;
   if (event.GetKeyCode() == (KeyCode)Key::A)
      left = false;
   if (event.GetKeyCode() == (KeyCode)Key::D)
      right = false;

   return true;
}

bool TestLayer::onScroll(MouseScrolledEvent &event) {
   cam.processMouseScroll(static_cast<float>(event.GetYOffset()));
   return true;
}
