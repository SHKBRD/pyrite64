/**
* @copyright 2025 - Max Bebök
* @license MIT
*/

// Based on: https://n64brew.dev/wiki/Reality_Display_Processor/Commands#0x3C_-_Set_Combine_Mode

namespace
{
  constexpr uint8_t CC_MAP_COLOR[4][0xFF] {
    {
      CC_C_COMB,
      CC_C_TEX0,
      CC_C_TEX1,
      CC_C_PRIM,
      CC_C_SHADE,
      CC_C_ENV,
      CC_C_1,
      CC_C_NOISE,
      CC_C_0,
    }, {
      CC_C_COMB,
      CC_C_TEX0,
      CC_C_TEX1,
      CC_C_PRIM,
      CC_C_SHADE,
      CC_C_ENV,
      CC_C_CENTER,
      CC_C_K4,
      CC_C_0,
    }, {
      CC_C_COMB,
      CC_C_TEX0,
      CC_C_TEX1,
      CC_C_PRIM,
      CC_C_SHADE,
      CC_C_ENV,
      CC_C_SCALE,
      CC_C_COMB_ALPHA,
      CC_C_TEX0_ALPHA,
      CC_C_TEX1_ALPHA,
      CC_C_PRIM_ALPHA,
      CC_C_SHADE_ALPHA,
      CC_C_ENV_ALPHA,
      CC_C_LOD_FRAC,
      CC_C_PRIM_LOD_FRAC,
      CC_C_K5,
      CC_C_0
    }, {
      CC_C_COMB,
      CC_C_TEX0,
      CC_C_TEX1,
      CC_C_PRIM,
      CC_C_SHADE,
      CC_C_ENV,
      CC_C_1,
      CC_C_0,
    }
  };

  constexpr uint8_t CC_MAP_ALPHA[4][0xFF] {
    {
      CC_A_COMB,
      CC_A_TEX0,
      CC_A_TEX1,
      CC_A_PRIM,
      CC_A_SHADE,
      CC_A_ENV,
      CC_A_1,
      CC_A_0,
    }, {
      CC_A_COMB,
      CC_A_TEX0,
      CC_A_TEX1,
      CC_A_PRIM,
      CC_A_SHADE,
      CC_A_ENV,
      CC_A_1,
      CC_A_0,
    }, {
      CC_A_LOD_FRAC,
      CC_A_TEX0,
      CC_A_TEX1,
      CC_A_PRIM,
      CC_A_SHADE,
      CC_A_ENV,
      CC_A_PRIM_LOD_FRAC,
      CC_A_0,
    }, {
      CC_A_COMB,
      CC_A_TEX0,
      CC_A_TEX1,
      CC_A_PRIM,
      CC_A_SHADE,
      CC_A_ENV,
      CC_A_1,
      CC_A_0,
    }
  };
}