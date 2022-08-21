/*
-----------------------------------------------------------------------------------
Nom du fichier  : Scene.hpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include "definitions.hpp"
#include <string>
#include <memory>
#include <Shader.hpp>
#include <entt.hpp>

namespace GE{
   class Entity;

   class Scene {
      friend class Entity;

   public:
      Scene();
      ~Scene() = default;

      Entity CreateEntity(const std::string& name = std::string());
      void DestroyEntity(Entity entity);

      void draw(Shader& shader);
      void init();

   private:
      entt::registry registry;

   };
}

#endif //SANDBOX_SCENE_HPP
