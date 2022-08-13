/*
-----------------------------------------------------------------------------------
Nom du fichier  : IndexBuffer.hpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_INDEXBUFFER_HPP
#define GAMEENGINE_INDEXBUFFER_HPP


class IndexBuffer {
public:
   IndexBuffer(const unsigned int* data, unsigned int count);
   ~IndexBuffer();

   void bind() const;
   static void unbind();
private:
   unsigned int rendererID = 0;
   unsigned int count;
};


#endif //GAMEENGINE_INDEXBUFFER_HPP
