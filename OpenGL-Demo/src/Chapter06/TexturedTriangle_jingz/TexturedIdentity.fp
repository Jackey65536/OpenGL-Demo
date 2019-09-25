#version 330

smooth in vec2 vVaryingTexCoords;

uniform sampler2D colorMap;

out vec4 vFragColor;


void main(void)
{
	vFragColor = texture(colorMap,vVaryingTexCoords.st);
}