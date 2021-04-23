#version 420

layout(location = 0) in vec2 inUV;

uniform float u_NearPlane;
uniform float u_FarPlane;

uniform float u_FocalDistance;
uniform float u_FocalLength;
uniform float u_Aperature;
uniform float u_MAXCoC;

in float depthEye;

out vec4 frag_color;

layout(binding = 0) uniform sampler2D s_Scene;
layout(binding = 1) uniform sampler2D s_DepthOfField;

float linearize_depth(float d, float zNear, float zFar)
{
	float z_n = 2.0 * d - 1.0;
	return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

float CalculateCircleOfConfusion(float depthEye)
{
	float S2 = abs(depthEye);

	float CoC = u_Aperature * (abs(S2 - u_FocalDistance) / S2) * (u_FocalLength / (u_FocalDistance - u_FocalLength));

	float SensorHeight = 0.024f;

	float PercentOfSensor = CoC / SensorHeight;

	float BlurFactor = clamp(PercentOfSensor, 0.0f, u_MAXCoC);

	return BlurFactor;
}

void main()
{
	vec4 colorA = texture(s_Scene, inUV);
	vec4 colorB = texture(s_DepthOfField, inUV);

	float actualDepth = linearize_depth(gl_FragCoord.z, u_NearPlane, u_FarPlane);
	float calcCoC = CalculateCircleOfConfusion(actualDepth);

	float diffCoC = u_MAXCoC - calcCoC;

	frag_color = (colorA * diffCoC) + (colorB * calcCoC);

	//frag_color.a = CalculateCircleOfConfusion(actualDepth);

	//colorB.a = calcCoC;

	//frag_color = colorA * colorB

	//frag_color = 1.0 - (1.0 - colorA) * (1.0 - colorB);
}