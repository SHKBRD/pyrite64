/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <cstdint>

namespace P64::DrawLayer
{
  struct Conf
  {
    static constexpr uint32_t FLAG_Z_WRITE = 1 << 0;
    static constexpr uint32_t FLAG_Z_COMPARE = 1 << 1;

    uint32_t flags{};
    uint32_t blender{};
  };

  struct Setup
  {
    uint8_t layerCount3D{};
    uint8_t layerCountPtx{};
    uint8_t layerCount2D{};
    uint8_t padding{};
    Conf layerConf[16]{};
  };

  void init(Setup &setup);

  void use(uint32_t idx);

  inline void use3D(uint32_t idx) { use(idx); }
  void usePtx(uint32_t idx = 0);
  void use2D(uint32_t idx = 0);

  inline void useDefault() { use(0); }


  void draw(uint32_t layerIdx);

  void draw3D();
  void drawPtx();
  void draw2D();

  void nextFrame();
  void reset();
}
