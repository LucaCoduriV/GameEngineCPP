/*
-----------------------------------------------------------------------------------
Nom du fichier  : VertexBufferLayout.hpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_VERTEXBUFFERLAYOUT_HPP
#define GAMEENGINE_VERTEXBUFFERLAYOUT_HPP


#include <vector>
#include <GL/glew.h>
#include <stdexcept>

enum class BufferType{
   FLOAT,
   INT,
   LONG,
};

struct VertexBufferElement {
   unsigned int count;
   unsigned int type;
   bool normalized;
   BufferType bufferType;

   static unsigned int getSizeOfType(unsigned int type) {
      switch(type) {
         case GL_FLOAT:
            return sizeof(GLfloat);
         case GL_UNSIGNED_INT:
            return sizeof(GLuint);
         case GL_UNSIGNED_BYTE:
            return sizeof(GLubyte);
         case GL_INT:
            return sizeof(GLint);
      }
      throw std::runtime_error("The type is not supported");
   };

};

class VertexBufferLayout {
public:
   VertexBufferLayout() : stride(0) {}

   template<typename T>
   inline void push(unsigned int count, BufferType bufferType = BufferType::FLOAT,
                    bool normalized = false);

   [[nodiscard]] inline const std::vector<VertexBufferElement> &GetElements() const {
      return elements;
   }

   [[nodiscard]] inline unsigned int getStride() const { return stride; }

private:
   std::vector<VertexBufferElement> elements;
   unsigned int stride;
};

template<typename T>
inline void VertexBufferLayout::push(unsigned int count, BufferType bufferType,
                                     bool normalized) {
   throw std::runtime_error("The type is not supported");
}

template<>
inline void
VertexBufferLayout::push<float>(unsigned int count, BufferType bufferType,
                                bool normalized) {
   elements.push_back({count, GL_FLOAT, normalized, bufferType});
   stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
inline void
VertexBufferLayout::push<unsigned int>(unsigned int count, BufferType bufferType,
                                       bool normalized) {
   elements.push_back({count, GL_UNSIGNED_INT, normalized, bufferType});
   stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void
VertexBufferLayout::push<unsigned char>(unsigned int count, BufferType bufferType,
                                        bool normalized) {
   elements.push_back({count, GL_UNSIGNED_BYTE, normalized, bufferType});
   stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}

template<>
inline void VertexBufferLayout::push<int>(unsigned int count, BufferType bufferType,
                                          bool normalized) {
   elements.push_back({count, GL_INT, normalized, bufferType});
   stride += count * VertexBufferElement::getSizeOfType(GL_INT);
}


#endif //GAMEENGINE_VERTEXBUFFERLAYOUT_HPP
