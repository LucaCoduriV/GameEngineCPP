/*
-----------------------------------------------------------------------------------
Nom du fichier  : DirectionalLightComponent.hpp
Auteur(s)       : lucac
Date creation   : 24.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ENGINE_DIRECTIONALLIGHTCOMPONENT_HPP
#define ENGINE_DIRECTIONALLIGHTCOMPONENT_HPP

#include <glm/vec3.hpp>

namespace GE{
   struct DirLight {
      glm::vec3 direction;

      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;
   };
}


#endif //ENGINE_DIRECTIONALLIGHTCOMPONENT_HPP
