/*
-----------------------------------------------------------------------------------
Nom du fichier  : KeyEvent.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_KEYEVENT_HPP
#define GAMEENGINE_KEYEVENT_HPP

#include <KeyCode.hpp>
#include <sstream>
#include "Event.hpp"

class KeyEvent : public Event
{
public:
   [[nodiscard]] KeyCode GetKeyCode() const { return keyCode; }

protected:
   KeyEvent(const KeyCode keycode)
      : keyCode(keycode) {}

   KeyCode keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
   explicit KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
      : KeyEvent(keycode), m_IsRepeat(isRepeat) {}

   [[nodiscard]] bool IsRepeat() const { return m_IsRepeat; }

   [[nodiscard]] std::string toString() const override
   {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << keyCode << " (repeat = " << m_IsRepeat << ")";
      return ss.str();
   }

   EVENT_CLASS_TYPE(KeyPressed)
private:
   bool m_IsRepeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
   explicit KeyReleasedEvent(const KeyCode keycode)
      : KeyEvent(keycode) {}

   [[nodiscard]] std::string toString() const override
   {
      std::stringstream ss;
      ss << "KeyReleasedEvent: " << keyCode;
      return ss.str();
   }

   EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
public:
   explicit KeyTypedEvent(const KeyCode keycode)
      : KeyEvent(keycode) {}

   [[nodiscard]] std::string toString() const override
   {
      std::stringstream ss;
      ss << "KeyTypedEvent: " << keyCode;
      return ss.str();
   }

   EVENT_CLASS_TYPE(KeyTyped)
};

#endif //GAMEENGINE_KEYEVENT_HPP
