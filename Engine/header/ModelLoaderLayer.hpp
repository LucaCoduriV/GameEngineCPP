//
// Created by luca on 19/08/22.
//

#ifndef SANDBOX_MODELLOADERLAYER_HPP
#define SANDBOX_MODELLOADERLAYER_HPP


#include "Layer.hpp"
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
#include "Events/ApplicationEvent.hpp"
#include "definitions.hpp"
#include <Layer.hpp>
#include <ModelLoader/ModelLoader.hpp>

class ModelLoaderLayer : public Layer {
public:
   ModelLoaderLayer();

   void onAttach() override;
   void onDetach() override;
   void onEvent(Event &event) override;
   void onImGuiRender() override;
   void onUpdate(float timeStamp) override;
   bool onMouseMove(MouseMovedEvent& event);
   bool onKeyPressed(KeyPressedEvent& event);
   bool onKeyReleased(KeyReleasedEvent& event);
   bool onScroll(MouseScrolledEvent& event);
   bool onWindowResize(WindowResizeEvent& event);
private:
   std::shared_ptr<Shader> shader;
   std::shared_ptr<Renderer> renderer;

   Camera cam;

   GM::Ref<ModelLoader> ourModel;

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


#endif //SANDBOX_MODELLOADERLAYER_HPP
