#version 400

layout(location=0) in vec4 In_Pos;
layout(location=1) in vec4 In_Color;

uniform mat4 Proj_Mat;  
uniform mat4 View_Mat;  
uniform mat4 Mode_Mat;  

out vec4 Frag_Color;

void main(void)
{
	gl_Position = Proj_Mat * View_Mat * Mode_Mat * In_Pos;
	Frag_Color = In_Color;
}