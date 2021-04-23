#include "DepthOfFieldEffect.h"

void DepthOfFieldEffect::Init(unsigned width, unsigned height)
{
	////Load in the buffers
	//int index = int(_buffers.size());
	//_buffers.push_back(new Framebuffer());
	//_buffers[index]->AddColorTarget(GL_RGBA8);
	//_buffers[index]->AddDepthTarget();
	//_buffers[index]->Init(width, height);
	//index++;

	//_buffers.push_back(new Framebuffer());
	//_buffers[index]->AddColorTarget(GL_RGBA8);
	//_buffers[index]->AddDepthTarget();
	//_buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));
	//index++;

	//_buffers.push_back(new Framebuffer());
	//_buffers[index]->AddColorTarget(GL_RGBA8);
	//_buffers[index]->AddDepthTarget();
	//_buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));
	//index++;

	////Load in the shaders
	//int index2 = int(_shaders.size());
	//_shaders.push_back(Shader::Create());
	//_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	//_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
	//_shaders[index2]->Link();
	//index2++;

	//_shaders.push_back(Shader::Create());
	//_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER); 
	//_shaders[index2]->LoadShaderPartFromFile("shaders/Post/HoriBlur_frag.glsl", GL_FRAGMENT_SHADER);
	//_shaders[index2]->Link();
	//index2++;

	//_shaders.push_back(Shader::Create());
	//_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	//_shaders[index2]->LoadShaderPartFromFile("shaders/Post/VertBlur_frag.glsl", GL_FRAGMENT_SHADER);
	//_shaders[index2]->Link();
	//index2++;

	//_shaders.push_back(Shader::Create());
	//_shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	//_shaders[index2]->LoadShaderPartFromFile("shaders/Post/depth_of_field_frag.glsl", GL_FRAGMENT_SHADER);
	//_shaders[index2]->Link();
	//index2++;

	//_pixelSize = glm::vec2(1.f / width, 1.f / height);

	//PostEffect::Init(width, height);
}

void DepthOfFieldEffect::ApplyEffect(PostEffect* buffer)
{
	/*Draws previous buffer to first render target
	BindShader(0);
	buffer->BindColorAsTexture(0, 0, 0);
	_buffers[0]->RenderToFSQ();
	buffer->UnbindTexture(0);
	UnbindShader();

	Computes blur (horizontal and vertical)
	for (unsigned int i = 0; i < _passes; ++i)
	{
		Horizontal pass
		BindShader(1);
		_shaders[1]->SetUniform("u_PixelSize", _pixelSize.x);
		BindColorAsTexture(1, 0, 0);
		_buffers[1]->RenderToFSQ();
		UnbindTexture(0);
		UnbindShader();

		Vertical pass
		BindShader(2);
		_shaders[2]->SetUniform("u_PixelSize", _pixelSize.y);
		BindColorAsTexture(2, 0, 0);
		_buffers[2]->RenderToFSQ();
		UnbindTexture(0);
		UnbindShader();
	}

	Depth Pass
	BindShader(3);
	_shaders[3]->SetUniform("u_NearPlane", _nearPlane);
	_shaders[3]->SetUniform("u_FarPlane", _farPlane);
	_shaders[3]->SetUniform("u_FocalDistance", _focalDistance);
	_shaders[3]->SetUniform("u_FocalLength", _focalLength);
	_shaders[3]->SetUniform("u_Aperature", _aperature);
	_shaders[3]->SetUniform("u_MAXCoC", _maxCoC);
	buffer->BindColorAsTexture(0, 0, 0);
	BindColorAsTexture(1, 0, 1);
	_buffers[0]->RenderToFSQ();
	UnbindTexture(1);
	UnbindTexture(0);
	UnbindShader();*/
	/*BindColorAsTexture(0, 0, 0);
	_buffers[0]->RenderToFSQ();
	UnbindTexture(0);
	UnbindShader();*/

	////Composite 
	//BindShader(4);
	//buffer->BindColorAsTexture(0, 0, 0);
	//BindColorAsTexture(1, 0, 1);
	//_buffers[0]->RenderToFSQ();
	//UnbindTexture(1);
	//UnbindTexture(0);
	//UnbindShader();
}

void DepthOfFieldEffect::Reshape(unsigned width, unsigned height)
{
	/*_buffers[0]->Reshape(width, height);
	_buffers[1]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
	_buffers[2]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));*/
}