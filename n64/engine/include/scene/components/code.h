/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "scene/object.h"
#include "script/scriptTable.h"

namespace P64::Comp
{
  struct Code
  {
    Script::FuncUpdate funcUpdate{};
    Script::FuncUpdate funcDraw{};

    static void init(Object& obj, Code* data, uint16_t* initData)
    {
      //debugf("Init: %d %d\n", initData[0], initData[1]);
      auto scriptPtr = Script::getCodeByIndex(initData[0]);
      assert(scriptPtr != nullptr);

      data->funcUpdate = scriptPtr;
      data->funcDraw = nullptr;
    }

    static void update(Object& obj, Code* data) {
      if(data->funcUpdate)data->funcUpdate(obj);
    }

    static void draw(Object& obj, Code* data) {
      if(data->funcDraw)data->funcDraw(obj);
    }
  };
}