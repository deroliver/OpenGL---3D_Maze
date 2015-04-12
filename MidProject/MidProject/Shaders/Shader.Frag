#version 400

in vec4 Frag_Color;

layout(location=0) out vec4 Out_Color;

void main(void)
{
	Out_Color = Frag_Color;
}