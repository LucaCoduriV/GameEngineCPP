/*
-----------------------------------------------------------------------------------
Nom du fichier  : GameEngine.cpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <Rendering/Rasterization/RasterizationEngine.hpp>
#include <stdexcept>
#include <iostream>
#include "GameEngine.hpp"

namespace GE {
   GameEngine::~GameEngine() {
      release();
   }

   void GameEngine::Initialize(const GE::SGameEngineCreateInfo &createInfo) {
      if (isInitialized) release();

      switch (createInfo.pRenderingEngineCreateInfo->renderingEnginyType) {
         case ERenderingEnginyType::Rasterization:
            pRenderingEngine = new RasterizationEngine();
            break;
         case ERenderingEnginyType::RayTracingCPU:
            throw std::runtime_error("RayTracingCPU is not implemented.");
         case ERenderingEnginyType::RayTracingGPU:
            throw std::runtime_error("RayTracingGPU is not implemented.");
      }

      if (!pRenderingEngine)
         throw std::bad_alloc();

      pRenderingEngine->initialize(*createInfo.pRenderingEngineCreateInfo);

      isInitialized = true;

      std::cout << "Game engine initialized." << std::endl;
   }

   void GameEngine::release() {
      if (!isInitialized) return;

      if (pRenderingEngine) {
         delete pRenderingEngine;
         pRenderingEngine = nullptr;
      }
      isInitialized = false;

      std::cout << "Game engine released." << std::endl;
   }

   void GameEngine::run() {
      if (!isInitialized)
         throw std::runtime_error("Game engine not initialized.");

      GLFWwindow *pWindow = pRenderingEngine->getRenderer()->getWindow()
         ->getHandle();

      // Timer
      double lag = 0.0;
      double previous = glfwGetTime();
      const double SECONDS_PER_UPDATE = 1.0 / 60.0;

      while (!glfwWindowShouldClose(pWindow)
             && glfwGetKey(pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

         double current = glfwGetTime();
         double elapsed = current - previous;
         previous = current;

         lag += elapsed;
         glfwPollEvents();

         while(lag >= SECONDS_PER_UPDATE){
            // Game logic
            lag -= SECONDS_PER_UPDATE;
         }

         // Rendering
         pRenderingEngine->render(static_cast<float>(lag / SECONDS_PER_UPDATE));
      }

      glfwTerminate();
   }
}




