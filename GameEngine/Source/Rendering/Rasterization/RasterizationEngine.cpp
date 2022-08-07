/*
-----------------------------------------------------------------------------------
Nom du fichier  : RasterizationEngine.cpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <stdexcept>
#include <Rendering/Renderer/OpenGL33/OpenGL33Renderer.hpp>
#include <iostream>
#include "Rendering/Rasterization/RasterizationEngine.hpp"

namespace GE {
   void RasterizationEngine::initialize(
      const GE::SRenderingEngineCreateInfo &renderingEngineCreateInfo) {
      if(isInitialized) release();

      switch (renderingEngineCreateInfo.pRendererCreateInfo->rendererType) {
         case ERendererType::Opengl33:
            pRenderer = new OpenGL33Renderer();
            break;
         case ERendererType::OpenGL45:
            throw std::runtime_error("OpenGL 4.5 currently not supported");
         case ERendererType::Vulkan:
            throw std::runtime_error("Vulkan currently not supported");
      }

      if(!pRenderer){
         throw std::bad_alloc();
      }

      isInitialized = true;
      pRenderer->initialize(*renderingEngineCreateInfo.pRendererCreateInfo);

      std::cout << "Rasterization engine initialized." << std::endl;
   }

   void RasterizationEngine::release() {
      if(!isInitialized) return;
      if(pRenderer) {
         delete pRenderer;
         pRenderer = nullptr;
         isInitialized = false;
      }

      std::cout << "Rasterization engine released." << std::endl;
   }

   void RasterizationEngine::render(float lag) {
      glfwSwapBuffers(pRenderer->getWindow()->getHandle());
   }

   RasterizationEngine::~RasterizationEngine() {
      release();
   }
}


