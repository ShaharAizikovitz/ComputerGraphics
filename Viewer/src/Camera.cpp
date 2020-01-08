#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

#define PI 3.14159265358
#define INIT_SCALE 1000

//ctor
Camera::Camera()
{
	//SetPerspectiveProjection(45, 280, 1, 10);
	setCameraLookAt(glm::vec3(0.0f, 0.0f, 50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) :
	zoom(1.0)
{
	//SetPerspectiveProjection(45, 1, 200, 500);
	oldeye = eye;
	oldat = at;
	FOV = 45.0f;
	aspectRatio = 0.5f;
	left = -200;
	right = 200;
	top = 200;
	bottom = -200;
	_near = 100;
	_far = 500;
	setCameraLookAt(eye, at, up);
	setPerspectiveProjection(FOV , aspectRatio , _near, _far);
	setOrthographicProjection(left, right, bottom, top, _near, _far);
	setCameraViewWorldTransform(glm::vec4(0, 0, 0, 1)); 
	setCameraScale();
}

Camera::~Camera()
{
}


void Camera::setCameraScale()
{
	this->scalingTransformation = glm::mat4x4(glm::vec4(INIT_SCALE, 0, 0, 0), glm::vec4(0, INIT_SCALE, 0, 0), glm::vec4(0, 0, INIT_SCALE, 0), glm::vec4(0, 0, 0, 1));
}

const glm::mat4 Camera::getViewTransformation() {
	//return viewTransformation;
	return (this->isOrtho) ? this->viewTransformation * this->orthographicTransformation : this->viewTransformation * this->perspectiveTransformation;
}
const glm::mat4 Camera::getperspectiveTransformation()
{
	return this->perspectiveTransformation;
}
const glm::mat4 Camera::getOrthographicTransformation()
{
	return this->orthographicTransformation;
}
void Camera::setCameraViewWorldTransform(glm::vec4 &v)
{
	this->viewWorldTransform = glm::mat4x4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), v); 
}

void Camera::setCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	glm::vec3 z = glm::normalize(eye - at);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::normalize(glm::cross(z, x));

	glm::vec4 t = glm::vec4(0, 0, 0, 1);
	glm::vec4 x4 = glm::vec4(x, 0);
	glm::vec4 y4 = glm::vec4(y, 0);
	glm::vec4 z4 = glm::vec4(z, 0);

	glm::mat4 c(x4, y4, z4, t);
	glm::mat4 iden(1);
	iden[3] = iden[3] - glm::vec4(eye,0);

	this->viewTransformation = c * iden;

}

//Function create the Normalized projection matrix by (P=ST)
//1. T = translate the center of the volume to the origin
//2. S = Scale to the volume of unit cube
void Camera::setOrthographicProjection(
	const int left,
	const int right,
	const int bottom,
	const int top,
	const int _near,
	const int _far)
{
	
	glm::vec4 v1 = glm::vec4( (float)2 / 400, 0, 0, 0);
	glm::vec4 v2 = glm::vec4(0, (float)2 / (top - bottom), 0, 0);
	glm::vec4 v3 = glm::vec4(0, 0, (float)2 / (_near - _far), 0);
	glm::vec4 v4 = glm::vec4(-(float)(right + left) / (right - left), -(float)(top + bottom) /(top - bottom), -(float)(_far + _near) / (_far - _near), 1);

	this->orthographicTransformation = glm::mat4(v1, v2, v3, v4);
}

void Camera::setPerspectiveProjection(float &fovy, float &aspectRatio, int &near, int &far)
{
	float nearHeight = 2 * near * tan(0.5*fovy * PI / 180);
	float nearWidth = aspectRatio * nearHeight;
	float t = 0.5 * nearHeight;
	float b = -0.5 * nearHeight;
	float l = -0.5 * nearWidth;
	float r = 0.5 * nearWidth;
	if (near == far || t == b) return;
	/*std::cout << "near " << near << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			std::cout << this->perspectiveTransformation[i][j] << " ";
		std::cout << std::endl;
	}*/
	std::cout << std::endl;
	glm::vec4 v1(2 * near / (r - l), 0, 0, 0);
	glm::vec4 v2(0, 2 * near / (t - b), 0, 0);
	glm::vec4 v3((r + l) / (r - l), (t + b) / (t - b), -1 * (far + near) / (far - near), -1);
	glm::vec4 v4(0, 0, -2 *( far * near )/ (far - near), 0);
	this->perspectiveTransformation = glm::mat4(v1, v2, v3, v4);
	/*this->perspectiveTransformation = glm::mat4(glm::vec4(2 * near / (r - l), 0, (r + l) / (r - l), 0),
											   glm::vec4(0, 2 * near / (t - b), (t + b) / (t - b), 0),
		                                       glm::vec4(0, 0, -1 * (far + near) / (far - near), -2 * (far * near) / (far - near)),
		                                       glm::vec4(0, 0, -1, 0));*/
	/*for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			std::cout << this->perspectiveTransformation[i][j] << " ";
		std::cout << std::endl;
	}*/
}

void Camera::SetZoom(const float zoom)
{

}

void Camera::scaleTransform(glm::vec3& vect) {
	vect.x = vect.x * 50;
	vect.x = vect.y * 50;
}

