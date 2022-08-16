/*
-----------------------------------------------------------------------------------
Nom du fichier  : LightLayer.hpp
Auteur(s)       : lucac
Date creation   : 16.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_LIGHTLAYER_HPP
#define SANDBOX_LIGHTLAYER_HPP

#include <Camera.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <Events/MouseEvent.hpp>
#include <Events/KeyEvent.hpp>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include <Layer.hpp>

class LightTestLayer : public Layer {
public:
   LightTestLayer();

   void onAttach() override;
   void onDetach() override;
   void onEvent(Event &event) override;
   void onImGuiRender() override;
   void onUpdate(float timeStamp) override;
   bool onMouseMove(MouseMovedEvent& event);
   bool onKeyPressed(KeyPressedEvent& event);
   bool onKeyReleased(KeyReleasedEvent& event);
   bool onScroll(MouseScrolledEvent& event);
private:
   std::shared_ptr<VertexArray> va;
   std::shared_ptr<VertexArray> lightVa;
   std::shared_ptr<VertexBuffer> vb;
   std::shared_ptr<VertexBufferLayout> layout;
   std::shared_ptr<Shader> shader;
   std::shared_ptr<Shader> lightShader;
   std::shared_ptr<Renderer> renderer;

   Camera cam;
   constexpr static glm::vec3 cubePositions[] = {
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

   float objectColors[3] = {1.0f, 0.5f, 0.31f};
   float lightColors[3] = {1.0f, 1.0f, 1.0f};

   float deltaTime = 0.0f;
   float lastFrame = 0.0f;

   float lastX = 800 / 2.0f;
   float lastY = 600 / 2.0f;
   bool firstMouse = true;

   bool forward = false;
   bool backward = false;
   bool right = false;
   bool left = false;
};
#endif //SANDBOX_LIGHTLAYER_HPP
