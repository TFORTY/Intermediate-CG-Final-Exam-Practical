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

	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->AddDepthTarget();
	_buffers[index]->Init(width, height);

	//Load in the shaders
	int index2 = int(_shaders.size());
	_shaders.push_back(Shader::Create());
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index2]->Link();
	index2++;

	_shaders.push_back(Shader::Create());
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index2]->LoadShaderPartFromFile("shaders/Post/depth_of_field_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index2]->Link();
	index2++;

	_shaders.push_back(Shader::Create());
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index2]->LoadShaderPartFromFile("shaders/Post/HoriBlur_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index2]->Link();
	index2++;

	_shaders.push_back(Shader::Create());
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index2]->LoadShaderPartFromFile("shaders/Post/VertBlur_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index2]->Link();
	index2++;

	_shaders.push_back(Shader::Create());
	_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index2]->LoadShaderPartFromFile("shaders/Post/dof_composite_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index2]->Link();
	index2++;

	_pixelSize = glm::vec2(1.f / width, 1.f / height);

	PostEffect::Init(width, height);
}

void DepthOfFieldEffect::ApplyEffect(PostEffect* buffer)
{
	//Draws previous buffer to first render target
	BindShader(0);
	buffer->BindColorAsTexture(0, 0, 0);
	_buffers[0]->RenderToFSQ();
	buffer->UnbindTexture(0);
	UnbindShader();

	//Depth Pass
	BindShader(1);
	_shaders[0]->SetUniform("u_Depth", _depth);
	BindColorAsTexture(0, 0, 0);
	_buffers[1]->RenderToFSQ();
	UnbindTexture(0);
	UnbindShader();

	//Computes blur (vert and hori)
	for (unsigned int i = 0; i < _passes; ++i)
	{
		//Horizontal pass
		BindShader(2);
		_shaders[1]->SetUniform("u_PixelSize", _pixelSize.x);
		BindColorAsTexture(1, 0, 0);
		_buffers[2]->RenderToFSQ();
		UnbindTexture(0);
		UnbindShader();

		//Vertical pass
		BindShader(3);
		_shaders[2]->SetUniform("u_PixelSize", _pixelSize.y);
		BindColorAsTexture(2, 0, 0);
		_buffers[3]->RenderToFSQ();
		UnbindTexture(0);
		UnbindShader();
	}

	//Composite scene and bloom
	BindShader(4);
	buffer->BindColorAsTexture(0, 0, 0);
	BindColorAsTexture(1, 0, 1);
	_buffers[0]->RenderToFSQ();
	UnbindTexture(1);
	UnbindTexture(0);
	UnbindShader();
}

void DepthOfFieldEffect::Reshape(unsigned width, unsigned height)
{
	_buffers[0]->Reshape(width, height);
	_buffers[1]->Reshape(width, height);
	_buffers[2]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
	_buffers[3]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
	_buffers[4]->Reshape(width, height);
	//_buffers[2]->Reshape(width, height);
	//_buffers[1]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
	//_buffers[2]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
	//_buffers[3]->Reshape(width, height);
}

float DepthOfFieldEffect::GetDepth() const
{
	return _depth;
}

unsigned DepthOfFieldEffect::GetPasses() const
{
	return _passes;
}

float DepthOfFieldEffect::GetDownscale() const
{
	return _downscale;
}

void DepthOfFieldEffect::SetDepth(float depth)
{
	_depth = depth;
}

void DepthOfFieldEffect::SetPasses(unsigned passes)
{
	_passes = passes;
}

void DepthOfFieldEffect::SetDownscale(float downscale)
{
	_downscale = downscale;
	Reshape(_buffers[0]->_width, _buffers[0]->_height);
}