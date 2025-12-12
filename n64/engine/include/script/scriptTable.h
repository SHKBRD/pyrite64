/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <libdragon.h>

namespace P64 { class Object; }

namespace P64::Script
{
  typedef void(*FuncObjData)(Object&, void*);
  typedef void(*FuncObjDataDelta)(Object&, void*, float);

  struct ScriptEntry
  {
    FuncObjData init;
    FuncObjDataDelta update;
    FuncObjDataDelta draw;
    FuncObjData destroy;
  };

  // Note: generated and implement in the project:
  ScriptEntry &getCodeByIndex(uint32_t idx);
  uint16_t getCodeSizeByIndex(uint32_t idx);
}