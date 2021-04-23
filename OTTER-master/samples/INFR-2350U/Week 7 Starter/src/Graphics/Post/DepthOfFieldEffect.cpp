#include "DepthOfFieldEffect.h"

void DepthOfFieldEffect::Init(unsigned width, unsigned height)
{
	//Load in the buffers
	int index = int(_buffers.size());
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->AddDepthTarget();
	_buffers[index]->Init(width, height);
	index++;

	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->AddDepthTarget();
	_buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));
	index++;

	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->AddDepthTarget();
	_buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));
	index++;

	//Load in the shaders
	int index2 = int(_shaders.size());
	_shaders.push_back(Shader::Create());
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index2]->Link();
	index2++;
}

void DepthOfFieldEffect::ApplyEffect(PostEffect* buffer)
{
	
}

void DepthOfFieldEffect::Reshape(unsigned width, unsigned height)
{
	
}

float DepthOfFieldEffect::GetDownscale() const
{
	return _downscale;
}

void DepthOfFieldEffect::SetDownscale(float downscale)
{
	_downscale = downscale;
}