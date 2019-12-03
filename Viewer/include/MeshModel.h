#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <memory>
#include "Face.h"
#include "Vertex.h"

typedef struct Cube {
	float front, back, right, left, top, bottom;
	glm::vec4 cPoints[8];  
	glm::vec4 color; 
}Cube;

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<Vertex> vertexs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> v_normals;
	std::vector<glm::vec4> centerLine; 

	glm::mat4 localTransform;
	glm::mat4 scaleTransform;
	glm::mat4 rotationTransform;
	glm::mat4 translationTransform, worldTranslation, xRotationWorld, yRotationWorld, zRotationWorld;

	glm::mat4 worldRotation;
	glm::mat4 xRotation;
	glm::mat4 yRotation;
	glm::mat4 zRotation;
	glm::mat4x4 worldTransform;
	glm::vec4 color;
	glm::vec4 center;

	glm::vec4 cg;
	glm::vec4 translate;

	std::string modelName;
	bool draw;
	bool drawCube;
	void createCube();
	void createNormals();
	void createCenterLines();
	void calculateCenter();

	void createCenteroGravity();
	bool isCurrentModel;
	float modelAIntensity;
	float modelDIntensity;
	float modelSIntensity;
	Cube cube; 

public:
	//ctor
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	MeshModel(const std::vector<Face>& faces, const std::vector<Vertex>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName);
	MeshModel(const std::vector<Face>& faces, const std::vector<Vertex>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName, const bool &isCurrent);
	MeshModel(const int type);
	MeshModel() {}
	virtual ~MeshModel();
	

	void addVertexNormal(glm::vec3 &n) { this->v_normals.push_back(n); }

	//getters-setters
	void setDraw(const bool b) { this->draw = b; }
	void setScaleTransform(float xFactor, float yFactor, float zFactor);
	void setRotationTransform(float xDegree, float yDegree, float zDegree);
	void setTranslationTransform(float x, float y, float z);
	void setWorldTranslation(float x, float y, float z);
	void setWorldRotation(float xDegree, float yDegree, float zDegree);
	void setCube(const Cube c) { this->cube = c; }
	void setDrawCube(const bool b) { this->drawCube = b; }
	void setCenteLines(const std::vector<glm::vec4> c) { this->centerLine = c; }
	void setIsCurrentModel(const bool& b) { this->isCurrentModel = b; }
	void setModelAIntensity(const float &f) { this->modelAIntensity = f; }
	void setModelDIntensity(const float &f) { this->modelDIntensity = f; }
	void setModelSIntensity(const float &f) { this->modelSIntensity = f; }
	void setWorldTransformation(const glm::mat4& worldTransform) { this->worldTransform = worldTransform; }
	void setColor(const glm::vec4& color) { this->color = color; }



	const bool& getDraw() { return this->draw; }
	const Cube getCube() const { return this->cube; }
	const bool getDrawCube() { return this->drawCube; }
	const std::vector<glm::vec4> getCenteLines() const { return this->centerLine; }	
	bool getIsCurrentModel() const { return this->isCurrentModel; }
	std::vector<Vertex> getVertexs() const { return this->vertexs; }
	const void setVertexs(const std::vector<Vertex> &v) { this->vertexs = v; } 
	const float getModelAIntensity() const { return this->modelAIntensity; }
	const float getModelDIntensity() const { return this->modelDIntensity; }
	const float getModelSIntensity() const { return this->modelSIntensity; }

	const glm::mat4& getScaleTransform() const { return this->scaleTransform; }
	const glm::mat4& getWorldTransformation() const { return this->worldTransform; }
	const glm::mat4& getLocalTransform() const { return this->localTransform; }
	const glm::vec4& getColor() const { return this->color; }
	const std::string& getModelName() { return this->modelName; }
	const std::vector<Face>& getFaces() { return this->faces; }
	const std::vector<glm::vec3>& getVertices() { return this->vertices; }
	const std::vector<glm::vec3>& getNormals() { return this->normals; }
	const glm::mat4& getRotationTransform() const { return this->rotationTransform; }
	const glm::mat4& getTranslationTransform() const { return this->translationTransform; }
	const glm::mat4& getWorldTranslate() const { return this->worldTranslation; }
	const glm::mat4& getWorldRotation() const { return this->worldRotation; }

	const glm::vec4& getCenterOGravity() const { return this->cg; }

};
