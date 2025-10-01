/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "../../utils/color.h"

namespace Project
{
  struct SceneConf
  {
    std::string name{};
    int fbWidth{320};
    int fbHeight{240};
    int fbFormat{0};
    Utils::Color clearColor{};
    bool doClearColor{};
    bool doClearDepth{};

    std::string serialize() const;
  };

  class Scene
  {
    private:
      int id{};

    public:
      SceneConf conf{};

      Scene(int id_);

      void save();
  };
}