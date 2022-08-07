/*
-----------------------------------------------------------------------------------
Nom du fichier  : OpenGL33Renderer.hpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_OPENGL33RENDERER_HPP
#define GAMEENGINE_OPENGL33RENDERER_HPP

#include <Rendering/Renderer/IRenderer.hpp>
#include "OpenGL33Window.hpp"

namespace GE {
   class OpenGL33Renderer : public IRenderer {

   public:
      ~OpenGL33Renderer() override;

      void release() final;
      void initialize(const SRendererCreateInfo &createInfo) final;

   private:
      OpenGL33Window window;

   };
}


#endif //GAMEENGINE_OPENGL33RENDERER_HPP
