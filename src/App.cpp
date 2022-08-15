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
#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_glfw_gl3.h>
#include <Events/EventDispatcher.hpp>


App::App(): window("Learning OpenGl", 600, 800) {

   ImGui::CreateContext();
   ImGui::StyleColorsDark();
   ImGui_ImplGlfwGL3_Init(window.getWindowHandler(), false);
   window.SetEventCallback(BIND_EVENT_FN(App::onEvent));
}

void App::run() {
   std::cout << "Loop running." << std::endl;
   while(running){
      float time = (float)glfwGetTime();
      float timeStep = time - lastFrameTime;
      lastFrameTime = time;

      for (auto layer : layers){
         layer->onUpdate(timeStep);
      }


      ImGui_ImplGlfwGL3_NewFrame();
      for (auto layer : layers){
         layer->onImGuiRender();
      }

      window.onUpdate();
   }
}

void App::onEvent(Event &e) {
   std::cout << e.toString() << std::endl;

   EventDispatcher dispatcher(e);
   dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::onWindowClose));
   dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(App::onWindowResize));

   for(auto* layer : layers){
      layer->onEvent(e);
   }
}

void App::pushLayer(Layer *layer) {
   layers.push_back(layer);
   layer->onAttach();
}

App::~App() {
   for (auto layer : layers){
      layer->onDetach();
   }
}

bool App::onWindowClose(WindowCloseEvent &e) {
   running = false;
   return true;
}

bool App::onWindowResize(WindowResizeEvent& e){

   if (e.getWidth() == 0 || e.getHeight() == 0)
   {
      minimized = true;
      return false;
   }

   minimized = false;
   return true;
}
