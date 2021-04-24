#include "DepthOfFieldEffect.h"

void DepthOfFieldEffect::Init(unsigned width, unsigned height)
{ 
    //Passthrough buffer
    int index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);
    index++;

    //CoC?


    //Horizontal Blur
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));
    index++;

    //Vertical Blur
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));
    index++;

    //Composite
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);
    


    ////Horizontal Blur
    //index++;
    //_buffers.push_back(new Framebuffer());
    //_buffers[index]->AddColorTarget(GL_RGBA8);
    //_buffers[index]->AddDepthTarget();
    //_buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));

    ////Blur Vertical
    //index++;
    //_buffers.push_back(new Framebuffer());
    //_buffers[index]->AddColorTarget(GL_RGBA8);
    //_buffers[index]->AddDepthTarget();
    //_buffers[index]->Init(unsigned(width / _downscale), unsigned(height / _downscale));

    ////Composite
    //index++;
    //_buffers.push_back(new Framebuffer());
    //_buffers[index]->AddColorTarget(GL_RGBA8);
    //_buffers[index]->AddDepthTarget();
    //_buffers[index]->Init(width, height);

    ////Composite2
    //index++;
    //_buffers.push_back(new Framebuffer());
    //_buffers[index]->AddColorTarget(GL_RGBA8);
    //_buffers[index]->AddDepthTarget();
    //_buffers[index]->Init(width, height);

    ////Passthough Test
    //index++;
    //_buffers.push_back(new Framebuffer());
    //_buffers[index]->AddColorTarget(GL_RGBA8);
    //_buffers[index]->AddDepthTarget();
    //_buffers[index]->Init(width, height);

    //Loads the shaders
    int index2 = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;
     
    /*_shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/dof_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;*/

    _shaders.push_back(Shader::Create());  
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    //_shaders[index2]->LoadShaderPartFromFile("shaders/Post/dof_horizontal_blur.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/HoriBlur_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;

    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    //_shaders[index2]->LoadShaderPartFromFile("shaders/Post/dof_vertical_blur.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/VertBlur_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;

    _shaders.push_back(Shader::Create());
    _shaders[index2]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index2]->LoadShaderPartFromFile("shaders/Post/dof_composite_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index2]->Link();
    index2++;

    //index++;
    //_shaders.push_back(Shader::Create());
    //_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    //_shaders[index]->LoadShaderPartFromFile("shaders/Post/dof_composite2_frag.glsl", GL_FRAGMENT_SHADER);
    //_shaders[index]->Link();

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
    
    for (unsigned i = 0; i < _passes; ++i)
    {
        //Horizontal
        BindShader(1);
        _shaders[1]->SetUniform("u_PixelSize", _pixelSize.x);
        BindColorAsTexture(1, 0, 0);
        _buffers[1]->RenderToFSQ();
        UnbindTexture(0);
        UnbindShader();

        //Vertical
        BindShader(2);
        _shaders[2]->SetUniform("u_PixelSize", _pixelSize.y);
        BindColorAsTexture(2, 0, 0);
        _buffers[2]->RenderToFSQ();
        UnbindTexture(0);
        UnbindShader();
    }

    //Composite
    BindShader(3);
    buffer->BindColorAsTexture(0, 0, 0);
    BindColorAsTexture(1, 0, 1);
    _buffers[0]->RenderToFSQ();
    UnbindTexture(1);
    UnbindTexture(0);
    UnbindShader();
   
    ////Depth
    //BindShader(1);
    //buffer->BindColorAsTexture(0, 0, 0);
    //_buffers[4]->RenderToFSQ();
    //buffer->UnbindTexture(0);
    //UnbindShader();

    ////Composite 2
    //BindShader(5);
    //BindColorAsTexture(5, 0, 0);
    //BindColorAsTexture(0, 0, 1);
    //_buffers[1]->RenderToFSQ();
    //UnbindTexture(1);
    //UnbindTexture(0);
    //UnbindShader();

    ////Gets the Blur
    //for (unsigned i = 0; i < _passes; i++)
    //{
    //    //Horizontal
    //    BindShader(2);
    //    _shaders[2]->SetUniform("u_PixelSize", _pixelSize.x);
    //    BindColorAsTexture(1, 0, 0);
    //    _buffers[2]->RenderToFSQ();
    //    UnbindTexture(0);
    //    UnbindShader();

    //    //Vertical
    //    BindShader(3);
    //    _shaders[3]->SetUniform("u_PixelSize", _pixelSize.y);
    //    BindColorAsTexture(2, 0, 0);
    //    _buffers[1]->RenderToFSQ();
    //    UnbindTexture(0);
    //    UnbindShader();
    //}

    ////Composite
    //BindShader(4);
    //BindColorAsTexture(5, 0, 0);
    //BindColorAsTexture(1, 0, 1);
    //_buffers[0]->RenderToFSQ();
    //UnbindTexture(1);
    //UnbindTexture(0);
    //UnbindShader();
}

void DepthOfFieldEffect::Reshape(unsigned width, unsigned height)
{
    _buffers[0]->Reshape(width, height);
    _buffers[1]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
    _buffers[2]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
    _buffers[3]->Reshape(width, height);
    /*_buffers[0]->Reshape(width, height);
    _buffers[1]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
    _buffers[2]->Reshape(unsigned(width / _downscale), unsigned(height / _downscale));
    _buffers[3]->Reshape(width, height);*/
}