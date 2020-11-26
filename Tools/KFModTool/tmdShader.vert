attribute vec3 inVertex;
//attribute vec3 inNormal;
//attribute vec4 inColour;
//attribute vec2 inTexcoord;

uniform mat4 uWVP;  //WorldViewProjection;

//varying vec3 vNormal;
varying vec4 vColour;

void main(void)
{
    //Pass transformed vertex to fragment shader
    gl_Position = uWVP * vec4(inVertex, 1.0);

    //Pass other vertex data to fragment shader
    //vNormal = normalize(inNormal);
    vColour = vec4(0.0, 1.0, 1.0, 1.0);
}
