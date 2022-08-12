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
#include <Shader/Shader.hpp>
#include <memory>
#include "OpenGL33Window.hpp"
#include "GL/glew.h"

namespace GE {
   class OpenGL33Renderer : public IRenderer {

   public:
      ~OpenGL33Renderer() override;

      void release() final;
      void initialize(const SRendererCreateInfo &createInfo) final;
      void render(float lag) final;

   private:
      OpenGL33Window window;
      unsigned int VBO, VAO, EBO;
      static constexpr float vertices[] = {
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
         -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         -0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
      };

      static constexpr unsigned int indices[] = {  // Notons que l’on commence à 0!
         0, 1, 3,   // premier triangle
         1, 2, 3    // second triangle
      };

      std::unique_ptr<Shader> shader;

   };
}


#endif //GAMEENGINE_OPENGL33RENDERER_HPP
