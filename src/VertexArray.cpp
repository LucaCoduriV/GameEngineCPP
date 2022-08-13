/*
-----------------------------------------------------------------------------------
Nom du fichier  : VertexArray.cpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "VertexArray.hpp"
#include "Renderer.hpp"

VertexArray::VertexArray() {
   GLCall(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray() {
   GLCall(glDeleteVertexArrays(1, &rendererID));
}

void
VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
   bind();
   vb.bind();
   const auto& elements = layout.GetElements();
   unsigned int offset = 0;

   for(unsigned int i = 0; i < elements.size(); i++){
      const auto& elem = elements[i];

      GLCall(glEnableVertexAttribArray(i));
      GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized ?
      GL_TRUE : GL_FALSE, layout.getStride() , (void*)(uintptr_t)offset));
      offset += elem.count * VertexBufferElement::getSizeOfType(elem.type);
   }


}

void VertexArray::bind() const {
   GLCall(glBindVertexArray(rendererID));
}

void VertexArray::unbind() {
   GLCall(glBindVertexArray(0));
}
