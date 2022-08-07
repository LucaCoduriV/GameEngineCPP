/*
-----------------------------------------------------------------------------------
Nom du fichier  : IRenderer.hpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_IRENDERER_HPP
#define GAMEENGINE_IRENDERER_HPP

#include "IWindow.hpp"

namespace GE {
   enum class ERendererType{
      Opengl33,
      OpenGL45,
      Vulkan,
   };

   struct SRendererCreateInfo{
      ERendererType rendererType;
      SWindowCreateInfo* windowCreateInfo;
   };

   class IRenderer {
   public:
      virtual ~IRenderer() = default;
      virtual void initialize(const SRendererCreateInfo& createInfo) = 0;
      virtual void release() = 0;

      IWindow* getWindow();
   protected:
      bool isInitialized = false;
      IWindow* pWindow = nullptr;
   };
}



#endif //GAMEENGINE_IRENDERER_HPP
