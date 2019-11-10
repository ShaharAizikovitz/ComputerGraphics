#include "Light.h"

//cotr
Light::Light()
{
	this->direction = glm::vec3(0, 0, 0);
	//pos - direction
	this->normal = glm::normalize(glm::vec3(0, 0, -400) - this->direction);
}

//dtor
Light::~Light()
{
}

float Light::TotalLight() const
{
	return this->DifusiveIntensity + this->AmbientIntensity + this->SpecularIntensity;
}

float Light::Difusive(const float & Kd, const float & Ld, glm::vec3 &l, glm::vec3 &n) 
{
	return DifusiveIntensity = Kd * glm::dot(l, n) * Ld;
}

float Light::Specular(const float & Ks, const float & r, const float & v, const int & alpha, const float & Ls) 
{
	return SpecularIntensity = Ks * pow(glm::dot(r,v), alpha) * Ls;
}

void Light::setDiameter(const int &s)
{
	int ss = s;
	glm::vec3 areaPoint;
	glm::vec3 loc = glm::vec3(this->pos.x-s/2, this->pos.y+s/2, this->pos.z);

	//# DEBUG, set a square of length s/2 around the position of the light
	for (size_t i = 0; i < s; i++)
		for (size_t j = 0; j < s; j++)
			areaPoint = glm::vec3(loc.x + j, loc.y - i, loc.z);



	//for (int d = 1; d <= (int)(s/2); d++)
	//{
	//	//areaPoint = glm::vec3(d * cos(s * PI / 180), d * sin(s * PI / 180), 1.0f);
	//	//this->lightArea.push_back(areaPoint);
	//	for (float t = 0.0f; t < 360.0f; t = t + 1.0f)
	//	{
	//		areaPoint = glm::vec3(d * cos(t * PI / 180), d * sin(t * PI / 180), 1.0f);
	//		this->lightArea.push_back(areaPoint);
	//	}
	//}
	this->diameter = s; 
}
