#version 440 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 tex_uv;

layout(std140, binding = 0) buffer PerCameraDataStruct
{
    vec4 view_projection1;
    vec4 view_projection2;
    vec4 view_projection3;
    vec4 view_projection4;
} PerCameraData;

layout(std430, binding = 1) buffer PerInstanceDataStruct
{
    vec4 world1;
    vec4 world2;
    vec4 world3_size;
} PerInstanceData;

layout(location = 0) out vec2 texture_uv_out;

mat3 toMat3(vec4 world1, vec4 world2, vec4 world3)
{
    return mat3(world1[0], world1[1], world1[2],
                world1[3], world2[0], world2[1],
                world2[2], world2[3], world3[0]);
}

mat4 toMat4(vec4 view_projection1, vec4 view_projection2, vec4 view_projection3, vec4 view_projection4)
{
    return mat4(view_projection1,
                view_projection2,
                view_projection3,
                view_projection4);
}

void main() 
{
    vec3 inputPosition = vec3(vertex_position.xy * PerInstanceData.world3_size.yz, 1.f);
    mat3 world = toMat3(PerInstanceData.world1, PerInstanceData.world2, PerInstanceData.world3_size);
    vec3 position2DWS = world * inputPosition;
    vec4 positionWS = vec4(position2DWS.xy, PerInstanceData.world3_size.w, 1.f);

    vec4 outPos = (toMat4(PerCameraData.view_projection1, PerCameraData.view_projection2, PerCameraData.view_projection3, PerCameraData.view_projection4)) * positionWS;
    outPos.y *= -1;

    gl_Position = outPos;
    texture_uv_out = tex_uv;
}