varying vec3 vNormal;
varying vec4 vColour;
varying vec2 vTexcoord;
varying vec3 vFragPos;

uniform sampler2D texture;
uniform vec3 uLightPos;

void main(void)
{
    //normalize our lighting vectors
    vec3 Normal = normalize(vNormal);
    vec3 lightDir = normalize(uLightPos - vFragPos);

    //Calculate diffuse component
    float D = max(dot(Normal, lightDir), 0.0);

    //Calculate fragment light.
    //the first vec (0.1, 0.1, 0.1) represents the ambient
    //which is multiplied by 1.0 - d (the amount of diffuse light hitting this fragment)
    //we then add the polygon colour multiplied by  to this.
    //this keeps each pixel within the range 0.0 - 1.0
    //gl_FragColor = vec4((vec3(0.1, 0.2, 0.4) * (1.0 - D)) + vColour.rgb * D, vColour.a);
    
    vec3 finalColour = texture2D(texture, vTexcoord).rgb * vColour.rgb;
    //gl_FragColor = vec4(mix(vec3(0.1, 0.2, 0.4), finalColour, clamp(D * 1.5, 0.0, 1.0)), vColour.a);
    gl_FragColor = vec4(finalColour, vColour.a);
}
