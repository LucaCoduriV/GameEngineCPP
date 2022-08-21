/*
-----------------------------------------------------------------------------------
Nom du fichier  : Renderer3D.hpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ENGINE_MESHRENDERERCOMPONENT_HPP
#define ENGINE_MESHRENDERERCOMPONENT_HPP

#include <Shader.hpp>
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>
#include <VertexArray.hpp>
#include <definitions.hpp>
#include <Scene/BaseComponents/MeshComponent.hpp>

namespace GE{
   class MeshRendererComponent {
   public:
      MeshRendererComponent() = default;

      void init(const std::vector<Vertex>& vertices,
                                       const std::vector<unsigned int>& uvs);
      void draw(const Shader &shader);

   private:
      Ref<VertexArray> vao;
      Ref<VertexBuffer> vbo;
      Ref<IndexBuffer> ebo;
   };


}

#endif //ENGINE_MESHRENDERER_HPP
