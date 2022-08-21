//
// Created by luca on 18/08/22.
//

#ifndef SANDBOX_MODELLOADER_HPP
#define SANDBOX_MODELLOADER_HPP


#include <Scene/BaseComponents/MeshComponent.hpp>
#include <Scene/Scene.hpp>
#include <Scene/BaseComponents/MaterialComponent.hpp>
#include "assimp/scene.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool
gamma = false);

class ModelLoader {
public:
   ModelLoader(const std::string &path, GE::Scene* gameScene);

private:
   GE::Scene* gameScene;
   std::string directory;
   std::vector<GE::Texture> textures_loaded;
   bool gammaCorrection;

   void processNode(aiNode *node, const aiScene *scene);

   void processMesh(aiMesh *mesh, const aiScene *scene, GE::Entity& entity);

   // checks all material textures of a given type and loads the textures if they're not loaded yet.
   // the required info is returned as a Texture struct.
   std::vector<GE::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         GE::TextureType typeName);

};


#endif //SANDBOX_MODELLOADER_HPP
