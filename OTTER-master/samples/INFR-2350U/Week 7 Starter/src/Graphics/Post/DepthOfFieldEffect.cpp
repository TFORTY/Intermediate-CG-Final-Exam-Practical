#include "DepthOfFieldEffect.h"

void DepthOfFieldEffect::Init(unsigned width, unsigned height)
{ 
    //Passthrough
    int index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);
    index++;
    //Blur
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);
    index++;
    //Composite 
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);
    index++;

    //Load in the shaders
    int index2 = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER); 
    _shaders[index2]->Link();
    index2++;
    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/gaussian_blur_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;
    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;
    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/dof_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();

    //_pixelSize = glm::vec2(1.f / width, 1.f / height);

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

    //Blur
    for (int i = 0; i < _passes; ++i)
    {
        BindShader(1);
        _shaders[2]->SetUniform("horizontal", (int)true);
        BindColorAsTexture(0, 0, 0);
        _buffers[2]->RenderToFSQ();
        buffer->UnbindTexture(0); 
         
        _shaders[2]->SetUniform("horizontal", (int)false);  
        BindColorAsTexture(0, 0, 0);
        _buffers[1]->RenderToFSQ();
        buffer->UnbindTexture(0);
         
        UnbindShader();  
    }
     
    //Passthrough  
    BindShader(2);
    buffer->BindColorAsTexture(0, 0, 0);
    _buffers[0]->RenderToFSQ();
    buffer->UnbindTexture(0);
    UnbindShader();

    //Composite
    BindShader(3);
    _shaders[3]->SetUniform("u_focalDistance", _focalDistance);
    _shaders[3]->SetUniform("u_focalLength", _focalLength);
    _shaders[3]->SetUniform("u_aperature", _aperature);
    _shaders[3]->SetUniform("u_nearPlane", _nearPlane);
    _shaders[3]->SetUniform("u_farPlane", _farPlane);
    buffer->BindColorAsTexture(0, 0, 0);
    buffer->BindColorAsTexture(0, 0, 1); 
    buffer->BindDepthAsTexture(0, 29);
    BindColorAsTexture(1, 0, 1);
    _buffers[0]->RenderToFSQ();
    UnbindTexture(1);
    UnbindTexture(29);
    UnbindTexture(0);
    UnbindShader();
}

void DepthOfFieldEffect::Reshape(unsigned width, unsigned height)
{
    _buffers[0]->Reshape(width, height);
    _buffers[1]->Reshape(width, height);
    _buffers[2]->Reshape(width, height);
    //_buffers[1]->Reshape((float)width / _downscale, (float)height / _downscale);
    //_buffers[2]->Reshape((float)width / _downscale, (float)height / _downscale);
    //_buffers[3]->Reshape(width, height);
}