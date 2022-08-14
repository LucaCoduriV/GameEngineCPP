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


void Camera::onUpdate(Shader& shader) const {
   auto view = glm::mat4(1.0f);
   view = glm::rotate(view, glm::radians(xRotation),
                      glm::vec3(1.0f, 0.0f, 0.0f));
   view = glm::rotate(view, glm::radians(yRotation),
                      glm::vec3(0.0f, 1.0f, 0.0f));
   view = glm::rotate(view, glm::radians(zRotation),
                      glm::vec3(0.0f, 0.0f, 1.0f));
   view = glm::translate(view, glm::vec3(xTranslation, yTranslation,
                                              zTranslation));

   shader.setMat4f("u_view", view);
}


Camera::Camera(const glm::mat4& projection) : projection(projection) {

}

void Camera::setXRotation(float x) {
   xRotation = x;
}

void Camera::setYRotation(float y) {
   yRotation = y;
}

void Camera::setZRotation(float z) {
   zRotation = z;
}

void Camera::setXTranslation(float x) {
   xTranslation = x;
}

void Camera::setYTranslation(float y) {
   yTranslation = y;
}

void Camera::setZTranslation(float z) {
   zTranslation = z;
}

float Camera::getXRotation() const {
   return xRotation;
}

float Camera::getYRotation() const {
   return yRotation;
}

float Camera::getZRotation() const {
   return zRotation;
}

float Camera::getXTranslation() const {
   return xTranslation;
}

float Camera::getYTranslation() const {
   return yTranslation;
}

float Camera::getZTranslation() const {
   return zTranslation;
}

void Camera::init(Shader &shader) const {
   shader.setMat4f("u_proj", projection);
}
