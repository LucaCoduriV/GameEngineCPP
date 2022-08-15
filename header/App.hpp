/*
-----------------------------------------------------------------------------------
Nom du fichier  : App.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_APP_HPP
#define GAMEENGINE_APP_HPP


#include <Events/ApplicationEvent.hpp>
#include "Window.hpp"
#include "Layer.hpp"

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

class App {
public:
   App();
   virtual ~App();
   void onEvent(Event& e);
   [[noreturn]] void run();
   void pushLayer(Layer* layer);
   bool onWindowClose(WindowCloseEvent& e);
private:
   Window window;
   bool running = true;
   float lastFrameTime = 0.0f;
   std::vector<Layer*> layers;

};


#endif //GAMEENGINE_APP_HPP
