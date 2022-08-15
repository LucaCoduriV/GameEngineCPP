/*
-----------------------------------------------------------------------------------
Nom du fichier  : VertexBuffer.cpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "VertexBuffer.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
   GLCall(glGenBuffers(1, &rendererID));
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
   GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
   GLCall(glDeleteBuffers(1, &rendererID));
}

void VertexBuffer::bind() const {
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
}

void VertexBuffer::unbind() {
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
