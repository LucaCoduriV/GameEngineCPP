/*
-----------------------------------------------------------------------------------
Nom du fichier  : ComponentPool.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_COMPONENTPOOL_HPP
#define SANDBOX_COMPONENTPOOL_HPP

#include "functions.hpp"

namespace ECS{
   class ComponentPool {
   public:
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

   private:
      char *pData = nullptr;
      size_t elementSize = 0;
   };
}
#endif //SANDBOX_COMPONENTPOOL_HPP
