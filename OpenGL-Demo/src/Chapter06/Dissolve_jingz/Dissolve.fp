#version 330

smooth in vec2 vVaryingTexCoord;
smooth in vec3 vVaryingNormal;
smooth in vec3 vVaryingLightDir;

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform sampler2D cloudTexture;
uniform float dissolveFactor;


out vec4 vFragColor;

void main(void)
{
	vec4 vCloudSample = texture(cloudTexture,vVaryingTexCoord);
	if(vCloudSample.r < dissolveFactor)
		discard;
		
	float diff = max(0.0f,dot(normalize(vVaryingNormal),normalize(vVaryingLightDir)));
	//自身颜色在点光源作用下
	vFragColor = diff * diffuseColor;
	//环境 
	vFragColor += ambientColor;
	//镜面
	vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir),normalize(vVaryingNormal)));
	
	float spec = max(0.0f,dot(normalize(vVaryingNormal),vReflection));
	
	if(diff != 0)
	{
		float fSpec = pow(spec,128.0f);
		vFragColor.rgb += vec3(fSpec,fSpec,fSpec);
	}
}