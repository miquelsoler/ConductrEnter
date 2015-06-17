#version 120

uniform	sampler2D tex;
uniform float offset;

varying vec3 N;
varying vec3 v;

void main() {

//    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
//	float size    = gl_Normal.x;
//    gl_PointSize  = size;
//    gl_FrontColor = gl_Color;
//    
//	gl_FrontColor =  gl_Color;
//	gl_TexCoord[0] = gl_MultiTexCoord0;
//	gl_Position = gl_Vertex;


    
    //.. and passes the multi texture coordinates along to the fragment shader
	gl_TexCoord[0] = gl_MultiTexCoord0;

    float pixelDepth = texture2D(tex,gl_TexCoord[0].st).r;
//    
//    gl_Position = ftransform();
//    vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
//    gl_Position.xyz = gl_Position.xyz + (100 * pixelDepth * normal);
//
    v = vec3(gl_ModelViewMatrix * gl_Vertex);
    N = normalize(gl_Normal * gl_NormalMatrix);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    gl_Position.xyz = gl_Position.xyz + N * offset * pixelDepth;


    //this is a default vertex shader all it does is this...

    //    gl_Position.x = gl_Position.x + 100*pixelDepth;

    
}