/*
-----------------------------------------------------------------------------------
Nom du fichier  : MouseEvent.hpp
Auteur(s)       : lucac
Date creation   : 15.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_MOUSEEVENT_HPP
#define GAMEENGINE_MOUSEEVENT_HPP

#include <MouseCode.hpp>
#include <sstream>
#include "Event.hpp"

class MouseMovedEvent : public Event {
public:
   MouseMovedEvent(const float x, const float y)
      : mouseX(x), mouseY(y) {}

   [[nodiscard]] float GetX() const { return mouseX; }

   [[nodiscard]] float GetY() const { return mouseY; }

   [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
      return ss.str();
   }

   EVENT_CLASS_TYPE(MouseMoved)

private:
   float mouseX;
   float mouseY;
};

class MouseScrolledEvent : public Event {
public:
   MouseScrolledEvent(const float xOffset, const float yOffset)
      : xOffset(xOffset), yOffset(yOffset) {}

   [[nodiscard]] float GetXOffset() const { return xOffset; }
   [[nodiscard]] float GetYOffset() const { return yOffset; }

   [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
      return ss.str();
   }

   EVENT_CLASS_TYPE(MouseScrolled)

private:
   float xOffset;
   float yOffset;
};

class MouseButtonEvent : public Event {
public:
   [[nodiscard]] MouseCode GetMouseButton() const { return button; }

protected:
   explicit MouseButtonEvent(MouseCode button);

   MouseCode button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
   explicit MouseButtonPressedEvent(MouseCode button);


   [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "MouseButtonPressedEvent: " << button;
      return ss.str();
   }

   EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
   explicit MouseButtonReleasedEvent(MouseCode button);

   [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "MouseButtonReleasedEvent: " << button;
      return ss.str();
   }

   EVENT_CLASS_TYPE(MouseButtonReleased)
};

#endif //GAMEENGINE_MOUSEEVENT_HPP
