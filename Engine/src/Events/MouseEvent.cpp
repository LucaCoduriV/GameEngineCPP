/*
-----------------------------------------------------------------------------------
Nom du fichier  : MouseEvent.cpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Events/MouseEvent.hpp"

MouseButtonEvent::MouseButtonEvent(MouseCode button) : button(button) {}

MouseButtonReleasedEvent::MouseButtonReleasedEvent(MouseCode button)
   : MouseButtonEvent(button) {}

MouseButtonPressedEvent::MouseButtonPressedEvent(MouseCode button)
   : MouseButtonEvent(button) {}
