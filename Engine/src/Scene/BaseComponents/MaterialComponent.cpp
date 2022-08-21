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

#include "Scene/BaseComponents/MaterialComponent.hpp"

namespace GE{
   std::string getTextureTypeName(TextureType type) {
      switch (type) {

         case TextureType::Diffuse:
            return "texture_diffuse";
         case TextureType::Specular:
            return "texture_specular";
         case TextureType::Normal:
            return "texture_normal";
         case TextureType::Height:
            return "texture_height";
         default:
            return "undefined";
      }
   }
}

