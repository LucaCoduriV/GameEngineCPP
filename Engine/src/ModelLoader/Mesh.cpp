//
// Created by luca on 18/08/22.
//

#include "ModelLoader/Mesh.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<STexture> textures) {
   this->vertices = vertices;
   this->indices = indices;
   this->textures = textures;

   setupMesh();
}

void Mesh::Draw(Shader &shader) {
   // bind appropriate textures
   unsigned int diffuseNr  = 1;
   unsigned int specularNr = 1;
   unsigned int normalNr   = 1;
   unsigned int heightNr   = 1;

   shader.bind();

   for(unsigned int i = 0; i < textures.size(); i++)
   {
      GLCall(glActiveTexture(GL_TEXTURE0 + i)); // active proper texture unit before
      // binding
      // retrieve texture number (the N in diffuse_textureN)
      std::string number;
      std::string name = textures[i].type;
      if(name == "texture_diffuse")
         number = std::to_string(diffuseNr++);
      else if(name == "texture_specular")
         number = std::to_string(specularNr++); // transfer unsigned int to string
      else if(name == "texture_normal")
         number = std::to_string(normalNr++); // transfer unsigned int to string
      else if(name == "texture_height")
         number = std::to_string(heightNr++); // transfer unsigned int to string

      // now set the sampler to the correct texture unit
      GLCall(glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()),
                         i));
      // and finally bind the texture
      GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id));
   }

   // draw mesh
   vao->bind();
   ebo->bind();
   GLCall(glDrawElements(GL_TRIANGLES, ebo->getCount(), GL_UNSIGNED_INT,
                  0));
   GLCall(glBindVertexArray(0));

   // always good practice to set everything back to defaults once configured.
   GLCall(glActiveTexture(GL_TEXTURE0));
}

void Mesh::setupMesh() {
   // create buffers/arrays
   vao = std::make_shared<VertexArray>();
   vbo = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
   ebo = std::make_shared<IndexBuffer>(indices.data(), indices.size());
   VertexBufferLayout layout;

   layout.push<float>(3);
   layout.push<float>(3);
   layout.push<float>(2);
   layout.push<float>(3);
   layout.push<float>(3);
   layout.push<int>(4, BufferType::INT);
   layout.push<float>(4);
   vao->addBuffer(*vbo, layout);

   VertexBuffer::unbind();
   IndexBuffer::unbind();
   VertexArray::unbind();
}
