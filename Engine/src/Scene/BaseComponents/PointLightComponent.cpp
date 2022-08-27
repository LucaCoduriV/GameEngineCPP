/*
-----------------------------------------------------------------------------------
Nom du fichier  : PointLightComponent.cpp
Auteur(s)       : lucac
Date creation   : 27.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include "Scene/BaseComponents/PointLightComponent.hpp"
namespace GE{
   void PointLightComponent::sendToShader(Shader &shader) const {
      shader.setFloat("u_pointLights[0].position", position.x, position.y, position.z);
      shader.setFloat("u_pointLights[0].ambient", ambient.x, ambient.y, ambient.z);
      shader.setFloat("u_pointLights[0].diffuse", diffuse.x, diffuse.y, diffuse.z);
      shader.setFloat("u_pointLights[0].specular", specular.x, diffuse.y, diffuse.z);
      shader.setFloat("u_pointLights[0].constant", constant);
      shader.setFloat("u_pointLights[0].linear", linear);
      shader.setFloat("u_pointLights[0].quadratic", quadratic);
   }
}
