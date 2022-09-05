#version 410 core

layout(location = 0) in vec2 texture_uv;

uniform sampler2D texture_sampler;
uniform vec4 in_color;

out vec4 frag_colour;

void main()
{
    frag_colour = texture( texture_sampler, texture_uv ).rgba * in_color;
}