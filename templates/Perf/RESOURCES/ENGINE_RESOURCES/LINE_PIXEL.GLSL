#version 430 core

layout(location = 0) in vec4 in_color;

out vec4 frag_colour;

void main()
{
    frag_colour = in_color;
}