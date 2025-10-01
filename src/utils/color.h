/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once

namespace Utils
{
  union Color
  {
    struct
    {
      float r{}, g{}, b{}, a{};
    };
    float rgba[4];
  };
}