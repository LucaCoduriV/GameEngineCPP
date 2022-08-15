/*
-----------------------------------------------------------------------------------
Nom du fichier  : ApplicationEvent.cpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <sstream>
#include "Events/ApplicationEvent.hpp"

WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
:height(height), width(width) {

}

unsigned int WindowResizeEvent::getHeight() const {
   return height;
}

unsigned int WindowResizeEvent::getWidth() const {
   return width;
}

std::string WindowResizeEvent::toString() const {
   std::stringstream ss;
   ss << "WindowResizeEvent: " << width << ", " << height;
   return ss.str();
}

