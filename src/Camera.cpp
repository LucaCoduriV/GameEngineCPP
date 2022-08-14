/*
-----------------------------------------------------------------------------------
Nom du fichier  : Camera.cpp
Auteur(s)       : lucac
Date creation   : 14.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Camera.hpp"


const float Camera::YAW = -90.0f;
const float Camera::PITCH = 0.0f;
const float Camera::SPEED = 2.5f;
const float Camera::SENSITIVITY = 0.1f;
const float Camera::ZOOM = 45.0f;

Camera::Camera(glm::vec3 position) :
   position(position),
   worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(YAW),
   pitch(PITCH), front(glm::vec3(0.0f, 0.0f, -1.0f)),
   movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
   updateCameraVectors();
}

void Camera::updateCameraVectors() {
   // calculate the new Front vector
   glm::vec3 _front;
   _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
   _front.y = sin(glm::radians(pitch));
   _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
   front = glm::normalize(_front);
   // also re-calculate the Right and Up vector
   right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors,
   // because their length gets closer to 0 the more you look up or down which results in slower movement.
   up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const {
   return glm::lookAt(position, position + front, up);
}

void Camera::onUpdate(Shader &shader) const {
   const int screenWidth = 800;
   const int screenHeight = 600;

   auto view = getViewMatrix();

   shader.setMat4f("u_view", view);
   auto proj = glm::perspective(glm::radians(zoom),
                                (float) screenWidth / (float) screenHeight,
                                0.1f, 100.0f);
   shader.setMat4f("u_proj", proj);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
   float velocity = movementSpeed * deltaTime;
   if (direction == FORWARD)
      position += front * velocity;
   if (direction == BACKWARD)
      position -= front * velocity;
   if (direction == LEFT)
      position -= right * velocity;
   if (direction == RIGHT)
      position += right * velocity;
}

void Camera::processMouseScroll(float yOffset) {
   zoom -= yOffset;
   if (zoom < 1.0f)
      zoom = 1.0f;
   if (zoom > 45.0f)
      zoom = 45.0f;
}

void Camera::processMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch) {
   xoffset *= mouseSensitivity;
   yoffset *= mouseSensitivity;

   yaw += xoffset;
   pitch += yoffset;

   // make sure that when pitch is out of bounds, screen doesn't get flipped
   if (constrainPitch) {
      if (pitch > 89.0f)
         pitch = 89.0f;
      if (pitch < -89.0f)
         pitch = -89.0f;
   }

   // update Front, Right and Up Vectors using the updated Euler angles
   updateCameraVectors();
}

float Camera::getZoom() const {
   return zoom;
}
