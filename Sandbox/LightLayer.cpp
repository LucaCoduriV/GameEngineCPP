/*
-----------------------------------------------------------------------------------
Nom du fichier  : LightLayer.cpp
Auteur(s)       : lucac
Date creation   : 16.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "LightLayer.hpp"
#include <VertexArray.hpp>
#include <IndexBuffer.hpp>
#include <Renderer.hpp>
#include <Texture.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vendor/imgui/imgui.h>
#include <Events/EventDispatcher.hpp>
#include <Events/MouseEvent.hpp>
#include <functional>
#include <filesystem>

LightTestLayer::LightTestLayer() : Layer("LightLayer"),
                                   cam(glm::vec3(0.0f, 0.0f, 0.0f)) {

}

void LightTestLayer::onAttach() {
   const float positions[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
   };


   GLCall(glEnable(GL_DEPTH_TEST));
   GLCall(glEnable(GL_TEXTURE_2D));
   GLCall(glEnable(GL_BLEND));
   GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

   va = std::make_shared<VertexArray>();
   lightVa = std::make_shared<VertexArray>();
   vb = std::make_shared<VertexBuffer>(positions, sizeof(positions));
   layout = std::make_shared<VertexBufferLayout>();

   layout->push<float>(3);
   layout->push<float>(3);
   lightVa->addBuffer(*vb, *layout);
   va->addBuffer(*vb, *layout);



   shader = std::make_shared<Shader>(
      "res/shaders/light/normal/vertex.glsl",
      "res/shaders/light/normal/fragment.glsl");

   lightShader = std::make_shared<Shader>(
      "res/shaders/light/lightsource/vertex.glsl",
      "res/shaders/light/lightsource/fragment.glsl");

   VertexArray::unbind();
   Shader::unbind();
   VertexBuffer::unbind();
   IndexBuffer::unbind();

   renderer = std::make_shared<Renderer>();

}

void LightTestLayer::onUpdate(float timeStamp) {

   if (forward) {
      cam.processKeyboard(CameraMovement::FORWARD, timeStamp);
   }
   if (backward) {
      cam.processKeyboard(CameraMovement::BACKWARD, timeStamp);
   }
   if (left) {
      cam.processKeyboard(CameraMovement::LEFT, timeStamp);
   }
   if (right) {
      cam.processKeyboard(CameraMovement::RIGHT, timeStamp);
   }

   float currentFrame = static_cast<float>(glfwGetTime());
   deltaTime = currentFrame - lastFrame;
   lastFrame = currentFrame;

   renderer->clear();

   shader->bind();
   shader->setFloat("u_objectColor", objectColors[0], objectColors[1],
                    objectColors[2]);
   shader->setFloat("u_lightColor",  lightColors[0], lightColors[1], lightColors[2]);
   shader->setFloat("u_lightPos", lightSourcePos[0],
                    lightSourcePos[1],
                    lightSourcePos[2]);
   auto camPos = cam.getPosition();
   shader->setFloat("u_viewPos", camPos.x, camPos.y, camPos.z);

   cam.onUpdate(*shader);

   //cube 1
   auto model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
   shader->setMat4f("u_model", model);
   renderer->draw(*va, *shader, 36);

   //cube 2 (light source)
   lightShader->bind();
   cam.onUpdate(*lightShader);
   model = glm::translate(glm::mat4(1.0f), glm::vec3(lightSourcePos[0],
                                                     lightSourcePos[1],
                                                     lightSourcePos[2]));
   lightShader->setMat4f("u_model", model);
   lightShader->setFloat("u_lightColor",  lightColors[0], lightColors[1], lightColors[2]);
   renderer->draw(*lightVa, *lightShader, 36);
}

void LightTestLayer::onDetach() {
   Layer::onDetach();
}

void LightTestLayer::onEvent(Event &event) {
   EventDispatcher dispatcher(event);
   dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(LightTestLayer::onMouseMove));
   dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(LightTestLayer::onKeyPressed));
   dispatcher.dispatch<KeyReleasedEvent>(
      BIND_EVENT_FN(LightTestLayer::onKeyReleased));
   dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(LightTestLayer::onScroll));
}

void LightTestLayer::onImGuiRender() {
   ImGui::Text("Color controls");
   ImGui::ColorEdit3("ObjectColor", objectColors);
   ImGui::ColorEdit3("LightColor", lightColors);
   ImGui::SliderFloat3("Light Position", lightSourcePos, -10.0f, 10.0f);
   ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
               1000.0f / ImGui::GetIO().Framerate,
               ImGui::GetIO().Framerate);
   ImGui::Render();
}

bool LightTestLayer::onMouseMove(MouseMovedEvent &event) {
   float xpos = static_cast<float>(event.GetX());
   float ypos = static_cast<float>(event.GetY());

   if (firstMouse) {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
   }

   float xoffset = xpos - lastX;
   float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

   lastX = xpos;
   lastY = ypos;

   cam.processMouseMovement(xoffset, yoffset);
   return true;
}

bool LightTestLayer::onKeyPressed(KeyPressedEvent &event) {
   if (event.GetKeyCode() == (KeyCode) Key::W && !event.IsRepeat())
      forward = true;
   if (event.GetKeyCode() == (KeyCode) Key::S && !event.IsRepeat())
      backward = true;
   if (event.GetKeyCode() == (KeyCode) Key::A && !event.IsRepeat())
      left = true;
   if (event.GetKeyCode() == (KeyCode) Key::D && !event.IsRepeat())
      right = true;

   return true;
}

bool LightTestLayer::onKeyReleased(KeyReleasedEvent &event) {
   if (event.GetKeyCode() == (KeyCode) Key::W)
      forward = false;
   if (event.GetKeyCode() == (KeyCode) Key::S)
      backward = false;
   if (event.GetKeyCode() == (KeyCode) Key::A)
      left = false;
   if (event.GetKeyCode() == (KeyCode) Key::D)
      right = false;

   return true;
}

bool LightTestLayer::onScroll(MouseScrolledEvent &event) {
   cam.processMouseScroll(static_cast<float>(event.GetYOffset()));
   return true;
}
