#version 420

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;
layout(location = 4) in vec4 inFragPosLightSpace;

struct DirectionalLight
{
	//Light direction (defaults to down, to the left, and a little forward)
	vec4 _lightDirection;

	//Generic Light controls
	vec4 _lightCol;

	//Ambience controls
	vec4 _ambientCol;
	float _ambientPow;
	
	//Power controls
	float _lightAmbientPow;
	float _lightSpecularPow;

	float _shadowBias;
};

layout (std140, binding = 0) uniform u_Lights
{
	DirectionalLight sun;
};

layout (binding = 30) uniform sampler2D s_ShadowMap;
uniform sampler2D s_Diffuse;
uniform sampler2D s_Diffuse2;
uniform sampler2D s_Specular;

uniform float u_TextureMix;
uniform vec3  u_CamPos;

uniform float u_NearPlane;
uniform float u_FarPlane;

//For lighting toggles
uniform int u_Condition;

out vec4 frag_color;

float ShadowCalculation(vec4 fragPosLightSpace)
{
	//Perspective division
	vec3 projectionCoordinates = fragPosLightSpace.xyz / fragPosLightSpace.w;

	//Transform into a [0,1] range
	projectionCoordinates = projectionCoordinates * 0.5 + 0.5;

	//Get the closest depth value
	float closestDepth = texture(s_ShadowMap, projectionCoordinates.xy).r;

	//Get the current depth according to our camera
	float currentDepth = projectionCoordinates.z;

	//PCF Calculation
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(s_ShadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(s_ShadowMap, projectionCoordinates.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - sun._shadowBias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;

	return shadow; 
}

float linearize_depth(float d, float zNear, float zFar)
{
	float z_n = 2.0 * d - 1.0;
	return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
void main() {
	// Diffuse
	vec3 N = normalize(inNormal);
	vec3 lightDir = normalize(-sun._lightDirection.xyz);
	float dif = max(dot(N, lightDir), 0.0);
	vec3 diffuse = dif * sun._lightCol.xyz;// add diffuse intensity

	// Specular
	vec3 viewDir  = normalize(u_CamPos - inPos);
	vec3 h        = normalize(lightDir + viewDir);

	// Get the specular power from the specular map
	float texSpec = 1.0f;
	float spec = pow(max(dot(N, h), 0.0), 4.0); // Shininess coefficient (can be a uniform)
	vec3 specular = sun._lightSpecularPow * texSpec * spec * sun._lightCol.xyz; // Can also use a specular color

	// Get the albedo from the diffuse / albedo map
	vec4 textureColor1 = texture(s_Diffuse, inUV);
	vec4 textureColor2 = texture(s_Diffuse2, inUV);
	vec4 textureColor = mix(textureColor1, textureColor2, u_TextureMix);

	float shadow = ShadowCalculation(inFragPosLightSpace);

	//float actualDepth = linearize_depth(gl_FragCoord.z, u_NearPlane, u_FarPlane);
	float actualDepth = linearize_depth(gl_FragCoord.z, 0.01, 1000.0);

	vec3 result;

	switch(u_Condition)
	{
		//No lighting
		case 0:
			result = inColor * textureColor.rgb;
			break;
		//Ambient
		case 1:
			result = (
			(sun._ambientPow * sun._ambientCol.xyz) + 
			(1.0 - shadow)) *
			inColor * textureColor.rgb; 
			break;
		//Specular
		case 2:
			result = (
			(specular) * (1.0 - shadow)) *
			inColor * textureColor.rgb;
			break;
		//Amb + Spec + Diffuse
		case 3:
			result = (
			(sun._ambientPow * sun._ambientCol.xyz) + 
			(1.0 - shadow) * (diffuse + specular) 
			) * inColor * textureColor.rgb; 
			break;

		case 4:
			result = (
			(sun._ambientPow * sun._ambientCol.xyz) + 
			(1.0 - shadow) * (diffuse + specular) 
			) * inColor * textureColor.rgb; 
			break;
	}

	frag_color = vec4(result, textureColor.a);

	if (u_Condition == 4)
	{
		//frag_color = vec4(actualDepth, actualDepth, actualDepth, textureColor.a);	
		frag_color = vec4(result, textureColor.a) * vec4(actualDepth, actualDepth, actualDepth, 1.0);
	}

	//frag_color = vec4(actualDepth, actualDepth, actualDepth, 1.0);	
}