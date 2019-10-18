#include "Light.h"

Light::Light()
{
}

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
	glm::vec3 areaPoint;
	for (int d = 0; d < s; d++)
	{
		for (float t = 0.0f; t < 360.0f; t = t + 1.0f)
		{
			areaPoint = glm::vec3(d * cos(t * PI / 180), d * sin(t * PI / 180), 1.0f);
			this->lightArea.push_back(areaPoint);
		}
	}
	this->diameter = s; 
}
