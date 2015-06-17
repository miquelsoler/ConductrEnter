#version 120

uniform	sampler2D tex;
uniform float offset;

varying vec3 N;
varying vec3 v;

void main() {
    
    //	gl_FrontColor =  gl_Color;
    //	gl_TexCoord[0] = gl_MultiTexCoord0;
    //	gl_Position = gl_Vertex;
    
    //.. and passes the multi texture coordinates along to the fragment shader
	gl_TexCoord[0] = gl_MultiTexCoord0;
    // duplicate the texCoord in X to have a repetition of the texture in mirror to avoid cuts
    gl_TexCoord[0].x = gl_TexCoord[0].x * 2;

    // calculate the color of the texture to quantify noise ammount
    float pixelDepth = texture2D(tex,gl_TexCoord[0].st).r;
    
    // transform the vertex position based on normal direction
    vec4 vv;
    vv.x = gl_Vertex.x + (gl_Normal.x * pixelDepth * offset);
    vv.y = gl_Vertex.y + (gl_Normal.y * pixelDepth * offset);
    vv.z = gl_Vertex.z + (gl_Normal.z * pixelDepth * offset);
    
    // this is needed by the fragment shader as it is
    v = vec3(gl_ModelViewMatrix * gl_Vertex);
    N = normalize(gl_NormalMatrix * gl_Normal);

    // fill .w with something ... ?¿
    vv.w = 1;
    
    // calculate gl_Position for the gragment shader
    gl_Position   = gl_ModelViewProjectionMatrix * vv;
    
    
}