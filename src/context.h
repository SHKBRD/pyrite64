/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "project/project.h"
#include "SDL3/SDL.h"

namespace Renderer { class Scene; }

struct Context
{
  Project::Project *project{nullptr};
  Renderer::Scene *scene{nullptr};
  SDL_Window* window{nullptr};
  SDL_GPUDevice *gpu{nullptr};
};

extern Context ctx;