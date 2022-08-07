/*
-----------------------------------------------------------------------------------
Nom du fichier  : IRenderer.cpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Rendering/Renderer/IRenderer.hpp"

GE::IWindow *GE::IRenderer::getWindow() {
   return pWindow;
}
