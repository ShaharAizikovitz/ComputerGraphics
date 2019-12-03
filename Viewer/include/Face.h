#pragma once
#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Face
{
private:
	std::vector<int> vertexIndices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;
	glm::vec3 centeroid, normal; 

public:
	Face(std::istream& issLine);
	Face(std::vector<int> vertexIndices1);
	virtual ~Face();

	//getters
	const int Face::getVertexIndex(int index);
	const int Face::getNormalIndex(int index);
	const int Face::getTextureIndex(int index);
	const std::vector<int> Face::GetVertices();
	const glm::vec3 getCenter() const { return this->centeroid; }
	const glm::vec3 getNormal() const { return this->normal; }
	//setters
	void setCenter(const glm::vec3 &v) { this->centeroid = v; }
	void setNormal(const glm::vec3 &n) { this->normal = n; }
};