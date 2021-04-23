#pragma once

#include "Graphics/Post/PostEffect.h"

class DepthOfFieldEffect : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	void ApplyEffect(PostEffect* buffer) override;

	void Reshape(unsigned width, unsigned height) override;

	//Getters
	float GetDownscale() const { return _downscale; }
	unsigned GetPasses() const { return _passes; }
	float GetNearPlane() const { return _nearPlane; }
	float GetFarPlane() const { return _farPlane; }
	float GetFocalDistance() const { return _focalDistance; }
	float GetFocalLength() const { return _focalLength; }
	float GetAperature() const { return _aperature; }
	float GetMaxCoC() const { return _maxCoC; }

	//Setters
	void SetDownscale(float downscale) { _downscale = downscale; }
	void SetPasses(unsigned passes) { _passes = passes; }
	void SetNearPlane(float nearPlane) { _nearPlane = nearPlane; }
	void SetFarPlane(float farPlane) { _farPlane = farPlane; }
	void SetFocalDistance(float focalDistance) { _focalDistance = focalDistance; }
	void SetFocalLength(float focalLength) { _focalLength = focalLength; }
	void SetAperature(float aperature) { _aperature = aperature; }
	void SetMaxCoC(float maxCoC) { _maxCoC = maxCoC; }

private:
	float _downscale = 16.f;
	unsigned _passes = 10.f;
	float _nearPlane = 0.01f;
	float _farPlane = 1000.f;
	float _focalDistance = 20.f;
	float _focalLength = 0.0303f;
	float _aperature = 0.6062f;
	float _maxCoC = 1.0f;
	glm::vec2 _pixelSize;
};