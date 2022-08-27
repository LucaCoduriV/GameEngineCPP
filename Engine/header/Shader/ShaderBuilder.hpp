/*
-----------------------------------------------------------------------------------
Nom du fichier  : ShaderBuilder.hpp
Auteur(s)       : lucac
Date creation   : 24.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef ENGINE_SHADERBUILDER_HPP
#define ENGINE_SHADERBUILDER_HPP

#include <string>
#include <unordered_map>
#include <filesystem>

namespace GE {
   class ShaderBuilder {
   public:
      explicit ShaderBuilder(
         const std::unordered_map<std::string, std::string> &vertexDefines,
         const std::unordered_map<std::string, std::string> &fragmentDefines,
         const std::filesystem::path &vertexPath,
         const std::filesystem::path &fragmentPath
      );

      const std::string &getVertexProgram() const;

      const std::string &getFragmentProgram() const;

   private:
      std::string vertexProgram;
      std::string fragmentProgram;

   };
}

#endif //ENGINE_SHADERBUILDER_HPP
