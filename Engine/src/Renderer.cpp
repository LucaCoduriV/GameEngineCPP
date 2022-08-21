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
#include "definitions.hpp"

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
   GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

   ib.unbind();
   va.unbind();
   shader.unbind();
}

void Renderer::clear() {
   GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));
   GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &va, Shader &shader, int count) {
   shader.bind();
   va.bind();

   glDrawArrays(GL_TRIANGLES, 0, count);
}
