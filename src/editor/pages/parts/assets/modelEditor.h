/**
* @copyright 2026 - Max Bebök
* @license MIT
*/
#pragma once
#include <cstdint>
#include "imgui.h"

namespace Editor
{
  class ModelEditor
  {
    private:
      uint64_t assetUUID{};

    public:
      explicit ModelEditor(uint64_t assetUUID) : assetUUID(assetUUID) {}

      bool draw(ImGuiID defDockId);
  };
}
