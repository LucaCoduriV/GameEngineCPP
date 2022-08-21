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
   Entity::Entity(unsigned long long id, Scene* scene):id
   (id), scene(scene) {}

   unsigned long long Entity::getId() const {
      return id;
   }

   bool Entity::operator==(const Entity &rhs) const {
      return id == rhs.id &&
             scene == rhs.scene;
   }

   bool Entity::operator!=(const Entity &rhs) const {
      return !(rhs == *this);
   }
}