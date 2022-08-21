/*
-----------------------------------------------------------------------------------
Nom du fichier  : TagComponent.hpp
Auteur(s)       : lucac
Date creation   : 21.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef SANDBOX_TAGCOMPONENT_HPP
#define SANDBOX_TAGCOMPONENT_HPP
namespace GE {
   struct TagComponent{
      std::string tag;

      TagComponent() = default;
      TagComponent(std::string tag) : tag(move(tag)){}
   };
};

#endif //SANDBOX_TAGCOMPONENT_HPP
