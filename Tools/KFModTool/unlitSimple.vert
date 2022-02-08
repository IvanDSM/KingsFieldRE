#version 330 core

layout(location = 0) in vec3 inVertex;
layout(location = 1) in vec3 inColour;

out vec4 vColour;

uniform mat4 uMVP;

void main(void)
{
    //Pass transformed vertex to fragment shader
    gl_Position = uMVP * vec4(inVertex, 1.0);

    //Pass other vertex data to fragment shader
    vColour = vec4(inColour, 1.0);
}
