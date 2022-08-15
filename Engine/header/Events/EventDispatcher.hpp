/*
-----------------------------------------------------------------------------------
Nom du fichier  : EventDispatcher.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_EVENTDISPATCHER_HPP
#define GAMEENGINE_EVENTDISPATCHER_HPP


#include "Event.hpp"

class EventDispatcher {
public:
   explicit EventDispatcher(Event& event);

   template<typename T, typename F>
   bool dispatch(const F& func){
      if(event.getEventType() == T::getStaticType()){
         event.handled = true;
         func(static_cast<T&>(event));
         return true;
      }
      return false;
   }

private:
   Event& event;
};


#endif //GAMEENGINE_EVENTDISPATCHER_HPP
