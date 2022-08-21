/*
-----------------------------------------------------------------------------------
Nom du fichier  : Entity.cpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <Scene/Entity.hpp>
#include <utility>

namespace GE{
   Entity::Entity(entt::entity handle, Scene* scene):entityHandle(handle), scene(scene) {}

   entt::entity Entity::getHandle() const {
      return entityHandle;
   }

   bool Entity::operator==(const Entity &rhs) const {
      return entityHandle == rhs.entityHandle &&
             scene == rhs.scene;
   }

   bool Entity::operator!=(const Entity &rhs) const {
      return !(rhs == *this);
   }
}