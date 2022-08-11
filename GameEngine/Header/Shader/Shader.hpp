/*
-----------------------------------------------------------------------------------
Nom du fichier  : Shader.hpp
Auteur(s)       : lucac
Date creation   : 10.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_SHADER_HPP
#define GAMEENGINE_SHADER_HPP

#include <string>
#include "GL/glew.h"

namespace GE {
   class Shader {
   public:
      // the program ID
      unsigned int ID;

      // le constructeur lit et construit le shader
      Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

      // Activation du shader
      void use();

      // fonctions utiles pour l'uniform
      void setBool(const std::string &name, bool value) const;

      void setInt(const std::string &name, int value) const;

      void setFloat(const std::string &name, float value) const;

      void setFloat(const std::string &name, float value, float value2) const;

      void setFloat(const std::string &name, float value, float value2,
                    float value3) const;

      void setFloat(const std::string &name, float value, float value2, float value3,
                    float value4) const;

   private:
      static void checkCompileErrors(unsigned int shader, const std::string& type);


   };
}


#endif //GAMEENGINE_SHADER_HPP
