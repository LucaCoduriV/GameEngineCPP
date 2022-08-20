//
// Created by luca on 18/08/22.
//

#ifndef SANDBOX_MESH_HPP
#define SANDBOX_MESH_HPP

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "definitions.hpp"
#include "IndexBuffer.hpp"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
   // position
   glm::vec3 Position;
   // normal
   glm::vec3 Normal;
   // texCoords
   glm::vec2 TexCoords;
   // tangent
   glm::vec3 Tangent;
   // bitangent
   glm::vec3 Bitangent;
   //bone indexes which will influence this vertex
   int m_BoneIDs[MAX_BONE_INFLUENCE];
   //weights from each bone
   float m_Weights[MAX_BONE_INFLUENCE];
};

struct STexture {
   unsigned int id;
   std::string type;
   std::string path;
};

class Mesh {
public:
   // mesh Data
   std::vector<Vertex>       vertices;
   std::vector<unsigned int> indices;
   std::vector<STexture>      textures;

   GM::Ref<VertexArray> vao;

   // constructor
   Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
        std::vector<STexture> textures);

   // render the mesh
   void Draw(Shader &shader);

private:
   // render data
   GM::Ref<VertexBuffer> vbo;
   GM::Ref<IndexBuffer> ebo;

   // initializes all the buffer objects/arrays
   void setupMesh();
};


#endif //SANDBOX_MESH_HPP
