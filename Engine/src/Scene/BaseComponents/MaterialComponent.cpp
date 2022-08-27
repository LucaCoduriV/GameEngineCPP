/*
-----------------------------------------------------------------------------------
Nom du fichier  : MaterialComponent.cpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <Shader.hpp>
#include "Scene/BaseComponents/MaterialComponent.hpp"

namespace GE{
   std::string getTextureTypeName(TextureType type) {
      switch (type) {

         case TextureType::Diffuse:
            return "diffuse";
         case TextureType::Specular:
            return "specular";
         case TextureType::Normal:
            return "normal";
         case TextureType::Height:
            return "height";
         default:
            return "undefined";
      }
   }

   void MaterialComponent::sendToShader(Shader &shader) const {

      shader.bind();

      for (auto& texture : textures){
         std::string typeName = getTextureTypeName(texture.type);
         shader.setInt(std::string("u_material.") + typeName, texture.id);
      }
      shader.setFloat("u_material.shininess", 32.0f);
   }
}

