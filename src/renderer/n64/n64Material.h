/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "../n64Mesh.h"
#include "tiny3d/tools/gltf_importer/src/structs.h"

namespace Renderer::N64Material
{
  void convert(N64Mesh::MeshPart &part, const T3DM::Material &t3dMat);
}
