/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <libdragon.h>

namespace P64
{
  class Object;

  typedef void(*FuncInit)(Object&, void*, void*);
  typedef void(*FuncUpdate)(Object&, void*);
  typedef void(*FuncDraw)(Object&, void*);

  struct ComponentDef
  {
    FuncInit init{};
    FuncUpdate update{};
    FuncDraw draw{};
    uint32_t allocSize{};
  };

  constexpr uint32_t COMP_TABLE_SIZE = 8;
  extern const ComponentDef COMP_TABLE[COMP_TABLE_SIZE];
}