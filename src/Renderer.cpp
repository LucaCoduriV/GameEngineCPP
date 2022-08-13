/*
-----------------------------------------------------------------------------------
Nom du fichier  : Renderer.cpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Renderer.hpp"
#include <iostream>

void GLClearError(){
   while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line){
   while(GLenum error = glGetError()){
      std::cerr << "[OpenGL Error] (" << error << "): " << function << " " << file
                << ":" << line << std::endl;
      return false;
   }
   return true;
}