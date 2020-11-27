attribute vec3 inVertex;
attribute vec3 inNormal;
attribute vec4 inColour;
attribute vec2 inTexcoord;

uniform mat4 uMVP;

varying vec3 vNormal;
varying vec4 vColour;
varying vec2 vTexcoord;

void main(void)
{
    //Pass transformed vertex to fragment shader
    gl_Position = uMVP * vec4(inVertex, 1.0);

    //Pass other vertex data to fragment shader
    vNormal = normalize(inNormal);
    vColour = inColour;
    vTexcoord = inTexcoord;
}
