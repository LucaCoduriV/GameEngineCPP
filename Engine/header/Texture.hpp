/*
-----------------------------------------------------------------------------------
Nom du fichier  : Texture.hpp
Auteur(s)       : lucac
Date creation   : 13.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_TEXTURE_HPP
#define GAMEENGINE_TEXTURE_HPP

#include <string>

class Texture {
public:
   explicit Texture(std::string path);

   ~Texture();

   void bind(unsigned int slot = 0) const;
   static void unbind();

private:
   unsigned int rendererID = 0;
   std::string filePath;
   unsigned char* localBuffer = nullptr;
   int width = 0;
   int height = 0;
   int bpp = 0;
};


#endif //GAMEENGINE_TEXTURE_HPP
