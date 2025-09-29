/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "assetInspector.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "../../imgui/helper.h"
#include "../../../context.h"
#include "../../../utils/textureFormats.h"

using FileType = Project::AssetManager::FileType;

int Selecteditem  = 0;

Editor::AssetInspector::AssetInspector() {
}

void Editor::AssetInspector::draw() {
  if (ctx.selAssetUUID == 0) {
    ImGui::Text("No Asset selected");
    return;
  }

  auto asset = ctx.project->getAssets().getEntryByUUID(ctx.selAssetUUID);
  if (!asset) {
    ctx.selAssetUUID = 0;
    return;
  }

  ImGui::Text("File: %s", asset->name.c_str());
  //ImGui::Text("Path: %s", asset->path.c_str());

  ImGui::Separator();

  ImGui::InpTable::start("Settings");
  if (asset->type == FileType::IMAGE) {
    ImGui::InpTable::addComboBox("Format", Selecteditem, Utils::TEX_TYPES, Utils::TEX_TYPE_COUNT);
  }

  int idxCompr = static_cast<int>(asset->compression) + 1;
  const char* const ComprItems[] = {
    "Project Default", "None",
    "Level 1 - Fast",
    "Level 2 - Good",
    "Level 3 - High",
  };
  ImGui::InpTable::addComboBox("Compression", idxCompr, ComprItems, 5);
  asset->compression = static_cast<Project::ComprTypes>(idxCompr - 1);

  ImGui::InpTable::end();

  if (asset->type == FileType::IMAGE && asset->texture) {
    ImGui::Separator();
    ImGui::Image(ImTextureRef(asset->texture->getGPUTex()), asset->texture->getSize(4.0f));
    ImGui::Text("%dx%dpx", asset->texture->getWidth(), asset->texture->getHeight());
  }
}
