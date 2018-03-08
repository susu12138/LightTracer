#ifndef COMMON_H
#define COMMON_H

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// 顶点数据
typedef struct {
  // 位置信息
  glm::vec3 position;
  // 点法向
  glm::vec3 normal;
  // 纹理坐标， 未被使用
  glm::vec2 texCoords;
  // color
  glm::vec3 color;
} Vertex;

// 材质
typedef struct{
    // ambient color
    glm::vec3 ambient;
    // Diffuse color
    glm::vec3 diffuse;
    // Specular color
    glm::vec3 specular;
    // Emissive color
    glm::vec3 emissive;
    // Transparent color
    glm::vec3 transparent;
    // Shininess
    float shininess;
} Material;

// 光源
typedef struct{
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
} Light;

// 存放从模型中载入的网格数据
class Mesh {
public:
  /*  Mesh Data  */
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  
  /* Materials */
  Material material;

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material) {
    this->vertices = vertices;
    this->indices = indices;
    this->material = material;
  }
};

// 场景
class Scene{
public:
    /* Mesh */
    std::vector<Mesh> mMeshes;

    /* Light */
    std::vector<Light> mLights;

    void AddLight(const Light &light){
      mLights.push_back(light);
    }

    void AddMesh(const Mesh &mesh){
      mMeshes.push_back(mesh);
    }    
};
#endif