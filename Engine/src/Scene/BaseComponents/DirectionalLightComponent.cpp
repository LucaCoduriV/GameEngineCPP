/*
-----------------------------------------------------------------------------------
Nom du fichier  : DirectionalLightComponent.cpp
Auteur(s)       : lucac
Date creation   : 28.08.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#include <Scene/BaseComponents/DirectionalLightComponent.hpp>

void GE::DirLightComponent::sendToShader(Shader &shader) const  {
   shader.setFloat("u_dirLight.direction", direction.x, direction.y, direction.z);
   shader.setFloat("u_dirLight.ambient", ambient.x, ambient.y, ambient.z);
   shader.setFloat("u_dirLight.diffuse", diffuse.x, diffuse.y, diffuse.z);
   shader.setFloat("u_dirLight.specular", specular.x, specular.y, specular.z);
}

