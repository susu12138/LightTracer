#include "modelLoader.h"

ModelLoader::ModelLoader(std::string path) { loadModel(path); }

void ModelLoader::loadModel(std::string path) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate |
                                                             aiProcess_FlipUVs);

  if (!scene) {
    std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    return;
  }
  // process light
  processLight(scene);

  // process mesh
  processNode(scene->mRootNode, scene);
}

void ModelLoader::processLight(const aiScene *scene){
  Light light;
  for(unsigned int i = 0; i < scene->mNumLights; ++i){
    aiLight *pLight = scene->mLights[i];
    aiVectorToVec3(light.position, pLight->mPosition);
    aiVectorToVec3(light.direction, pLight->mDirection);
    aiColorToVec3(light.ambient, pLight->mColorAmbient);
    aiColorToVec3(light.diffuse, pLight->mColorDiffuse);
    aiColorToVec3(light.specular, pLight->mColorSpecular);

    this->mScene.AddLight(light);
  }
  return;
}

void ModelLoader::processNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    this->mScene.AddMesh(processMesh(mesh, scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; ++i) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  Material material;

  for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;
    // vertex postion
    glm::vec3 vect;
    vect.x = mesh->mVertices[i].x;
    vect.y = mesh->mVertices[i].y;
    vect.z = mesh->mVertices[i].z;
    vertex.position = vect;

    // normal
    vect.x = mesh->mNormals[i].x;
    vect.y = mesh->mNormals[i].y;
    vect.z = mesh->mNormals[i].z;
    vertex.normal = vect;

    // coordinates
    if (mesh->mTextureCoords[0]) {
      glm::vec2 vect;
      vect.x = mesh->mTextureCoords[0][i].x;
      vect.y = mesh->mTextureCoords[0][i].y;
      vertex.texCoords = vect;
    } else
      vertex.texCoords = glm::vec2(0.0f, 0.0f);

    vertices.push_back(vertex);
  }

  // process indices
  for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; ++j)
      indices.push_back(face.mIndices[j]);
  }

  // process material
  aiMaterial *pMaterial = scene->mMaterials[mesh->mMaterialIndex];
  aiColor3D color;
  // ambient
  pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);  
  aiColorToVec3(material.ambient, color);
  // diffuse
  pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);  
  aiColorToVec3(material.diffuse, color);
  // emissive
  pMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);  
  aiColorToVec3(material.emissive, color);
  // transparent
  pMaterial->Get(AI_MATKEY_COLOR_TRANSPARENT, color);  
  aiColorToVec3(material.transparent, color);
  // specular
  pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);  
  aiColorToVec3(material.transparent, color);
  // shininess
  pMaterial->Get(AI_MATKEY_SHININESS, material.shininess);

  return Mesh(vertices, indices, material);
}

const Scene& ModelLoader::GetSceneData() { return this->mScene; }

void aiColorToVec3(glm::vec3 &vec3, const aiColor3D &color){
  vec3.x = color.r;
  vec3.y = color.g;
  vec3.z = color.b;
}

void aiVectorToVec3(glm::vec3 &vec3, const aiVector3D &aiVec3){
  vec3.x = aiVec3.x;
  vec3.y = aiVec3.y;
  vec3.z = aiVec3.z;
}