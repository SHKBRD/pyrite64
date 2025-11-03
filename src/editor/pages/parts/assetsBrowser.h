/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "../../../renderer/texture.h"

namespace Editor
{
  class AssetsBrowser
  {
    private:
      int activeTab{0};

    public:
      void draw();
  };
}