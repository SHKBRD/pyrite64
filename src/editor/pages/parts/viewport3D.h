/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "../../../renderer/vertBuffer.h"
#include "../../../renderer/framebuffer.h"

namespace Editor
{
  class Viewport3D
  {
    private:
      Renderer::Framebuffer fb{};
      uint32_t passId{};

      void onRenderPass(SDL_GPUCommandBuffer* cmdBuff, SDL_GPUGraphicsPipeline* pipeline);
      void onCopyPass(SDL_GPUCommandBuffer* cmdBuff, SDL_GPUCopyPass *copyPass);

    public:
      Viewport3D();
      ~Viewport3D();

      void draw();
  };
}
