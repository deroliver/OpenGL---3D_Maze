#version 150

in vec4 vPosition;
in vec4 vColor;


void main() 
{
	vec4 t = vPosition;
	gl_Position = t;
} 
