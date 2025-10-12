/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <libdragon.h>

namespace P64 { class Object; }

namespace P64::Script
{
  typedef void(*FuncUpdate)(Object&);

  // Note: generated and implement in the project:
  FuncUpdate getCodeByIndex(uint32_t idx);
}