/*
-----------------------------------------------------------------------------------
Nom du fichier  : MeshComponent.hpp
Auteur(s)       : lucac
Date creation   : 20.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_MESHCOMPONENT_HPP
#define SANDBOX_MESHCOMPONENT_HPP

#include <vector>
#include <array>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#define MAX_BONE_INFLUENCE 4

namespace GE{
   struct Vertex {
      // position
      glm::vec3 position;
      // normal
      glm::vec3 normal;
      // texCoords
      glm::vec2 uv;
      // tangent
      glm::vec3 tangent;
      // bitangent
      glm::vec3 bitangent;
      //bone indexes which will influence this vertex
      int m_BoneIDs[MAX_BONE_INFLUENCE];
      //weights from each bone
      float m_Weights[MAX_BONE_INFLUENCE];
   };

   struct MeshComponent{
      std::vector<Vertex> vertices;
      std::vector<unsigned int> triangles;
   };
}
#endif //SANDBOX_MESHCOMPONENT_HPP
