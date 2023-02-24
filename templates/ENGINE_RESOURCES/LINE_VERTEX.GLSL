#version 440 core

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;

layout(std140, binding = 0) buffer PerCameraDataStruct
{
    vec4 view_projection1;
    vec4 view_projection2;
    vec4 view_projection3;
    vec4 view_projection4;
} PerCameraData;

layout(location = 0) out vec4 out_color;

mat4 toMat4(vec4 view_projection1, vec4 view_projection2, vec4 view_projection3, vec4 view_projection4)
{
    return mat4(view_projection1,
                view_projection2,
                view_projection3,
                view_projection4);
}

void main() 
{
    vec4 positionWS = vec4(vertex_position.xy, 0.f, 1.f);
    vec4 outPos = (toMat4(PerCameraData.view_projection1, PerCameraData.view_projection2, PerCameraData.view_projection3, PerCameraData.view_projection4)) * positionWS;
    outPos.y *= -1;

    gl_Position = outPos;
    out_color = vec4(vertex_color) / 255.f;
}