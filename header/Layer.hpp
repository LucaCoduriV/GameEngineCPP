/*
-----------------------------------------------------------------------------------
Nom du fichier  : Layer.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_LAYER_HPP
#define GAMEENGINE_LAYER_HPP


#include <string>
#include <Events/Event.hpp>

class Layer {
public:
   explicit Layer(std::string name = "Layer");
   virtual ~Layer() = default;

   virtual void onAttach() {}
   virtual void onDetach() {}
   virtual void onUpdate(float timeStamp) {}
   virtual void onImGuiRender() {}
   virtual void onEvent(Event& event) {}

   const std::string& getName();

protected:
   std::string name;
};


#endif //GAMEENGINE_LAYER_HPP
