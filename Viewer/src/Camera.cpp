#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

//ctor
Camera::Camera()
{
	init();
	setCameraLookAt();
	setCameraLookAt(glm::vec3(0.0f, 0.0f, 50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) :
	zoom(1.0)
{
	init();
	setCameraLookAt(eye, at, up);
	setPerspectiveProjection(FOV , aspectRatio , zNear, zFar);
	setOrthographicProjection(left, right, bottom, top);
}
Camera::~Camera()
{
}
void Camera::init()
{
	this->isOrtho = false;
	FOV = 45.0f;
	aspectRatio = 0.7f;
	left = -200;
	right = 200;
	top = 200;
	bottom = -200;
	zNear = 100;
	zFar = 500;
	this->viewTransformation = glm::mat4(1);
	this->perspectiveTransformation = glm::mat4(1);
	this->orthographicTransformation = glm::mat4(1);
	this->scalingTransformation = glm::mat4(1);
	this->eye = glm::vec4(0.0f, 0.0f, 50.0f, 0.0f);
	this->at = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	this->up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
}

void Camera::setCameraScale()
{
	this->scalingTransformation = glm::mat4x4(glm::vec4(INIT_SCALE, 0, 0, 0), glm::vec4(0, INIT_SCALE, 0, 0), glm::vec4(0, 0, INIT_SCALE, 0), glm::vec4(0, 0, 0, 1));
}

const glm::mat4 Camera::getViewTransformation() {
	return viewTransformation;
}
const glm::mat4 Camera::getperspectiveTransformation()
{
	return this->perspectiveTransformation;
}
const glm::mat4 Camera::getOrthographicTransformation()
{
	return this->orthographicTransformation;
}
const glm::mat4 Camera::getProjection()
{
	return (isOrtho) ? this->orthographicTransformation : this->perspectiveTransformation;
}
void Camera::setCameraViewWorldTransform(glm::vec4 &v)
{
	this->viewWorldTransform = glm::mat4x4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), v); 
}

void Camera::setCameraLookAt()
{
	glm::vec3 z = glm::normalize(this->eye - this->at);
	glm::vec3 x = glm::normalize(glm::cross(glm::vec3(this->up), glm::vec3(z)));
	glm::vec3 y = glm::normalize(glm::cross(z, x));

	glm::vec4 t = glm::vec4(0, 0, 0, 1);
	glm::vec4 x4 = glm::vec4(x, 0);
	glm::vec4 y4 = glm::vec4(y, 0);
	glm::vec4 z4 = glm::vec4(z, 0);

	glm::mat4 c(x4, y4, z4, t);
	glm::mat4 iden(1);
	iden[3] = iden[3] - glm::vec4(this->eye);

	this->viewTransformation = c * iden;
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
void Camera::setOrthographicProjection(const int left,const int right,const int bottom,const int top)
{
	
	glm::vec4 v1 = glm::vec4( (float)2 / 400, 0, 0, 0);
	glm::vec4 v2 = glm::vec4(0, (float)2 / (top - bottom), 0, 0);
	glm::vec4 v3 = glm::vec4(0, 0, (float)2 / (zNear - zFar), 0);
	glm::vec4 v4 = glm::vec4(-(float)(right + left) / (right - left), -(float)(top + bottom) /(top - bottom), -(float)(zFar + zNear) / (zFar - zNear), 1);

	//this->orthographicTransformation = glm::mat4(v1, v2, v3, v4);
	this->orthographicTransformation = glm::ortho<int>(left, right, bottom, top);
}

void Camera::setPerspectiveProjection(float &fovy, float &aspectRatio, int &near, int &far)
{
	float nearHeight = 2.0f * near * tan(0.5f * fovy * PI / 180.f);
	float nearWidth = aspectRatio * nearHeight;
	float t = 0.5f * nearHeight;
	float b = -0.5f * nearHeight;
	float l = -0.5f * nearWidth;
	float r = 0.5f * nearWidth;
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

	this->perspectiveTransformation = glm::perspective<float>((float)fovy*PI / 180.f, aspectRatio, near, far);
	//this->perspectiveTransformation = glm::mat4(v1, v2, v3, v4);
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
void Camera::updateProjection()
{
	if (isOrtho)
		setOrthographicProjection(left, right, bottom, top);
	else
		setPerspectiveProjection(FOV, aspectRatio, zNear,zFar);
}

