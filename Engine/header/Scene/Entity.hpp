/*
-----------------------------------------------------------------------------------
Nom du fichier  : Entity.hpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ENGINE_ENTITY_HPP
#define ENGINE_ENTITY_HPP

#include "Scene/Scene.hpp"
#include "definitions.hpp"

namespace GE{
   class Entity {
      friend class Scene;

   public:
      explicit Entity(unsigned long long id, Scene* scene);

      template<typename T, typename... Args>
      T& AddComponent(Args&&... args){
         T* ptr = scene->registry->assign<T>(id, std::forward<Args>(args)...);
         scene->template onComponentAdded(*this, *ptr);
         return *ptr;
      }

      template<typename T>
      T& GetComponent(){
         T* ptr = scene->registry->get<T>(id);
         return *ptr;
      }

      template<typename T>
      bool HasComponent(){
         T* ptr = scene->registry->get<T>(id);
         return ptr != nullptr;
      }

      template<typename T>
      void RemoveComponent(){
         scene->registry->remove<T>(id);
      }

      [[nodiscard]] unsigned long long getId() const;

      bool operator==(const Entity &rhs) const;

      bool operator!=(const Entity &rhs) const;

   private:
      unsigned long long id;
      Scene* scene;

   };


}




#endif //ENGINE_ENTITY_HPP
