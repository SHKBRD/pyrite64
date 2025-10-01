/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "sceneInspector.h"
#include "../../../context.h"
#include "imgui.h"
#include "../../../utils/color.h"
#include "misc/cpp/imgui_stdlib.h"
#include "../../imgui/helper.h"

Editor::SceneInspector::SceneInspector() {
}

void Editor::SceneInspector::draw() {
  auto scene = ctx.project->getScenes().getLoadedScene();
  if(!scene)return;

  if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::InpTable::start("Settings");
    ImGui::InpTable::addString("Name", scene->conf.name);

    ImGui::InpTable::end();
  }

  if (ImGui::CollapsingHeader("Framebuffer", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::InpTable::start("Framebuffer");

    ImGui::InpTable::addInputInt("Width", scene->conf.fbWidth);
    ImGui::InpTable::addInputInt("Height", scene->conf.fbHeight);

    constexpr char* const FORMATS[] = {"RGBA16","RGBA32"};
    ImGui::InpTable::addComboBox("Format", scene->conf.fbFormat, FORMATS, 2);

    ImGui::InpTable::addColor("Color", scene->conf.clearColor, false);
    scene->conf.clearColor.a = 1.0f;

    ImGui::InpTable::addCheckBox("Clear Color", scene->conf.doClearColor);
    ImGui::InpTable::addCheckBox("Clear Depth", scene->conf.doClearDepth);
    ImGui::InpTable::end();
  }
}
