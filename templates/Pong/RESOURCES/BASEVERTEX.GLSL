#version 410 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 tex_uv;

uniform mat4 world;
uniform mat4 view_projection;

layout(location = 0) out vec2 texture_uv_out;

void main() 
{
    texture_uv_out = tex_uv;
    vec4 inputPosition = vec4(vertex_position.xy, 0.0, 1.f);
    vec4 positionWS = world * inputPosition;
    gl_Position = view_projection * positionWS;
}