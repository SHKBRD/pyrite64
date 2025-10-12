/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "scene/componentTable.h"
#include "scene/components/code.h"

// Note: GCC allows 'reinterpret_cast' in constant expressions
#define SET_COMP(name) \
  { \
    .init   = reinterpret_cast<FuncInit>(Comp::name::init), \
    .update = reinterpret_cast<FuncUpdate>(Comp::name::update), \
    .draw   = reinterpret_cast<FuncDraw>(Comp::name::draw), \
    .allocSize = sizeof(Comp::name), \
  }

namespace P64
{
  const ComponentDef COMP_TABLE[COMP_TABLE_SIZE] {
    SET_COMP(Code),
    SET_COMP(Code),
  };
}