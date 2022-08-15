/*
-----------------------------------------------------------------------------------
Nom du fichier  : Texture.cpp
Auteur(s)       : lucac
Date creation   : 13.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <Renderer.hpp>
#include "Texture.hpp"
#include "vendor/stb_image/stb_image.h"
#include <iostream>

Texture::Texture(std::filesystem::path path) : filePath(std::move(path)) {
   stbi_set_flip_vertically_on_load(1);

   GLCall(glGenTextures(1, &rendererID));
   GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

   GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
   GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
   GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
   GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));


   localBuffer = stbi_load(filePath.string().c_str(), &width, &height, &bpp, 4);
   if (localBuffer)
   {
      GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
                          GL_UNSIGNED_BYTE, localBuffer));
      GLCall(glGenerateMipmap(GL_TEXTURE_2D));
      unbind();
   }
   else
   {
      std::cout << "\nError: Failed to load texture" << std::endl;
      std::cout << stbi_failure_reason() << std::endl;
      __debugbreak();
   }
   stbi_image_free(localBuffer);

}

void Texture::bind(unsigned int slot) const {
   GLCall(glActiveTexture(GL_TEXTURE0 + slot));
   GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void Texture::unbind() {
   GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture() {
   GLCall(glDeleteTextures(1, &rendererID));
}
