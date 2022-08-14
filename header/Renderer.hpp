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

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) GLClearError(); \
   x;                             \
   ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class Renderer{
public:
   void draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader);
   void draw(const VertexArray &va, Shader &shader, int count);
   void clear();
private:
};

#endif //GAMEENGINE_RENDERER_HPP
