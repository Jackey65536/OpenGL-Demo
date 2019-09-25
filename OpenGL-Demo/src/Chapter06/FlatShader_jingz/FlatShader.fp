#version 330

uniform vec4 vColorValue;

out vec4 vFragColor;

void main(void)
{
	vFragColor = vColorValue;
}