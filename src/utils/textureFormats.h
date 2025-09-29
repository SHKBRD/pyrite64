/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once

namespace Utils
{
  enum class TexFormat {
    AUTO = 0,
    RGBA32,
    RGBA16,
    CI8,
    CI4,
    I8,
    I4,
    IA16,
    IA8,
    IA4,
    IHQ,
    SHQ,
    ZBUF,
  };

  constexpr int TEX_TYPE_COUNT = static_cast<int>(TexFormat::ZBUF) + 1;

  constexpr const char* TEX_TYPES[] = {
    "Auto",
    "RGBA32",
    "RGBA16",
    "CI8",
    "CI4",
    "I8",
    "I4",
    "IA16",
    "IA8",
    "IA4",
    "IHQ",
    "SHQ",
    "ZBUF",
  };

  constexpr const char* getTexFormatName(TexFormat fmt) {
   return TEX_TYPES[static_cast<int>(fmt)];
  }
}