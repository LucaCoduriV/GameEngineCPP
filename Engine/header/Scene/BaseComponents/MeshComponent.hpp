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
   struct MeshComponent{
      std::vector<glm::vec3> vertices;
      std::vector<glm::vec2> uvs;
      std::vector<unsigned int> triangles;
      std::vector<glm::vec3> Normal;
      std::vector<glm::vec3> Tangent;
      std::vector<glm::vec3> Bitangent;
      std::vector<std::array<int, MAX_BONE_INFLUENCE>> boneIDs;
      std::vector<std::array<int, MAX_BONE_INFLUENCE>> weights;
   };
}
#endif //SANDBOX_MESHCOMPONENT_HPP
