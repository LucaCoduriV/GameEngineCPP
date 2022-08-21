/*
-----------------------------------------------------------------------------------
Nom du fichier  : Renderer3D.cpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <ModelLoader/Mesh.hpp>
#include "Scene/BaseComponents/MeshRendererComponent.hpp"

namespace GE{
   void MeshRendererComponent::init(const std::vector<Vertex>& vertices,
                                    const std::vector<unsigned int>& uvs){
      vao = std::make_shared<VertexArray>();
      vbo = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
      ebo = std::make_shared<IndexBuffer>(uvs.data(), uvs.size());

      VertexBufferLayout layout;
      layout.push<float>(3);
      layout.push<float>(3);
      layout.push<float>(2);
      layout.push<float>(3);
      layout.push<float>(3);
      layout.push<int>(4, BufferType::INT);
      layout.push<float>(4);
      vao->addBuffer(*vbo, layout);
   }

   void MeshRendererComponent::draw(const Shader &shader){
      // bind appropriate textures
      unsigned int diffuseNr  = 1;
      unsigned int specularNr = 1;
      unsigned int normalNr   = 1;
      unsigned int heightNr   = 1;

      // draw mesh
      vao->bind();
      ebo->bind();
      GLCall(glDrawElements(GL_TRIANGLES, ebo->getCount(), GL_UNSIGNED_INT, 0));

      VertexArray::unbind();

   }
}