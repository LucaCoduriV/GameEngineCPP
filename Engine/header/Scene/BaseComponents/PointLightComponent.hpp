/*
-----------------------------------------------------------------------------------
Nom du fichier  : LightComponent.hpp
Auteur(s)       : lucac
Date creation   : 24.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ENGINE_POINTLIGHTCOMPONENT_HPP
#define ENGINE_POINTLIGHTCOMPONENT_HPP

#include <glm/vec3.hpp>
#include "Shader.hpp"

namespace GE{
   struct PointLightComponent {
      glm::vec3 position;

      float constant;
      float linear;
      float quadratic;

      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;

      void sendToShader(Shader& shader) const;

   };




}



#endif //ENGINE_LIGHTCOMPONENT_HPP
