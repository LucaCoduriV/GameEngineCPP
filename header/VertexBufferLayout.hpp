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

struct VertexBufferElement {
   unsigned int count;
   unsigned int type;
   bool normalized;

   static unsigned int getSizeOfType(unsigned int type) {
      switch(type) {
         case GL_FLOAT:
            return sizeof(GLfloat);
         case GL_UNSIGNED_INT:
            return sizeof(GLuint);
         case GL_UNSIGNED_BYTE:
            return sizeof(GLubyte);
      }
      throw std::runtime_error("The type is not supported");
   };

};

class VertexBufferLayout {
public:
   VertexBufferLayout() : stride(0) {}

   template<typename T>
   inline void push(unsigned int count);

   [[nodiscard]] inline const std::vector<VertexBufferElement> &GetElements() const {
      return elements;
   }

   [[nodiscard]] inline unsigned int getStride() const { return stride; }

private:
   std::vector<VertexBufferElement> elements;
   unsigned int stride;
};

template<typename T>
inline void VertexBufferLayout::push(unsigned int) {
   throw std::runtime_error("The type is not supported");
}

template<>
inline void VertexBufferLayout::push<float>(unsigned int count) {
   elements.push_back({count, GL_FLOAT, false});
   stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count) {
   elements.push_back({count, GL_UNSIGNED_INT, false});
   stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count) {
   elements.push_back({count, GL_UNSIGNED_BYTE, true});
   stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}


#endif //GAMEENGINE_VERTEXBUFFERLAYOUT_HPP
