/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <string>

namespace CLI
{
  enum Result
  {
    SUCCESS,
    ERROR,
    GUI
  };

  const std::string& getProjectPath();
  bool isExperimentalEnabled();
  Result run(int argc, char** argv);
};
