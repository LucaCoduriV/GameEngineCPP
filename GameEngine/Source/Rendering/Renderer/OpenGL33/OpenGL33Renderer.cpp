/*
-----------------------------------------------------------------------------------
Nom du fichier  : OpenGL33Renderer.cpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <iostream>
#include <valarray>
#include "Rendering/Renderer/OpenGL33/OpenGL33Renderer.hpp"


GE::OpenGL33Renderer::~OpenGL33Renderer() {
   release();
}

void GE::OpenGL33Renderer::initialize(const GE::SRendererCreateInfo &createInfo) {
   if (isInitialized) release();


   window.initialize(*createInfo.windowCreateInfo);
   pWindow = &window;
   isInitialized = true;

   shader = std::make_unique<Shader>(
      R"(B:\Users\lucac\Documents\GitHub\GameEngine\GameEngine)"
      R"(\Source\Shader\Files\vertex.glsl)",
      R"(B:\Users\lucac\Documents\GitHub\GameEngine\GameEngine\Source\Shader\Files\fragment.glsl)");


   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) 0);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                         (void *) (3 * sizeof(float)));

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);

   // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 1);

   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   std::cout << "OpenGL 3.3 renderer initialized." << std::endl;
}

void GE::OpenGL33Renderer::render(float lag) {
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   shader->use();

   //generate color from actual time
   float timeValue = glfwGetTime();
   float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
   shader->setFloat("ourColor", greenValue);


   // render the triangle

   glBindVertexArray(VAO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int),
                  GL_UNSIGNED_INT, 0);
}

void GE::OpenGL33Renderer::release() {
   if (!isInitialized) return;

   window.release();
   pWindow = nullptr;
   isInitialized = false;
   std::cout << "OpenGL 3.3 renderer released." << std::endl;
}