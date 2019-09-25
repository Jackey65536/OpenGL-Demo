#version 330

smooth in vec3 vVaryingNormal;
smooth in vec3 vVaryingLightDir;

uniform vec4 ambientColor;//环境光颜色
uniform vec4 diffuseColor;//	球体颜色
uniform vec4 specularColor;// 材质颜色属性

out vec4 vFragColor;

void main(void)
{
	//计算点光源给物体的颜色加成
	float diff = max(0.0,dot(normalize(vVaryingNormal),normalize(vVaryingLightDir)));

	vFragColor = diff * diffuseColor;
	vFragColor.a = diffuseColor.a;

	//计算环境光加成
	vFragColor += ambientColor;

	//计算材质镜面光加成
	vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),normalize(vVaryingNormal)));//放射光方向
	float spec = max(0.0f,dot(normalize(vVaryingNormal),vReflection));
	if(diff != 0)
	{
		float fSpec = pow(spec,128.0);//默认镜面反光度属性shininess 128
		vFragColor.rgb += vec3(fSpec,fSpec,fSpec);
	}
}