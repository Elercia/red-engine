#version 410 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 tex_uv;

uniform mat4 world;
uniform mat4 view_projection;
uniform vec2 size;

layout(location = 0) out vec2 texture_uv_out;

void main() 
{
    vec4 inputPosition = vec4(vertex_position.xy * size, 0.f, 1.f);
    vec4 positionWS = inputPosition * world;

    texture_uv_out = tex_uv;
    gl_Position = positionWS * view_projection;
    gl_Position.z = 0;
}