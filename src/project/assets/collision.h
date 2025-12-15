/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <string>
#include <vector>
#include "glm/vec3.hpp"

namespace Project::Assets
{
  struct CollisionMesh
  {
    std::vector<glm::vec3> verticesFloat{};
    std::vector<glm::ivec3> vertices{};
    std::vector<glm::ivec3> normals{};
    std::vector<uint16_t> indices{};

    void fromGLTF(const std::string &path);
  };
}
