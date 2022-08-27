/*
-----------------------------------------------------------------------------------
Nom du fichier  : MaterialComponent.hpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_MATERIALCOMPONENT_HPP
#define SANDBOX_MATERIALCOMPONENT_HPP

#include <vector>
#include <string>

namespace GE{
   enum class TextureType {
      Diffuse,
      Specular,
      Normal,
      Height
   };

   std::string getTextureTypeName(TextureType type);

   struct Texture {
      int id;
      TextureType type;
      std::string path; // pour du debug

   };

   enum class ShaderType{
      Normal
   };

   struct MaterialComponent{
      ShaderType shaderType = ShaderType::Normal;
      std::vector<Texture> textures;

      void sendToShader(Shader& shader) const;
   };
}
#endif //SANDBOX_MATERIALCOMPONENT_HPP
