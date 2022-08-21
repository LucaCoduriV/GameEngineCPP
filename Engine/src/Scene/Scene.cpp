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
   Scene::Scene() {}

   Entity Scene::CreateEntity(const std::string &name) {
      Entity entity(registry.create(), this);
      entity.AddComponent<TagComponent>(name);
      entity.AddComponent<TransformComponent>();

      return entity;
   }

   void Scene::DestroyEntity(Entity entity) {
      registry.destroy(entity.getHandle());
   }



   void Scene::draw(Shader& shader) {
      auto view = registry.view<MeshRendererComponent, TransformComponent>();
      for (auto entity : view){
         auto [meshRenderer, transform] =
            view.get<MeshRendererComponent, TransformComponent>(entity);

         //////////////////MODEL///////////////////

         glm::mat4 model = glm::mat4(1.0f);
         model = glm::scale(model, transform.scale);
         model = glm::translate(model, transform.position);

         shader.setMat4f("u_model", model);
         //////////////////////////////////////////////

         /////////////////////textures/////////////////
         if(auto* mat = registry.try_get<MaterialComponent>(entity)){



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
      auto view = registry.view<MeshRendererComponent, MeshComponent>();
      for(auto entity : view){
         auto [meshRenderer, mesh] =
            view.get<MeshRendererComponent,MeshComponent>(entity);
         meshRenderer.init(mesh.vertices, mesh.triangles);
      }
   }

}
