#pragma once

#include "Graphics/Post/PostEffect.h"

class DepthOfFieldEffect : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	void ApplyEffect(PostEffect* buffer) override;

	//Getters
	float GetFocalDistance() const { return _focalDistance; }
	float GetFocalLength() const { return _focalLength; }
	float GetAperature() const { return _aperature; }

	//Setters
	void SetFocalDistance(float distance) { _focalDistance = distance; }
	void SetFocalLength(float length) { _focalLength = length; }
	void SetAperature(float aperature) { _aperature = aperature; }

private:
	unsigned _passes = 10.f;
	float _focalDistance = 20.f;
	float _focalLength = 0.0303f;
	float _aperature = 0.6062f;
	float _nearPlane = 0.01f;
	float _farPlane = 1000.0f;
};