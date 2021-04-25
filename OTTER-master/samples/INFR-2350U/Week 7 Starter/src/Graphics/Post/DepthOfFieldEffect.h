#pragma once

#include "Graphics/Post/PostEffect.h"

class DepthOfFieldEffect : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	void ApplyEffect(PostEffect* buffer) override;

	void Reshape(unsigned width, unsigned height) override;

	//Getters
	//float GetDownscale() const { return _downscale; }

	float GetPasses() const { return _passes; }
	float GetFocalDistance() const { return _focalDistance; }
	float GetFocalLength() const { return _focalLength; }
	float GetAperature() const { return _aperature; }
	float GetNearPlane() const { return _nearPlane; }
	float GetFarPlane() const { return _farPlane; }

	//Setters
	//void SetDownscale(float downscale) { _downscale = downscale; }
	void SetPasses(unsigned passes) { _passes = passes; }
	void SetFocalDistance(float distance) { _focalDistance = distance; }
	void SetFocalLength(float length) { _focalLength = length; }
	void SetAperature(float aperature) { _aperature = aperature; }
	void SetNearPlane(float nearPlane) { _nearPlane = nearPlane; }
	void SetFarPlane(float farPlane) { _farPlane = farPlane; }

private:
	//float _downscale = 2.f;
	unsigned _passes = 10.f;
	float _focalDistance = 20.f;
	float _focalLength = 0.0303f;
	float _aperature = 0.6062f;
	float _nearPlane = 0.01f;
	float _farPlane = 1000.0f;
	//glm::vec2 _pixelSize;
};