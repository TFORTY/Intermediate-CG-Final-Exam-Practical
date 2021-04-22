#version 420

uniform vec4 u_lightPos;
uniform vec4 u_colour;

in VertexData
{
	vec3 normal;
	vec3 texCoord;
	vec4 colour;
	vec3 posEye;
} vIn;

in float depthEye;

float S1 = 20.0f;
float F = 0.0303f;
float A = 0.6062f;
float MAXCoC = 1.0f;

layout(location = 0) out vec4 frag_color;

float CalculateCircleOfConfusion()
{
	float S2 = abs(depthEye);

	float CoC = A * (abs(S2 - S1) / S2) * (F / (S1 - F));

	float SensorHeight = 0.024f;

	float PercentOfSensor = CoC / SensorHeight;

	float blurFactor = clamp(PercentOfSensor, 0.0, MAXCoC);

	return blurFactor;
}

vec3 CalculatePixelColor()
{
	vec3 L = normalize(u_lightPos.xyz - vIn.posEye);
	vec3 N = normalize(vIn.normal);

	float diffuse = max(0.0, dot(N, L));

	if (diffuse <= 0.00) diffuse = 0.00;
	else if (diffuse <= 0.25) diffuse = 0.25;
	else if (diffuse <= 0.50) diffuse = 0.50;
	else if (diffuse <= 0.75) diffuse = 0.75;
	else diffuse = 1.00;

	return vec3(0.5, 0.5, 0.5) * (diffuse * 0.8f) + u_colour.rgb;
}

void main()
{
	frag_color.rgb = CalculatePixelColor();

	frag_color.a = CalculateCircleOfConfusion();
}