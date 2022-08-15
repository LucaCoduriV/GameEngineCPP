/*
-----------------------------------------------------------------------------------
Nom du fichier  : MouseCod.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_MOUSECODE_HPP
#define GAMEENGINE_MOUSECODE_HPP

#include <cstdint>

using MouseCode = uint16_t;


enum class Mouse : MouseCode {
   // From glfw3.h
   Button0 = 0,
   Button1 = 1,
   Button2 = 2,
   Button3 = 3,
   Button4 = 4,
   Button5 = 5,
   Button6 = 6,
   Button7 = 7,

   ButtonLast = Button7,
   ButtonLeft = Button0,
   ButtonRight = Button1,
   ButtonMiddle = Button2
};

#endif //GAMEENGINE_MOUSECODE_HPP
