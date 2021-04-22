#pragma once

#include "Graphics/Post/PostEffect.h"

class DepthOfFieldEffect : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	void ApplyEffect(PostEffect* buffer) override;

	void Reshape(unsigned width, unsigned height) override;

	//Getters
	float GetDepth() const;
	unsigned GetPasses() const;
	float GetDownscale() const;

	//Setters
	void SetDepth(float depth);
	void SetPasses(unsigned passes);
	void SetDownscale(float downscale);

private:
	float _depth = 0.7;
	float _downscale = 2.f;
	unsigned _passes = 10;
	glm::vec2 _pixelSize;
};