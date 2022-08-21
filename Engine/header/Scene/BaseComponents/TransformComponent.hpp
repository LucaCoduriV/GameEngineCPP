/*
-----------------------------------------------------------------------------------
Nom du fichier  : TransformComponent.hpp
Auteur(s)       : lucac
Date creation   : 20.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_TRANSFORMCOMPONENT_HPP
#define SANDBOX_TRANSFORMCOMPONENT_HPP

#include <glm/vec3.hpp>

namespace GE{
   struct TransformComponent{
      glm::vec3 position = { 0.0f, 0.0f, 0.0f };
      glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
      glm::vec3 scale = { 0.0f, 0.0f, 0.0f };

      TransformComponent() = default;
      TransformComponent(const TransformComponent&) = default;
      explicit TransformComponent(const glm::vec3& position)
         : position(position) {}
   };
}

#endif //SANDBOX_TRANSFORMCOMPONENT_HPP
