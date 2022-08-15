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


private:
   unsigned int height{};
   unsigned int width{};
   std::string title;
   GLFWwindow* window;
   EventCallbackFn eventCallback;

   static void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
   static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
   static void keyboardCallback(GLFWwindow *window, float deltaTime);
   static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

};


#endif //GAMEENGINE_WINDOW_HPP
