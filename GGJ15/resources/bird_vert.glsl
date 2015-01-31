
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 positionInView = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
