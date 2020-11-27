attribute vec3 inVertex;
attribute vec3 inColour;

uniform mat4 uMVP;

varying vec4 vColour;

void main(void)
{
    //Pass transformed vertex to fragment shader
    gl_Position = uMVP * vec4(inVertex, 1.0);

    //Pass other vertex data to fragment shader
    vColour = vec4(inColour, 1.0);
}
