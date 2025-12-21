/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <cstdint>

namespace P64::DrawLayer
{
  void init(uint32_t layerCount);

  void use(uint32_t idx);
  inline void useDefault() { use(0); }

  void drawAll();
  void draw(uint32_t layerIdx);
  void nextFrame();

  constexpr uint32_t LAYER_OPAQUE = 0;
  constexpr uint32_t LAYER_TRANS = 1;
  constexpr uint32_t LAYER_2D = 2;
}
