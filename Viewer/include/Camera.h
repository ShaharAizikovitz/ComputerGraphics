#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "MeshModel.h"
#include "Definitions.h"

/*
 * Camera class. This class takes care of all the camera transformations and manipulations.
 *
 * Implementation suggestion:
 * --------------------------
 * Make the Camera class be a subclass of MeshModel, so you can easily and elegantly render 
 * the cameras you have added to the scene.
 */
class Camera : public MeshModel
{
private:
	glm::mat4 viewWorldTransform;
	glm::mat4 viewTransformation;
	glm::mat4 perspectiveTransformation;
	glm::mat4 orthographicTransformation;
	glm::mat4 scalingTransformation;
	glm::vec4 eye;
	glm::vec4 at;
	glm::vec4 up;
	float zoom;
	int left;
	int right;
	int top;
	int bottom;
	int zNear;
	int zFar;
	float aspectRatio;
	float FOV;
	bool isCurrent;
	bool isOrtho;
	int index;
	void init();
	void updateProjection();

public:
	Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	~Camera();
	Camera();
	void setCameraLookAt();
	void setCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void scaleTransform(glm::vec3& vect);
	void setOrthographicProjection(const int left, const int right, const int bottom, const int top);
	void setPerspectiveProjection(float &fovy, float &aspect, int &_near, int &_far);
	void setCameraScale();

	//getters/setters
	//getters
	const glm::mat4 getViewTransformation();
	const glm::mat4 getperspectiveTransformation();
	const glm::mat4 getOrthographicTransformation();
	const glm::mat4 getViewWorldTransform() const { return this->viewWorldTransform; }
	const glm::mat4 getProjection();
	const int getNear() const { return this->zNear; }
	const int getFar() const { return this->zFar; }
	const float getAspectRatio() const { return this->aspectRatio; }
	const float getFOV() const { return this->FOV; }
	const bool getCurrent() const { return this->isCurrent; }
	const int getCameraIndex() const { return this->index; }
	glm::vec4 getEye() const { return this->eye; }
	glm::vec4 getAt() const { return this->at; }
	glm::vec4 getUp() const { return this->up; }
	int getLeft() const { return this->left; }
	int getRight() const { return this->right; }
	int getBottom() const { return this->bottom; }
	int getTop() const { return this->top; }
	bool getIsOrtho() const { return this->isOrtho; }

	//setters
	void setNear(const int &n) { this->zNear = n; updateProjection(); }
	void setFar(const int &f) { this->zFar = f; updateProjection(); }
	void setAspectRatio(const float &ar) { this->aspectRatio = ar; updateProjection();  }
	void setFOV(const float &f) { this->FOV = f; updateProjection(); }
	void SetZoom(const float zoom);
	void setCurrent(const bool &b) { this->isCurrent = b; }
	void setCameraViewWorldTransform(glm::vec4&);
	void setCameraNum(const int& i) { this->index = i; }
	void setIsortho(const bool& b) { this->isOrtho = b; }
	void setLeft(const int& l) { this->left = l; updateProjection();
	}
	void setRight(const int& r) { this->right = r; updateProjection();
	}
	void setTop(const int& t) { this->left = t; updateProjection();
	}
	void setBottom(const int& b) { this->bottom = b; updateProjection();
	}
	void setEye(const glm::vec4 e) { this->eye = e; setCameraLookAt(); }
	void setUp(const glm::vec4 u) { this->up = u; setCameraLookAt(); }
	void setAt(const glm::vec4 a) { this->at = a; setCameraLookAt(); }

};
