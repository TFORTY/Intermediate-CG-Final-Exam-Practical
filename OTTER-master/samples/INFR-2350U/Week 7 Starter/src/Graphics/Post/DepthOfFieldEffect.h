#pragma once

#include "Graphics/Post/PostEffect.h"

class DepthOfFieldEffect : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	void ApplyEffect(PostEffect* buffer) override;

	void Reshape(unsigned width, unsigned height) override;

	//Getters
	float GetDownscale() const;

	//Setters
	void SetDownscale(float downscale);

private:
	float _downscale = 2.f;
	glm::vec2 _pixelSize;
};