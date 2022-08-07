/*
-----------------------------------------------------------------------------------
Nom du fichier  : IRenderingEngine.cpp
Auteur(s)       : lucac
Date creation   : 07.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Rendering/IRenderingEngine.hpp"

GE::IRenderer *GE::IRenderingEngine::getRenderer() {
   return pRenderer;
}
