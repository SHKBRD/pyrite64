/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "framebuffer.h"
#include "../context.h"

Renderer::Framebuffer::Framebuffer()
{
  texInfo.width = 0;
  texInfo.height = 0;
  texInfo.layer_count_or_depth = 1;
  texInfo.num_levels = 1;
  texInfo.sample_count = SDL_GPU_SAMPLECOUNT_1;

  targetInfo.texture = nullptr;
  targetInfo.clear_color = {0, 0, 0, 1};
  targetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
  targetInfo.store_op = SDL_GPU_STOREOP_STORE;
  targetInfo.mip_level = 0;
  targetInfo.layer_or_depth_plane = 0;
  targetInfo.cycle = false;

  depthTargetInfo.texture = nullptr;
  depthTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
  depthTargetInfo.clear_depth = 1;
  depthTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
  depthTargetInfo.stencil_load_op = SDL_GPU_LOADOP_CLEAR;
  depthTargetInfo.stencil_store_op = SDL_GPU_STOREOP_STORE;
  depthTargetInfo.mip_level = 0;
}

Renderer::Framebuffer::~Framebuffer() {
  if (transBufferRead) {
    SDL_ReleaseGPUTransferBuffer(ctx.gpu, transBufferRead);
  }
  if(gpuTex) {
    SDL_ReleaseGPUTexture(ctx.gpu, gpuTex);
  }
}

void Renderer::Framebuffer::resize(uint32_t width, uint32_t height)
{
  if (texInfo.width == width && texInfo.height == height) return;
  texInfo.width = width;
  texInfo.height = height;

  if(gpuTex) {
    SDL_ReleaseGPUTexture(ctx.gpu, gpuTex);
  }

  texInfo.type = SDL_GPU_TEXTURETYPE_2D;
  texInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
  texInfo.usage = SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER;
  gpuTex = SDL_CreateGPUTexture(ctx.gpu, &texInfo);

  texInfo.type = SDL_GPU_TEXTURETYPE_2D;
  texInfo.format = SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT;
  texInfo.usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET;
  gpuTexDepth = SDL_CreateGPUTexture(ctx.gpu, &texInfo);

  targetInfo.texture = gpuTex;
  depthTargetInfo.texture = gpuTexDepth;
}

glm::u8vec4 Renderer::Framebuffer::readColor(uint32_t x, uint32_t y)
{
  if (x >= texInfo.width || y >= texInfo.height) {
    return {0,0,0,0};
  }

  SDL_GPUCommandBuffer* cmdBuff = SDL_AcquireGPUCommandBuffer(ctx.gpu);
  uint32_t w = 1;
  uint32_t h = 1;

  if (!transBufferRead) {
    SDL_GPUTransferBufferCreateInfo tbci{};
    tbci.size = (Uint32)32;
    tbci.usage = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD;
    transBufferRead = SDL_CreateGPUTransferBuffer(ctx.gpu, &tbci);
  }

  SDL_GPUCopyPass *pass = SDL_BeginGPUCopyPass(cmdBuff);

  glm::u8vec4 color{0,0,0,0};
  SDL_GPUTextureRegion src{};
  src.texture = getTexture();
  src.x = x;
  src.y = y;
  src.w = w;
  src.h = h;
  src.d = 1;

  SDL_GPUTextureTransferInfo dst{};
  dst.transfer_buffer = transBufferRead;
  dst.rows_per_layer = w;
  dst.pixels_per_row = h;

  SDL_DownloadFromGPUTexture(pass, &src, &dst);

  SDL_EndGPUCopyPass(pass);

  SDL_GPUFence *fence = SDL_SubmitGPUCommandBufferAndAcquireFence(cmdBuff);
  SDL_WaitForGPUFences(ctx.gpu, true, &fence, 1);
  SDL_ReleaseGPUFence(ctx.gpu, fence);
  //auto buff = SDL_AcquireGPUCommandBuffer(ctx.gpu);

  auto *mapped_tbuf = (uint8_t*)SDL_MapGPUTransferBuffer(ctx.gpu, transBufferRead, false);
  glm::u8vec4 res{};
  res.r = mapped_tbuf[0];
  res.g = mapped_tbuf[1];
  res.b = mapped_tbuf[2];
  res.a = mapped_tbuf[3];
  printf("Pixel: %d %d %d %d\n", mapped_tbuf[0], mapped_tbuf[1], mapped_tbuf[2], mapped_tbuf[3]);

  SDL_UnmapGPUTransferBuffer(ctx.gpu, transBufferRead);
  return res;
}

