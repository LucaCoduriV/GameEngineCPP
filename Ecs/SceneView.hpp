/*
-----------------------------------------------------------------------------------
Nom du fichier  : SceneView.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_SCENEVIEW_HPP
#define SANDBOX_SCENEVIEW_HPP

#include "functions.hpp"

namespace ECS {
   template<typename... ComponentTypes>
   class SceneView {
   public:
      SceneView(Scene &scene) : pScene(&scene) {
         if (sizeof...(ComponentTypes) == 0) {
            all = true;
         } else {
            // Unpack les types (c'est une feature de c++11)
            int componentIds[] = {0, getComponentId<ComponentTypes>() ...};
            for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++) {
               // ce mask indiquera les Component qu'il faut chercher
               componentMask.set(componentIds[i]);
            }
         }
      }

      class Iterator {
      public:
         Iterator(Scene *pScene, EntityIndex index, ComponentMask mask, bool all)
            : pScene(pScene), index(index), mask(mask), all(all) {}

         ECS::EntityID operator*() const {
            return pScene->entities[index].id;
         }

         bool operator==(const Iterator &other) const {
            return index == other.index || index == pScene->entities.size();
         }

         bool operator!=(const Iterator &other) const {
            return index != other.index && index != pScene->entities.size();
         }

         bool validIndex() {
            return
               isEntityValid(pScene->entities[index].id) &&
               (all || mask == (mask & pScene->entities[index].mask));
         }

         Iterator &operator++() {
            do {
               index++;
            } while (index < pScene->entities.size() && !validIndex());
            return *this;
         }

         EntityIndex getIndex() const {
            return index;
         }
      private:
         Scene *pScene;
         EntityIndex index;
         ComponentMask mask;
         bool all = false;

      };

      const Iterator begin() const {
         EntityIndex firstIndex = 0;
         while (firstIndex < pScene->entities.size() &&
                (componentMask != (componentMask & pScene->entities[firstIndex].mask)
                 || !isEntityValid(pScene->entities[firstIndex].id))) {
            firstIndex++;
         }
         return Iterator(pScene, firstIndex, componentMask, all);
      }

      const Iterator end() const {
         return Iterator(pScene, EntityIndex(pScene->entities.size()), componentMask,
                         all);
      }
   private:
      Scene *pScene = nullptr;
      ComponentMask componentMask;
      bool all = false;
   };
}


#endif //SANDBOX_SCENEVIEW_HPP
