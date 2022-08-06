/*
-----------------------------------------------------------------------------------
Nom du fichier  : OpenGl33Window.hpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_OPENGL33WINDOW_HPP
#define GAMEENGINE_OPENGL33WINDOW_HPP

#include <Rendering/Renderer/IWindow.hpp>

namespace GE{
   class OpenGl33Window : public IWindow {
   public:
      ~OpenGl33Window() override;

      void initialize(const SWindowCreateInfo &windowInfos) final;
      void release() final;
   };
}



#endif //GAMEENGINE_OPENGL33WINDOW_HPP
