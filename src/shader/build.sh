set -e
cd "$(dirname "$0")"

glslc -fshader-stage=fragment n64.frag.glsl -o ../../data/shader/n64.frag.spv
glslc -fshader-stage=vertex n64.vert.glsl -o ../../data/shader/n64.vert.spv

glslc -fshader-stage=fragment lines.frag.glsl -o ../../data/shader/lines.frag.spv
glslc -fshader-stage=vertex lines.vert.glsl -o ../../data/shader/lines.vert.spv
