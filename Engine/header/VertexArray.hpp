/*
-----------------------------------------------------------------------------------
Nom du fichier  : VertexArray.hpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_VERTEXARRAY_HPP
#define GAMEENGINE_VERTEXARRAY_HPP


#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
public:
   VertexArray();
   ~VertexArray();

   void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

   void bind() const;
   static void unbind();

private:
   unsigned int rendererID;
};


#endif //GAMEENGINE_VERTEXARRAY_HPP
