attribute vec3 inVertex1;
attribute vec3 inVertex2;
attribute vec3 inNormal;
attribute vec4 inColour;
attribute vec2 inTexcoord;

uniform mat4 uMVP;
uniform mat4 uModel;
uniform float uWeight;

varying vec3 vNormal;
varying vec4 vColour;
varying vec2 vTexcoord;
varying vec3 vFragPos;

vec3 CosineIntr(vec3 v1, vec3 v2, float t)
{
    float t2 = (1.0 - cos(t * 3.14159)) / 2.0;
    return (v1 * (1.0 - t2) + v2 * t2);
}

vec3 LinearIntr(vec3 v1, vec3 v2, float t)
{
    return (v1 * (1.0 - t) + v2 * t);
}

void main(void)
{
    vec3 finalVertex = CosineIntr(inVertex1, inVertex2, uWeight);

    //Pass transformed vertex to fragment shader
    gl_Position = uMVP * vec4(finalVertex, 1.0);

    //Pass other vertex data to fragment shader
    vNormal = normalize(inNormal);
    vColour = inColour;
    vTexcoord = inTexcoord;

    vFragPos = (uModel * vec4(finalVertex, 1.0)).xyz;
}
