#version 430 core

layout(location = 0) in vec2 texture_uv;

layout(location = 0) uniform sampler2D texture_sampler;
layout(location = 2) uniform vec4 fontsize;

out vec4 frag_colour;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    vec4 bgColor = vec4(0, 0, 0, 1);
    vec4 fgColor = vec4(1, 1, 1, 1);

    vec3 msdfcolor = texture( texture_sampler, texture_uv ).rgb;
    float sd = median(msdfcolor.r, msdfcolor.g, msdfcolor.b);

    float screenPxDistance = fontsize.x*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);

    frag_colour = mix(bgColor, fgColor, opacity);
}