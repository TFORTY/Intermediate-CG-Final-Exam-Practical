#version 420

layout(location = 0) in vec2 inUV;

uniform float u_NearPlane;
uniform float u_FarPlane;

uniform float u_FocalDistance;
uniform float u_FocalLength;
uniform float u_Aperature;
uniform float u_MAXCoC;

out vec4 frag_color;

layout(binding = 0) uniform sampler2D s_Scene;
layout(binding = 1) uniform sampler2D s_DOF;

float linearize_depth(float d, float zNear, float zFar)
{
	float z_n = 2.0 * d - 1.0;
	return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

void main()
{
	float actualDepth = linearize_depth(gl_FragCoord.z, 0.01, 1000.0);

	frag_color = vec4(actualDepth, actualDepth, actualDepth, 1.0);

//	vec4 colorA = texture(s_Scene, inUV);
//	vec4 colorB = texture(s_DOF, inUV);
//
//	frag_color = 1.0 - (1.0 - colorA) * (1.0 - colorB);
}