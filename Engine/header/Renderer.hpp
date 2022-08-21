/*
-----------------------------------------------------------------------------------
Nom du fichier  : Renderer.hpp
Auteur(s)       : lucac
Date creation   : 12.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_RENDERER_HPP
#define GAMEENGINE_RENDERER_HPP

#include <GL/glew.h>
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"



class Renderer{
public:
   void draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader);
   void draw(const VertexArray &va, Shader &shader, int count);
   void clear();
private:
};

#endif //GAMEENGINE_RENDERER_HPP
