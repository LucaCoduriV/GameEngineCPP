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

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib,
                    Shader &shader) {
   shader.bind();
   va.bind();
   ib.bind();
   GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

   ib.unbind();
   va.unbind();
   shader.unbind();
}

void Renderer::clear() {
   GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
