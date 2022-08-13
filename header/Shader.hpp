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
#include <unordered_map>
#include "GL/glew.h"


class Shader {
public:
   // the program ID
   unsigned int ID;

   // le constructeur lit et construit le shader
   Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

   // Activation du shader
   void bind();

   static void unbind();

   // fonctions utiles pour l'uniform

   void setBool(const std::string &name, bool value);

   void setInt(const std::string &name, int value);

   void setFloat(const std::string &name, float value);

   void setFloat(const std::string &name, float value, float value2);

   void setFloat(const std::string &name, float value, float value2,
                 float value3);

   void setFloat(const std::string &name, float value, float value2, float value3,
                 float value4);

private:
   [[nodiscard]] int getUniformLocation(const std::string &name);
   static void checkCompileErrors(unsigned int shader, const std::string &type);
   std::unordered_map<const char*, int> uniformLocationCache;

};


#endif //GAMEENGINE_SHADER_HPP
