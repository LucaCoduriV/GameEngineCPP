/*
-----------------------------------------------------------------------------------
Nom du fichier  : IndexBuffer.cpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "IndexBuffer.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
   : count(count) {
   GLCall(glGenBuffers(1, &rendererID));
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
   GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data,
                       GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
   GLCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::bind() const {
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::unbind() {
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}