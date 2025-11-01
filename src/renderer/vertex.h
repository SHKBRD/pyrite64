/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Renderer
{
  struct Vertex
  {
    /* 0x00 */ glm::i16vec3 pos{}; // 16.0 fixed point
    /* 0x06 */ uint16_t norm{};    // 5,5,5 compressed normal
    /* 0x08 */ glm::u8vec4 color{};   // RGBA8 color
    /* 0x0C */ glm::i16vec2 uv{};  // 10.6 fixed point (pixel coords)
  };

  struct LineVertex
  {
    glm::vec3 pos{};
    uint32_t objectId{};
    glm::u8vec4 color{};
  };
}
