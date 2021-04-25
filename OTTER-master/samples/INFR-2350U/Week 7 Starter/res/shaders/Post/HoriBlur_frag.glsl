#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout(binding = 0) uniform sampler2D s_Tex;

const float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

uniform float u_PixelSize;

void main()
{
	vec3 result = texture(s_Tex, inUV).rgb * weight[0]; // current fragment's contribution

	result += texture(s_Tex, vec2(inUV.x - u_PixelSize * 4, inUV.y)).rgb * weight[4];
	result += texture(s_Tex, vec2(inUV.x - u_PixelSize * 3, inUV.y)).rgb * weight[3];
	result += texture(s_Tex, vec2(inUV.x - u_PixelSize * 2, inUV.y)).rgb * weight[2];
	result += texture(s_Tex, vec2(inUV.x - u_PixelSize    , inUV.y)).rgb * weight[1];
	result += texture(s_Tex, vec2(inUV.x + u_PixelSize    , inUV.y)).rgb * weight[1];
	result += texture(s_Tex, vec2(inUV.x + u_PixelSize * 2, inUV.y)).rgb * weight[2];
	result += texture(s_Tex, vec2(inUV.x + u_PixelSize * 3, inUV.y)).rgb * weight[3];
	result += texture(s_Tex, vec2(inUV.x + u_PixelSize * 4, inUV.y)).rgb * weight[4];

	frag_color = vec4(result, 1.0);

	//frag_color = vec4(0.0);

//		frag_color += texture(s_Tex, vec2(inUV.x - 4.0 * u_PixelSize, inUV.y)) * 0.06;
//		frag_color += texture(s_Tex, vec2(inUV.x - 3.0 * u_PixelSize, inUV.y)) * 0.09;
//		frag_color += texture(s_Tex, vec2(inUV.x - 2.0 * u_PixelSize, inUV.y)) * 0.12;
//		frag_color += texture(s_Tex, vec2(inUV.x -	     u_PixelSize, inUV.y)) * 0.15;
//		frag_color += texture(s_Tex, vec2(inUV.x,					  inUV.y)) * 0.16;
//		frag_color += texture(s_Tex, vec2(inUV.x +	     u_PixelSize, inUV.y)) * 0.15;
//		frag_color += texture(s_Tex, vec2(inUV.x + 2.0 * u_PixelSize, inUV.y)) * 0.12;
//		frag_color += texture(s_Tex, vec2(inUV.x + 3.0 * u_PixelSize, inUV.y)) * 0.09;
//		frag_color += texture(s_Tex, vec2(inUV.x + 4.0 * u_PixelSize, inUV.y)) * 0.06;
	
//	frag_color += texture(s_Tex, vec2(inUV.x - 4.0 * u_PixelSize, inUV.y)) * 0.06;
//	frag_color += texture(s_Tex, vec2(inUV.x - 3.0 * u_PixelSize, inUV.y)) * 0.09;
//	frag_color += texture(s_Tex, vec2(inUV.x - 2.0 * u_PixelSize, inUV.y)) * 0.12;
//	frag_color += texture(s_Tex, vec2(inUV.x -	     u_PixelSize, inUV.y)) * 0.15;
//	frag_color += texture(s_Tex, vec2(inUV.x,					  inUV.y)) * 0.16;
//	frag_color += texture(s_Tex, vec2(inUV.x +	     u_PixelSize, inUV.y)) * 0.15;
//	frag_color += texture(s_Tex, vec2(inUV.x + 2.0 * u_PixelSize, inUV.y)) * 0.12;
//	frag_color += texture(s_Tex, vec2(inUV.x + 3.0 * u_PixelSize, inUV.y)) * 0.09;
//	frag_color += texture(s_Tex, vec2(inUV.x + 4.0 * u_PixelSize, inUV.y)) * 0.06;
}