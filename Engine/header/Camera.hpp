/*
-----------------------------------------------------------------------------------
Nom du fichier  : Camera.hpp
Auteur(s)       : lucac
Date creation   : 14.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef GAMEENGINE_CAMERA_HPP
#define GAMEENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.hpp>



enum class CameraMovement {
   FORWARD,
   BACKWARD,
   LEFT,
   RIGHT
};

class Camera {
public:
   explicit Camera(glm::vec3 position);

   void onUpdate(Shader &shader) const;

   void init(Shader &shader) const;

   void processKeyboard(CameraMovement direction, float deltaTime);

   void processMouseScroll(float yoffset);

   glm::mat4 getViewMatrix() const;

   void processMouseMovement(float xoffset, float yoffset, GLboolean
   constrainPitch = true);

private:
   void updateCameraVectors();

   // camera Attributes
   glm::vec3 position;
   glm::vec3 front;
   glm::vec3 up;
   glm::vec3 right;
   glm::vec3 worldUp;
   // euler Angles
   float yaw;
   float pitch;
   // camera options
   float movementSpeed;
   float mouseSensitivity;
   float zoom;
public:
   float getZoom() const;

private:
   float speed = 1.0f;

   static const float YAW;
   static const float PITCH;
   static const float SPEED;
   static const float SENSITIVITY;
   static const float ZOOM;

};





#endif //GAMEENGINE_CAMERA_HPP
