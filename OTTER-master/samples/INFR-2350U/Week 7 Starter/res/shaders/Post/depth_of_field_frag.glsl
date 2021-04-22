#version 420

//Referenced from https://www.programmersought.com/article/226451461/

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout(binding = 0) uniform sampler2D s_Tex;

uniform float u_Depth = 0.7;

void main()
{
	frag_color = texture2D(s_Tex, inUV);

	float blur = 0;

	float near_distance = 10.0;
	float far_distance = 10.0;

	float near_plane = -20.0;
	float far_plane = -25.0;

	if (u_Depth <= near_plane && u_Depth >= far_plane)
	{
		blur = 0;
	}
	else if (u_Depth > near_plane)
	{
		blur = clamp(u_Depth, near_plane, near_plane + near_distance);
		blur = (blur - near_plane) / near_distance;
	}
	else if (u_Depth < far_plane)
	{
		blur = clamp(u_Depth, far_plane - far_distance, far_plane);
		blur = (far_plane - blur) / far_distance;
	}

	frag_color.a = blur;
}