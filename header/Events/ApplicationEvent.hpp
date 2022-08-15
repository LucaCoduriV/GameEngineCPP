/*
-----------------------------------------------------------------------------------
Nom du fichier  : ApplicationEvent.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_APPLICATIONEVENT_HPP
#define GAMEENGINE_APPLICATIONEVENT_HPP

#include <Events/Event.hpp>

class WindowResizeEvent : public Event {
public:
   WindowResizeEvent(unsigned int width, unsigned int height);

   [[nodiscard]] unsigned int getHeight() const;

   [[nodiscard]] unsigned int getWidth() const;

   [[nodiscard]] std::string toString() const override;

   EVENT_CLASS_TYPE(WindowResize)

private:
   unsigned int height;
   unsigned int width;
};

class WindowCloseEvent : public Event
{
public:
   WindowCloseEvent() = default;

   EVENT_CLASS_TYPE(WindowClose)
};

class AppTickEvent : public Event
{
public:
   AppTickEvent() = default;

   EVENT_CLASS_TYPE(AppTick)
};

class AppUpdateEvent : public Event
{
public:
   AppUpdateEvent() = default;

   EVENT_CLASS_TYPE(AppUpdate)
};

class AppRenderEvent : public Event
{
public:
   AppRenderEvent() = default;

   EVENT_CLASS_TYPE(AppRender)
};


#endif //GAMEENGINE_APPLICATIONEVENT_HPP
