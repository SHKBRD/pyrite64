#version 460

layout (location = 0) in ivec3 inPosition;
//layout (location = 1) in vec2 inNorm;
layout (location = 1) in vec4 inColor;
layout (location = 2) in ivec2 inUV;

layout (location = 0) out vec4 v_color;
layout (location = 1) out vec4 uv;
layout (location = 2) out flat uint v_objectID;
layout (location = 3) out flat vec4 tileSize;
layout (location = 4) out vec2 posScreen;
layout (location = 5) out noperspective vec4 cc_shade;
layout (location = 6) out flat vec4 cc_shade_flat;

#include "./defines.h"
#include "./ubo.glsl"

// set=3 in fragment shader
layout(std140, set = 1, binding = 0) uniform UniformGlobal {
    mat4 projMat;
    mat4 cameraMat;
};

layout(std140, set = 1, binding = 1) uniform UniformObject {
  UBO_Material material;
};

layout(set = 2, binding = 0) uniform sampler2D tex0;
layout(set = 2, binding = 1) uniform sampler2D tex1;

#include "./utils.glsl"

void main()
{
  mat4 matMVP = projMat * cameraMat * material.modelMat;
  // @TODO: do on CPU:
  mat3 matNorm = mat3(transpose(inverse(material.modelMat)));

  //posNorm /= 32768.0;

  vec2 uvPixel = (vec2(inUV) / float(1 << 5)); // @TODO: <-
  v_objectID = material.objectID;

  vec3 inNormal = vec3(0,1,0); // @TODO: <-

  // Directional light
  vec3 norm = inNormal;
  vec3 normScreen = normalize(matNorm * norm);

  cc_shade = inColor;

  vec4 lightTotal = vec4(linearToGamma(material.ambientColor.rgb), 0.0);
  for(int i=0; i<2; ++i) {
    float lightStren = max(dot(norm, material.lightDir[i].xyz), 0.0);
    vec4 colorNorm = vec4(linearToGamma(material.lightColor[i].rgb), 1.0);
    lightTotal += colorNorm * lightStren;
  }

  lightTotal.rgb = clamp(lightTotal.rgb, 0.0, 1.0);
  lightTotal.a = 1.0;

  vec3 shadeWithLight = cc_shade.rgb * lightTotal.rgb;
  cc_shade.rgb = geoModeSelect(G_LIGHTING, cc_shade.rgb, shadeWithLight);
  cc_shade = clamp(cc_shade, 0.0, 1.0);
  cc_shade_flat = cc_shade;

  vec2 uvGen = geoModeSelect(G_TEX_GEN, uvPixel, normScreen.xy * 0.5 + 0.5);

  // turn UVs ionto pixel-space, apply first tile settings
  ivec4 texSize = ivec4(textureSize(tex0, 0), textureSize(tex1, 0));
  // we simulate UVs in pixel-space, since there is only one UV set, we scale by the first texture size
  uv = uvGen.xyxy;// * texSize.xyxy;
  // apply material.shift from top left of texture:

  uv.yw = texSize.yw - uv.yw - 1;
  uv *= material.shift;
  uv.yw = texSize.yw - uv.yw - 1;

  uv = uv - (material.shift * 0.5) - material.low;

  tileSize = abs(material.high) - abs(material.low);

  // @TODO: uvgen (f3d + t3d)
  // forward CC (@TODO: do part of this here? e.g. prim/env/shade etc.)

  vec3 posQuant = vec3(inPosition) / (32768.0 / 256.0);

  gl_Position = matMVP * vec4(posQuant, 1.0);
  posScreen = gl_Position.xy / gl_Position.w;
}
