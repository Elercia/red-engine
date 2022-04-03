#version 440 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 tex_uv;

layout(std430, binding = 0) buffer PerCameraDataStruct
{
    mat4 view_projection;
} PerCameraData;

layout(std430, binding = 1) buffer PerInstanceDataStruct
{
    mat4 world;
    vec2 size;
} PerInstanceData;

layout(location = 0) out vec2 texture_uv_out;

void main() 
{
    vec4 inputPosition = vec4(vertex_position.xy * PerInstanceData.size, 0.f, 1.f);
    vec4 positionWS = inputPosition * PerInstanceData.world;

    texture_uv_out = tex_uv;
    gl_Position = positionWS * PerCameraData.view_projection;
    gl_Position.z = 0;
}