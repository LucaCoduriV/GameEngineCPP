/*
-----------------------------------------------------------------------------------
Nom du fichier  : IRenderingEngine.hpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_IRENDERINGENGINE_HPP
#define GAMEENGINE_IRENDERINGENGINE_HPP

#include "Rendering/Renderer/IRenderer.hpp"

namespace GE{

   enum class ERenderingEnginyType{
      Rasterization,
      RayTracingCPU,
      RayTracingGPU,
   };

   struct SRenderingEngineCreateInfo{
      ERenderingEnginyType renderingEnginyType;
      SRendererCreateInfo* pRendererCreateInfo;
   };

   class IRenderingEngine {
   public:
      virtual ~IRenderingEngine() = default;
      virtual void initialize(const SRenderingEngineCreateInfo& createInfo) = 0;
      virtual void release() = 0;
      virtual void render(float lag) = 0;

      IRenderer* getRenderer();
   protected:
      bool isInitialized = false;
      IRenderer* pRenderer = nullptr;
   };
}



#endif //GAMEENGINE_IRENDERINGENGINE_HPP
