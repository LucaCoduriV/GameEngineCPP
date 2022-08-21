//
// Created by luca on 18/08/22.
//

#ifndef SANDBOX_MODELLOADER_HPP
#define SANDBOX_MODELLOADER_HPP


#include <Scene/BaseComponents/MeshComponent.hpp>
#include "assimp/scene.h"
#include "Mesh.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool
gamma = false);

class ModelLoader {
public:
   ModelLoader(const std::string &path);

   void Draw(Shader &shader);

private:
   std::string directory;
   std::vector<STexture> textures_loaded;
   std::vector<GE::MeshComponent>    meshes;
   bool gammaCorrection;

   void processNode(aiNode *node, const aiScene *scene);

   GE::MeshComponent processMesh(aiMesh *mesh, const aiScene *scene);

   // checks all material textures of a given type and loads the textures if they're not loaded yet.
   // the required info is returned as a Texture struct.
   std::vector<STexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);

};


#endif //SANDBOX_MODELLOADER_HPP
