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

namespace ECS{
   static int componentCounter = 0;
   const int MAX_COMPONENTS = 32;

   using ComponentMask = std::bitset<MAX_COMPONENTS>;
   using EntityID = unsigned long long;

   const unsigned long long MAX_ENTITIES = 5000;



   template <typename T>
   int getId(){
      static int componentId = componentCounter++;
      return componentId;
   }

   struct ComponentPool {
      ComponentPool(size_t elementSize){
         this->elementSize = elementSize;
         pData = new char[elementSize * MAX_ENTITIES];
      }

      ~ComponentPool(){
         delete[] pData;
      }

      inline void* get(size_t index){
         return &pData[index * elementSize];
      }

      char* pData = nullptr;
      size_t elementSize = 0;
   };

   struct Scene{
      struct EntityDesc {
         EntityID id;
         ComponentMask mask;
      };

      std::vector<EntityDesc> entities;
      std::vector<ComponentPool*> componentPools;

      EntityID newEntity(){
         entities.push_back({entities.size(), ComponentMask()});
         return entities.back().id;
      };

      template<typename T>
      T* assign(EntityID id){
         auto componentId = getId<T>();

         if(componentPools.size() <= componentId) { // Pas assez de mémoire
            componentPools.resize(componentId + 1, nullptr);
         }
         if(componentPools[componentId] == nullptr){ // Il faut donc en créer un
            componentPools[componentId] = new ComponentPool(sizeof(T));
         }

         //Solution temporaire mais utilise plus de mémoire
         //componentPools.push_back(new ComponentPool(sizeof(T)));

         // on crée un nouvel élément à cet emplacement mémoire
         auto* pComponent = new (componentPools[componentId]->get(id)) T();

         entities[id].mask.set(componentId);

         return pComponent;
      }

      template<typename T>
      T* get(EntityID id){
         auto componentId = getId<T>();

         if(!entities[id].mask.test(componentId)){
            return nullptr;
         }

         T* pComponent = static_cast<T*>(componentPools[componentId]->get(id));
         return pComponent;
      }


   };






}




#endif //SANDBOX_ECS_HPP
