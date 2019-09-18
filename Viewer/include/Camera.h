#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "MeshModel.h"

/*
 * Camera class. This class takes care of all the camera transformations and manipulations.
 *
 * Implementation suggestion:
 * --------------------------
 * Make the Camera class be a subclass of MeshModel, so you can easily and elegantly render 
 * the cameras you have added to the scene.
 */
class Camera
{
private:
	glm::mat4x4 viewWorldTransform;
	glm::mat4x4 viewTransformation;
	glm::mat4x4 projectionTransformation;
	glm::mat4x4 orthographicTransformation;
	glm::mat4x4 scalingTransformation;
	glm::vec3 oldeye;
	glm::vec3 oldat;
	float zoom;
	float _near;
	float _far;
	float aspectRatio;
	float FOV;
	bool isCurrent;
	int number;


public:
	Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	~Camera();
	Camera();
	void setCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void scaleTransform(glm::vec3& vect);
	void setOrthographicProjection(float height, float aspectRatio, float _near, float _far);
	void setPerspectiveProjection(float &fovy, float &aspect, float &_near, float &_far);
	void setCameraScale();

	//getters/setters
	//getters
	const glm::mat4 getViewTransformation();
	const glm::mat4 getProjectionTransformation();
	const glm::mat4 getOrthographicTransformation();
	const glm::mat4x4 getViewWorldTransform() const { return this->viewWorldTransform; }
	const float getNear() const { return this->_near; }
	const float getFar() const { return this->_far; }
	const float getAspectRatio() const { return this->aspectRatio; }
	const float getFOV() const { return this->FOV; }
	const bool getCurrent() const { return this->isCurrent; }

	//setters
	void setNear(const float &n) { this->_near = n; }
	void setFar(const float &f) { this->_far = f; }
	void setAspectRatio(const float &ar) { this->aspectRatio = ar; }
	void setFOV(const float &f) { this->FOV = f; }
	void SetZoom(const float zoom);
	void setCurrent(const bool &b) { this->isCurrent = b; }
	void setCameraViewWorldTransform(glm::vec4&);
	void setCameraNum(const int& i) { this->number = i; }
};
