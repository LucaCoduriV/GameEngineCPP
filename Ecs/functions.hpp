/*
-----------------------------------------------------------------------------------
Nom du fichier  : functions.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_FUNCTIONS_HPP
#define SANDBOX_FUNCTIONS_HPP
namespace ECS {
   static int componentCounter = 0;
   static const int MAX_COMPONENTS = 32;

   using ComponentMask = std::bitset<MAX_COMPONENTS>;
   using EntityIndex = unsigned int;
   using EntityVersion = unsigned int;
   using EntityID = unsigned long long;

   static const unsigned long long MAX_ENTITIES = 5000;


   template<typename T>
   int getComponentId() {
      // la variable ici ne sera assignée qu'une seule fois au premier appel pour
      // chaque T.
      static int componentId = componentCounter++;
      return componentId;
   }


   inline EntityID createEntityId(EntityIndex index, EntityVersion version) {
      // On décale l'index de 32 bit, car EntityID contient 64bit
      return ((EntityID) index << 32 | (EntityID) version);
   }

   inline EntityIndex getEntityIndex(EntityID id) {
      return (EntityIndex)(id >> 32);
   }

   inline EntityVersion getEntityVersion(EntityID id) {
      // Avec le cast on perd les 32 derniers bits.
      return (EntityVersion) id;
   }

   inline bool isEntityValid(EntityID id) {
      return (id >> 32) != (EntityIndex) -1;
   }
}
#define INVALID_ENTITY createEntityId(EntityIndex(-1), 0)
#endif //SANDBOX_FUNCTIONS_HPP
