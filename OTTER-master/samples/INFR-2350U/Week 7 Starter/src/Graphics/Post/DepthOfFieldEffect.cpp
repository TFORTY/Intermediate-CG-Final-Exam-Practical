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

    //Blur
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);
    index++;

    //Passthrough 
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

    //Gaussian Blur
    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/gaussian_blur_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;

    //Composite
    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/dof_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();

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
        //Horizontal Blur
        BindShader(1);
        _shaders[1]->SetUniform("horizontal", true);
        BindColorAsTexture(0, 0, 0);
        _buffers[3]->RenderToFSQ();
        buffer->UnbindTexture(0); 
         
        //Vertical Blur
        _shaders[1]->SetUniform("horizontal", false);  
        BindColorAsTexture(0, 0, 0);
        _buffers[1]->RenderToFSQ();
        buffer->UnbindTexture(0);
         
        UnbindShader();  
    }
     
    //Passthrough  
    buffer->BindColorAsTexture(0, 0, 0);
    _buffers[2]->RenderToFSQ();
    buffer->UnbindTexture(0);

    //Composite
    BindShader(2);
    _shaders[2]->SetUniform("u_focalDistance", _focalDistance);
    _shaders[2]->SetUniform("u_focalLength", _focalLength);
    _shaders[2]->SetUniform("u_aperature", _aperature);
    _shaders[2]->SetUniform("u_nearPlane", _nearPlane);
    _shaders[2]->SetUniform("u_farPlane", _farPlane);
    buffer->BindColorAsTexture(0, 0, 0);
    buffer->BindDepthAsTexture(0, 29);
    BindColorAsTexture(1, 0, 1);
    _buffers[0]->RenderToFSQ();
    UnbindTexture(29);
    UnbindTexture(0);
    UnbindShader();
}