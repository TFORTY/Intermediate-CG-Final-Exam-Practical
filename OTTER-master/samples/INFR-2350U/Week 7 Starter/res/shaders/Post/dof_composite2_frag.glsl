#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout(binding = 0) uniform sampler2D s_colorTex;
layout(binding = 1) uniform sampler2D s_depthTex;

void main()
{
	vec4 colorA = texture(s_colorTex, inUV);
	vec4 colorB = texture(s_depthTex, inUV);

	frag_color = vec4(colorA.rgb, colorB.r);
}