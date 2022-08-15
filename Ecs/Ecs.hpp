/*
-----------------------------------------------------------------------------------
Nom du fichier  : Ecs.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_ECS_HPP
#define SANDBOX_ECS_HPP


#include <bitset>
#include <vector>
#include <limits>

namespace ECS {
   static int componentCounter = 0;
   const int MAX_COMPONENTS = 32;

   using ComponentMask = std::bitset<MAX_COMPONENTS>;
   using EntityIndex = unsigned int;
   using EntityVersion = unsigned int;
   using EntityID = unsigned long long;

   const unsigned long long MAX_ENTITIES = 5000;


   template<typename T>
   int getId() {
      // la variable ici ne sera assignée qu'une seule fois au premier appel pour
      // chaque T.
      static int componentId = componentCounter++;
      return componentId;
   }

   struct ComponentPool {
      ComponentPool(size_t elementSize) {
         this->elementSize = elementSize;
         pData = new char[elementSize * MAX_ENTITIES];
      }

      ~ComponentPool() {
         delete[] pData;
      }

      inline void *get(size_t index) {
         return &pData[index * elementSize];
      }

      char *pData = nullptr;
      size_t elementSize = 0;
   };

   inline EntityID createEntityId(EntityIndex index, EntityVersion version) {
      // On décale l'index de 32 bit, car EntityID contient 64bit
      return ((EntityID) index << 32 | (EntityID) version);
   }

   inline EntityIndex getEntityIndex(EntityID id) {
      return (id >> 32);
   }

   inline EntityVersion getEntityVersion(EntityID id) {
      // Avec le cast on perd les 32 derniers bits.
      return (EntityVersion) id;
   }

   inline bool isEntityValid(EntityID id) {
      return (id >> 32) != (EntityIndex) -1;
   }

#define INVALID_ENTITY createEntityId(EntityIndex(-1), 0)

   struct Scene {
      struct EntityDesc {
         EntityID id;
         ComponentMask mask;
      };

      std::vector<EntityDesc> entities;
      std::vector<ComponentPool *> componentPools;
      std::vector<EntityIndex> freeEntities;

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

      template<typename T>
      T *assign(EntityID id) {
         auto componentId = getId<T>();

         auto entityIndex = getEntityIndex(id);
//         if(entities[entityIndex].id != id){
//            return nullptr;
//         }

         // on utilise pas le pushback car son implémentation double la mémoire
         // s'il y en a pas assez.

         if (componentPools.size() <= componentId) { // Pas assez de mémoire
            componentPools.resize(componentId + 1, nullptr);
         }
         if (componentPools[componentId] == nullptr) { // Il faut donc en créer un
            componentPools[componentId] = new ComponentPool(sizeof(T));
         }

         // on crée un nouvel élément à cet emplacement mémoire
         auto *pComponent = new(componentPools[componentId]->get(entityIndex)) T();

         entities[entityIndex].mask.set(componentId);

         return pComponent;
      }

      template<typename T>
      T *get(EntityID id) {
         auto componentId = getId<T>();

         auto entityIndex = getEntityIndex(id);
         if (entities[entityIndex].id != id) {
            return nullptr;
         }

         if (!entities[entityIndex].mask.test(componentId)) {
            return nullptr;
         }

         T *pComponent = static_cast<T *>(componentPools[componentId]->get(entityIndex));
         return pComponent;
      }

      template<typename T>
      void remove(EntityID id) {

         auto entityIndex = getEntityIndex(id);

         if (entities[entityIndex].id != id) {
            return;
         }

         auto componentId = getId<T>();

         entities[entityIndex].mask.reset(componentId);

      }

   };


}


#endif //SANDBOX_ECS_HPP
