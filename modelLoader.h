#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <iostream>
#include <string>
#include <vector>

#include "assimp/Importer.hpp"  // C++ importer interface
#include "assimp/postprocess.h" // Post processing fla
#include "assimp/scene.h"       // Output data structure

#include "common.h"

void aiColorToVec3(glm::vec3 &vec3, const aiColor3D &color);
void aiVectorToVec3(glm::vec3 &vec3, const aiVector3D &aiVec3);

class ModelLoader {
public:
  ModelLoader(std::string path);

  const Scene &GetSceneData();

private:
  /* Scene data */
  Scene mScene;

private:
  void loadModel(std::string path);
  void processLight(const aiScene *scene);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};
#endif