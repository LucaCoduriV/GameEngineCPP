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
#include "Rendering/Renderer/OpenGL33/OpenGL33Renderer.hpp"

GE::OpenGL33Renderer::~OpenGL33Renderer() {
   release();
}

void GE::OpenGL33Renderer::initialize(const GE::SRendererCreateInfo &createInfo) {
   if(isInitialized) release();


   window.initialize(*createInfo.windowCreateInfo);
   pWindow = &window;
   isInitialized = true;

   std::cout << "OpenGL 3.3 renderer initialized." << std::endl;
}

void GE::OpenGL33Renderer::release() {
   if(!isInitialized) return;

   window.release();
   pWindow = nullptr;
   isInitialized = false;
   std::cout << "OpenGL 3.3 renderer released." << std::endl;
}
