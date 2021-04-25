#version 420

layout(location = 0) in vec2 inUV;

layout(binding = 0) uniform sampler2D s_Scene;
layout(binding = 1) uniform sampler2D s_Blur;
layout(binding = 29) uniform sampler2D s_Depth;

uniform float u_focalDistance;
uniform float u_focalLength;
uniform float u_aperature;
uniform float u_nearPlane;
uniform float u_farPlane;

out vec4 frag_Color;

//From water tutorial
float linearize_depth(float d, float zNear, float zFar)
{
	float z_n = 2.0 * d - 1.0;
	return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

float CalculateCircleOfConfusion()
{
	float CoCScale = (u_aperature * u_focalLength * u_focalDistance * (u_farPlane - u_nearPlane)) / ((u_focalDistance - u_focalLength) * u_nearPlane * u_farPlane);

	float CoCBias = (u_aperature * u_focalLength * (u_nearPlane - u_focalDistance)) / ((u_focalDistance * u_focalLength) * u_nearPlane);

	//float actualDepth = linearize_depth(gl_FragCoord.z, 0.01, 1000.0);

	//float CoC = abs(actualDepth * CoCScale + CoCBias);

	float actualDepth = linearize_depth(texture(s_Depth, inUV).x, 0.01, 1000.0);

	float CoC = abs(actualDepth * CoCScale + CoCBias);

	CoC = clamp(1.0 - CoC, 0.0f, 1.0f);

	return CoC;
}

void main()
{
	float CoC = CalculateCircleOfConfusion();

	vec3 texColor = mix(texture2D(s_Scene, inUV), texture2D(s_Blur, inUV), 1.0 - CoC).rgb;

	frag_Color = vec4(texColor, 1.0);
}