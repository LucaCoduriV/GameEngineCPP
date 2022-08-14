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

class Camera {
public:
   explicit Camera(const glm::mat4& projection);
   void onUpdate(Shader& shader) const;

   void setXRotation(float x);
   void setYRotation(float y);
   void setZRotation(float z);

   void setXTranslation(float x);
   void setYTranslation(float y);
   void setZTranslation(float z);

private:
   glm::mat4 projection;

   float xRotation = 0;
   float yRotation = 0;
public:
   float getXRotation() const;

   float getYRotation() const;

   float getZRotation() const;

   float getXTranslation() const;

   float getYTranslation() const;

   float getZTranslation() const;

private:
   float zRotation = 0;

   float xTranslation = 0;
   float yTranslation = 0;
   float zTranslation = 0;
};


#endif //GAMEENGINE_CAMERA_HPP
