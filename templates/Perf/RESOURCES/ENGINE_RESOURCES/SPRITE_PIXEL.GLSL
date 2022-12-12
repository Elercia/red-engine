#version 430 core

layout(location = 0) in vec2 texture_uv;

layout(location = 0) uniform sampler2D texture_sampler;
layout(location = 1) uniform vec4 in_color;

out vec4 frag_colour;

void main()
{
    vec4 sampledColor = texture( texture_sampler, texture_uv );
    frag_colour = vec4( sampledColor.rgb * in_color.rgb, sampledColor.a);
}