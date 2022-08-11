/*
-----------------------------------------------------------------------------------
Nom du fichier  : IWindow.hpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_IWINDOW_HPP
#define GAMEENGINE_IWINDOW_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace GE{

   struct SWindowCreateInfo {
      int windowWidth;
      int windowHeight;
      const char* windowTitle;
   };

   class IWindow {
   public:
      virtual ~IWindow() = default;
      virtual void initialize(const SWindowCreateInfo& windowInfos) = 0;
      virtual void release() = 0;

      GLFWwindow* getHandle();
   protected:
      GLFWwindow* pWindow = nullptr;
   };
}
#endif //GAMEENGINE_IWINDOW_HPP
