/*
-----------------------------------------------------------------------------------
Nom du fichier  : Layer.cpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Layer.hpp"

const std::string &Layer::getName() {
   return name;
}

Layer::Layer(std::string name):name(move(name)) {

}
