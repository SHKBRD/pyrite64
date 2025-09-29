/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <string>
#include <vector>

#include "../renderer/texture.h"

namespace Project
{
  enum class ComprTypes : int
  {
    DEFAULT = -1,
    LEVEL_0 = 0,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
  };

  class AssetManager
  {
    public:
      enum class FileType : int
      {
        UNKNOWN = 0,
        IMAGE,
        AUDIO,
        MODEL_3D,
      };

      struct Entry
      {
        uint64_t uuid{0};
        std::string name{};
        std::string path{};
        FileType type{};
        // Generic settings
        ComprTypes compression{ComprTypes::DEFAULT};

        // Preview
        Renderer::Texture *texture{nullptr};
      };

    private:
      std::vector<Entry> entries{};

    public:
      void reload();

      [[nodiscard]] const std::vector<Entry>& getEntries() const {
        return entries;
      }

      Entry* getEntryByUUID(uint64_t uuid) {
        for (auto &entry : entries) {
          if (entry.uuid == uuid) {
            return &entry;
          }
        }
        return nullptr;
      }
  };
}
