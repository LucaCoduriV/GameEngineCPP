/*
-----------------------------------------------------------------------------------
Nom du fichier  : Scene.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ECS_REGISTRY_HPP
#define ECS_REGISTRY_HPP


#include "functions.hpp"
#include "ComponentPool.hpp"
#include "vector"

namespace ECS {

   class Registry {
      template<typename...> friend class SceneView;
   public:
      EntityID newEntity() {

         // si pas vide on peur réutiliser un ancien emplacement
         if (!freeEntities.empty()) {
            EntityIndex newIndex = freeEntities.back();
            freeEntities.pop_back();

            EntityID newId = createEntityId(newIndex,
                                            getEntityVersion(entities[newIndex].id));
            entities[newIndex].id = newId;
            return newId;
         }

         entities.push_back({createEntityId(EntityIndex(entities.size()), 0),
                             ComponentMask()});

         return entities.back().id;
      };

      void destroyEntity(EntityID id) {
         EntityID newID = createEntityId(EntityIndex(-1), getEntityVersion(id) + 1);
         entities[getEntityIndex(id)].id = newID;
         entities[getEntityIndex(id)].mask.reset();
         freeEntities.push_back(getEntityIndex(id));
      }

      template<typename T, typename...Args>
      T *assign(EntityID id, Args&&... args) {
         auto componentId = getComponentId<T>();

         auto entityIndex = getEntityIndex(id);
         if(entities[entityIndex].id != id){
            return nullptr;
         }

         // on utilise pas le pushback car son implémentation double la mémoire
         // s'il y en a pas assez.

         if (componentPools.size() <= componentId) { // Pas assez de mémoire
            componentPools.resize(componentId + 1, nullptr);
         }
         if (componentPools[componentId] == nullptr) { // Il faut donc en créer un
            componentPools[componentId] = new ComponentPool(sizeof(T));
         }

         // on crée un nouvel élément à cet emplacement mémoire
         auto *pComponent = new(componentPools[componentId]->get(entityIndex))
            T(std::forward<Args>(args)...);

         entities[entityIndex].mask.set(componentId);

         return pComponent;
      }

      template<typename T>
      T *get(EntityID id) {
         auto componentId = getComponentId<T>();

         auto entityIndex = getEntityIndex(id);
         if (entities[entityIndex].id != id) {
            return nullptr;
         }

         if (!entities[entityIndex].mask.test(componentId)) {
            return nullptr;
         }

         T *pComponent = static_cast<T *>(componentPools[componentId]->get(
            entityIndex));
         return pComponent;
      }

      template<typename T>
      void remove(EntityID id) {

         auto entityIndex = getEntityIndex(id);

         if (entities[entityIndex].id != id) {
            return;
         }

         auto componentId = getComponentId<T>();

         entities[entityIndex].mask.reset(componentId);

      }
   private:
      struct EntityDesc {
         EntityID id;
         ComponentMask mask;
      };

      std::vector<EntityDesc> entities;
      std::vector<ComponentPool *> componentPools;
      std::vector<EntityIndex> freeEntities;
   };
}
#endif //SANDBOX_SCENE_HPP
