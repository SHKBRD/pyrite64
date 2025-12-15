/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "projectBuilder.h"
#include "../utils/string.h"
#include <filesystem>

#include "../utils/binaryFile.h"
#include "../utils/fs.h"
#include "../utils/logger.h"
#include "tiny3d/tools/gltf_importer/src/parser.h"

namespace fs = std::filesystem;

namespace
{

}

void Build::buildT3DMAssets(Project::Project &project, SceneCtx &sceneCtx)
{
  auto &models = sceneCtx.project->getAssets().getTypeEntries(Project::AssetManager::FileType::MODEL_3D);
  for (auto &model : models)
  {
    Utils::Logger::log("Building 3D Model Asset: " + model.path + " | rom: " + model.outPath);

    T3DM::config = {
      .globalScale = (float)model.conf.baseScale,
      .animSampleRate = 60,
      //.ignoreMaterials = args.checkArg("--ignore-materials"),
      //.ignoreTransforms = args.checkArg("--ignore-transforms"),
      .createBVH = model.conf.gltfBVH,
      .verbose = false,
      .assetPath = "assets/",
      .assetPathFull = fs::absolute(project.getPath() + "/assets").string(),
    };

    auto t3dm = T3DM::parseGLTF(model.path.c_str());
    auto projectPath = fs::path{project.getPath()};
    auto t3dmPath = projectPath / model.outPath;
    T3DM::writeT3DM(t3dm, t3dmPath.c_str(), projectPath, {});
  }
}