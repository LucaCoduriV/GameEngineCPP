/*
-----------------------------------------------------------------------------------
Nom du fichier  : Event.hpp
Auteur(s)       : lucac
Date creation   : 14.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_EVENT_HPP
#define GAMEENGINE_EVENT_HPP

#include <string>

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


enum class EventType {
   None = 0,
   WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
   AppTick, AppUpdate, AppRender,
   KeyPressed, KeyReleased, KeyTyped,
   MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return \
EventType::type; }\
								virtual EventType getEventType() const override { return         \
                        getStaticType(); }\
								virtual const char* getName() const override { return            \
								#type; }

class Event {
   friend class EventDispatcher;
public:
   virtual ~Event() = default;
   [[nodiscard]] virtual EventType getEventType() const = 0;
   [[nodiscard]] virtual const char* getName() const = 0;
   virtual std::string toString() const;



protected:
   bool handled = false;
};


#endif //GAMEENGINE_EVENT_HPP
