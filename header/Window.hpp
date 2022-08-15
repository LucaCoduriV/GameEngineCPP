/*
-----------------------------------------------------------------------------------
Nom du fichier  : Window.hpp
Auteur(s)       : lucac
Date creation   : 14.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_WINDOW_HPP
#define GAMEENGINE_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Events/Event.hpp"

class Window {
public:
   using EventCallbackFn = std::function<void(Event&)>;

   Window(std::string title, unsigned int height, unsigned int width);

   [[nodiscard]] unsigned int getHeight() const;
   [[nodiscard]] unsigned int getWidth() const;

   void onUpdate();
   void SetEventCallback(const EventCallbackFn& callback);
   [[nodiscard]] GLFWwindow* getWindowHandler() const;

private:
   unsigned int height{};
   unsigned int width{};
   std::string title;
   GLFWwindow* window;

   struct WindowData
   {
      std::string title;
      unsigned int width;
      unsigned int height;
      bool vSync;

      EventCallbackFn eventCallback;
   };

   WindowData data;

};


#endif //GAMEENGINE_WINDOW_HPP
