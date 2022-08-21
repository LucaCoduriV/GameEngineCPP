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
#include <Scene/BaseComponents/MeshComponent.hpp>
#include <Scene/BaseComponents/MeshRendererComponent.hpp>
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <Math/Random.hpp>
#include <Scene/BaseComponents/MaterialComponent.hpp>


namespace GE{
   Scene::Scene() {
      registry = makeRef<ECS::Registry>();
   }

   Entity Scene::CreateEntity(const std::string &name) {
      auto id = registry->newEntity();
      registry->assign<TagComponent>(id, name);
      auto* transform = registry->assign<TransformComponent>(id);

      transform->position.x = 0.0f;
      transform->position.y = 0.0f;
      transform->position.z = 0.0f;

      transform->scale.x = 1.0f;
      transform->scale.y = 1.0f;
      transform->scale.z = 1.0f;

      return Entity(id, this);
   }

   void Scene::DestroyEntity(Entity entity) {
      registry->destroyEntity(entity.getId());
   }

//   template<typename T>
//   void Scene::onComponentAdded(Entity &entity, T &component) {
//      DEBUGBREAK;
//   }



   void Scene::draw(Shader& shader) {
      for(auto id : ECS::SceneView<GE::MeshRendererComponent, GE::TransformComponent>
         (*registry)){
         static bool test = false;

         auto& meshRenderer = *registry->get<GE::MeshRendererComponent>(id);

         //////////////////transform///////////////////
         auto* transform = registry->get<GE::TransformComponent>(id);


            transform->scale.x = 1.0f;
            transform->scale.y = 1.0f;
            transform->scale.z = 1.0f;
            test = true;

         transform = registry->get<GE::TransformComponent>(id);

         std::cout << transform->scale.x << " " << transform->scale.y << " " <<
         transform->scale.z << " " << std::endl;

         glm::mat4 model = glm::mat4(1.0f);
         model = glm::scale(model, transform->scale);
         model = glm::translate(model, transform->position);


         shader.setMat4f("u_model", model);
         //////////////////////////////////////////////

         /////////////////////textures/////////////////
         if(auto* mat = registry->get<GE::MaterialComponent>(id)){

            auto& textures = mat->textures;


            // bind appropriate textures
            unsigned int diffuseNr  = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr   = 1;
            unsigned int heightNr   = 1;

            //shader.bind();

            for(unsigned int i = 0; i < textures.size(); i++)
            {
               GLCall(glActiveTexture(GL_TEXTURE0 + i)); // active proper texture unit before
               // binding
               // retrieve texture number (the N in diffuse_textureN)
               std::string number;
               auto type = textures[i].type;
               if(type == TextureType::Diffuse)
                  number = std::to_string(diffuseNr++);
               else if(type == TextureType::Specular)
                  number = std::to_string(specularNr++); // transfer unsigned int to string
               else if(type == TextureType::Normal)
                  number = std::to_string(normalNr++); // transfer unsigned int to string
               else if(type == TextureType::Height)
                  number = std::to_string(heightNr++); // transfer unsigned int to string

               // now set the sampler to the correct texture unit
               GLCall(glUniform1i(glGetUniformLocation(shader.ID,
                                                       (getTextureTypeName(type) +
                                                       number).c_str()), i));
               // and finally bind the texture
               GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id));
            }
         }



         //////////////////////////////////////////////
         meshRenderer.draw(shader);
      }
   }

   void Scene::init() {
      for(auto i : ECS::SceneView<GE::MeshRendererComponent, GE::MeshComponent>
         (*registry)){

         auto& meshRenderer = *registry->get<GE::MeshRendererComponent>(i);
         auto& mesh = *registry->get<GE::MeshComponent>(i);

         meshRenderer.init(mesh.vertices, mesh.triangles);
      }

   }

}
