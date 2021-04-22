#include "DepthOfFieldEffect.h"

void DepthOfFieldEffect::Init(unsigned width, unsigned height)
{
}

void DepthOfFieldEffect::ApplyEffect(PostEffect* buffer)
{
}

void DepthOfFieldEffect::Reshape(unsigned width, unsigned height)
{
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
}