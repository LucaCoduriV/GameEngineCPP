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
      explicit Entity(entt::entity handle, Scene* scene);
      Entity(const Entity& other) = default;

      template<typename T, typename... Args>
      T& AddComponent(Args&&... args){
         T& component =
            scene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
         return component;
      }

      template<typename T, typename... Args>
      T& AddOrReplaceComponent(Args&&... args)
      {
         T& component = scene->registry.emplace_or_replace<T>(entityHandle,
                                                            std::forward<Args>(args)...);
         return component;
      }

      template<typename T>
      T& GetComponent(){
         T& component = scene->registry.get<T>(entityHandle);
         return component;
      }

      template<typename T>
      bool HasComponent(){
         T* ptr = scene->registry.try_get<T>(entityHandle);
         return ptr != nullptr;
      }

      template<typename T>
      void RemoveComponent(){
         scene->registry.remove<T>(entityHandle);
      }

      [[nodiscard]] entt::entity getHandle() const;

      bool operator==(const Entity &rhs) const;

      bool operator!=(const Entity &rhs) const;

   private:
      entt::entity entityHandle{entt::null};
      Scene* scene;

   };


}




#endif //ENGINE_ENTITY_HPP
