/*
-----------------------------------------------------------------------------------
Nom du fichier  : IWindow.cpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Rendering/Renderer/IWindow.hpp"

namespace GE{
   GLFWwindow *IWindow::getHandle() {
      return pWindow;
   }
}