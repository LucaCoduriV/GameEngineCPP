/*
-----------------------------------------------------------------------------------
Nom du fichier  : SpotLightComponent.hpp
Auteur(s)       : lucac
Date creation   : 24.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ENGINE_SPOTLIGHTCOMPONENT_HPP
#define ENGINE_SPOTLIGHTCOMPONENT_HPP

#include <glm/vec3.hpp>

struct SpotLight {
   glm::vec3 position;
   glm::vec3 direction;
   float cutOff;
   float outerCutOff;

   float constant;
   float linear;
   float quadratic;

   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
};

#endif //ENGINE_SPOTLIGHTCOMPONENT_HPP
