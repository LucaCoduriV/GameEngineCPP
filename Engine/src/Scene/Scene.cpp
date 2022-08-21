/*
-----------------------------------------------------------------------------------
Nom du fichier  : Scene.cpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/



#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"
#include <Scene/BaseComponents/TagComponent.hpp>
#include <Scene/BaseComponents/TransformComponent.hpp>


namespace GE{
   Scene::Scene() {
      registry = makeRef<ECS::Registry>();
   }

   Entity Scene::CreateEntity(const std::string &name) {
      auto id = registry->newEntity();
      registry->assign<TagComponent>(id, name);
      registry->assign<TransformComponent>(id);

      return Entity(id, this);
   }

   void Scene::DestroyEntity(Entity entity) {
      registry->destroyEntity(entity.getId());
   }

   template<typename T>
   void Scene::onComponentAdded(Entity &entity, T &component) {
      DEBUGBREAK;
   }

}
