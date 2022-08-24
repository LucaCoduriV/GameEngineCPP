/*
-----------------------------------------------------------------------------------
Nom du fichier  : ShaderBuilder.cpp
Auteur(s)       : lucac
Date creation   : 24.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderBuilder.hpp"

std::tuple<std::string, std::string> readFiles(
   const std::filesystem::path& vertexPath,
   const std::filesystem::path& fragmentPath
   ){
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
      std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what()
                << std::endl;
   }

   return {vertexCode, fragmentCode};
}

GE::ShaderBuilder::ShaderBuilder(
   const std::unordered_map<std::string, std::string>& vertexDefines,
   const std::unordered_map<std::string, std::string>& fragmentDefines,
   const std::filesystem::path& vertexPath,
   const std::filesystem::path& fragmentPath
){
   auto [vertexCode, fragmentCode] = readFiles(vertexPath, fragmentPath);

   size_t posV = vertexCode.find_first_of('\n');
   for (auto& v: vertexDefines) {
      if (posV ==  std::string::npos){
         throw std::runtime_error("something wrong in file, no new line found");
      }
      vertexCode.insert(
         posV + 1,
         std::string("#define ") + v.first + " " + v.second + "\n");
   }

   size_t posF = fragmentCode.find_first_of('\n');
   for (auto& v: fragmentDefines) {
      if (posF ==  std::string::npos){
         throw std::runtime_error("something wrong in file, no new line found");
      }
      vertexCode.insert(
         posF + 1,
         std::string("#define ") + v.first + " " + v.second + "\n");
   }

}
