/*
-----------------------------------------------------------------------------------
Nom du fichier  : Shader.cpp
Auteur(s)       : lucac
Date creation   : 10.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Renderer.hpp"


Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
// 1. retrieve the vertex/fragment source code from filePath
   std::string vertexCode;
   std::string fragmentCode;
   std::ifstream vShaderFile;
   std::ifstream fShaderFile;
   // ensure ifstream objects can throw exceptions:
   vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
   try {
      // open files
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream;
      std::stringstream fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
   }
   catch (std::ifstream::failure &e) {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what()
                << std::endl;
   }
   const char *vShaderCode = vertexCode.c_str();
   const char *fShaderCode = fragmentCode.c_str();
   // 2. compile shaders
   unsigned int vertex;
   unsigned int fragment;
   // vertex shader
   vertex = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex, 1, &vShaderCode, NULL);
   glCompileShader(vertex);
   checkCompileErrors(vertex, "VERTEX");
   // fragment Shader
   fragment = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment, 1, &fShaderCode, NULL);
   glCompileShader(fragment);
   checkCompileErrors(fragment, "FRAGMENT");
   // shader Program
   ID = glCreateProgram();
   glAttachShader(ID, vertex);
   glAttachShader(ID, fragment);
   glLinkProgram(ID);
   checkCompileErrors(ID, "PROGRAM");
   // delete the shaders as they're linked into our program now and no longer necessary
   glDeleteShader(vertex);
   glDeleteShader(fragment);
}

void Shader::bind() {
   glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) {
   glUniform1i(getUniformLocation(name), (int) value);
}

void Shader::setInt(const std::string &name, int value) {
   glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string &name, float value) {
   glUniform1f(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string &name, float value, float value2) {
   glUniform2f(getUniformLocation(name), value, value2);
}

void Shader::setFloat(const std::string &name, float value, float value2, float
value3) {
   glUniform3f(getUniformLocation(name), value, value2, value3);
}

void Shader::setFloat(const std::string &name, float value, float value2, float
value3, float value4) {
   glUniform4f(getUniformLocation(name), value, value2, value3,
               value4);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string &type) {
   int success;
   char infoLog[1024];
   if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
         glGetShaderInfoLog(shader, 1024, NULL, infoLog);
         std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                   << infoLog
                   << "\n -- --------------------------------------------------- -- "
                   << std::endl;
      }
   } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
         glGetProgramInfoLog(shader, 1024, NULL, infoLog);
         std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                   << infoLog
                   << "\n -- --------------------------------------------------- -- "
                   << std::endl;
      }
   }
}

void Shader::unbind() {
   glUseProgram(0);
}

int Shader::getUniformLocation(const std::string &name) {

   try{
      return uniformLocationCache.at(name.c_str());
   }catch (const std::out_of_range& e){
      std::cout << "UniformLocation '" << name << "' not found in cache, getting "
                                                 "from GPU..." <<
      std::endl;
   }

   GLCall(int location = glGetUniformLocation(ID, name.c_str()));
   if(location == -1){
      std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
   }
   uniformLocationCache[name.c_str()] = location;

   return location;

}



