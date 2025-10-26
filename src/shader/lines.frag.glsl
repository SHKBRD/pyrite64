#version 460

layout (location = 0) in vec4 v_color;

layout (location = 0) out vec4 FragColor;
// layout (location = 1) out uint ObjID;

// layout(set = 2, binding = 0) uniform sampler2D texSampler;

void main()
{
  FragColor = v_color;
}
