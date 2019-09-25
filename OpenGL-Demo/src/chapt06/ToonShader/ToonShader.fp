// Cell lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

uniform sampler1D colorTable;
out vec4 vFragColor;

smooth in float textureCoordinate;


void main(void)
   { 
   //四种红色，根据顶点的漫放射光强（textureCoordinate）作为纹理坐标添加到一个包含逐渐变亮颜色表的一维纹理
   vFragColor = texture(colorTable, textureCoordinate);
   }
