#version 420

layout(location = 0) in vec2 inUV;

float FocalDistance = 20.f;
float FocalLength = 0.0303f;
float Aperature = 0.6062f;
float MAXCoC = 1.0f; //maximum diameter of CoC

float depthEye;

out vec4 frag_color;

float linearize_depth(float d, float zNear, float zFar)
{
	float z_n = 2.0 * d - 1.0;
	return 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
}

float CalculateCircleOfConfusion(float depthEye)
{
	float S2 = abs(depthEye);

	float CoC = Aperature * (abs(S2 - FocalDistance) / S2) * (FocalLength / (FocalDistance - FocalLength));

	float SensorHeight = 0.024f;

	float PercentOfSensor = CoC / SensorHeight;

	float BlurFactor = clamp(PercentOfSensor, 0.0f, MAXCoC);

	return BlurFactor;
}

void main()
{
	float actualDepth = linearize_depth(gl_FragCoord.z, 0.01, 1000.0);

	frag_color.a = CalculateCircleOfConfusion(actualDepth);
}