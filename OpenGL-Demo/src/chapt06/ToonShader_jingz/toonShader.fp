#version 330
smooth in float textureCoordinate;

uniform sampler1D colorTable;

out vec4 vFragColor;

void main(void)
{
	vFragColor = texture(colorTable,textureCoordinate);
	
}