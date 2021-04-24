#version 420

out vec4 frag_color;

float linearize_depth(float d, float zNear, float zFar)
{
	float z_n = 2.0 * d - 1.0;
	return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

void main()
{
	float actualDepth = linearize_depth(gl_FragCoord.z, 0.01, 1000.0);

	frag_color = vec4(actualDepth, actualDepth, actualDepth, actualDepth);
}	