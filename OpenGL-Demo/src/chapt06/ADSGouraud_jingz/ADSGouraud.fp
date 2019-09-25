#version 330

smooth in vec4 vVaryingColor;

out vec4 vFragColor;

void main(void)
{
	vFragColor = vVaryingColor;
}