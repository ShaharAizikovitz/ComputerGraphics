#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <memory>
#include "Face.h"
#include "Vertex.h"
#define PI 3.14159265358 / 180

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
	glm::mat4 translationTransform, worldTranslation;

	glm::mat4 worldRotation;
	glm::vec3 wRotation;
	glm::vec3 lRotation;
	glm::mat4x4 worldTransform;
	glm::vec4 color;
	glm::vec3 centerPoint;
	std::string modelName;
	bool draw;
	bool drawCube;
	void createCube();
	void createNormals();
	void createCenterLines();
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
	virtual ~MeshModel();
	MeshModel();

	void addVertexNormal(glm::vec3 &n) { this->v_normals.push_back(n); }
	void SetWorldTransformation(const glm::mat4& worldTransform);
	const glm::mat4& GetWorldTransformation() const;
	const glm::mat4& GetLocalTransform() const;
	const glm::mat4& GetScaleTransform() const;
	const glm::mat4& GetTranslationTransform() const;
	const glm::mat4& GetRotationTransform() const;
	const glm::mat4& GetWorldTranslate() const;
	const glm::mat4& GetWorldRotation() const;
	const glm::vec4& GetColor() const;
	

	//getters-setters
	void SetColor(const glm::vec4& color);
	void setDraw(const bool b) { this->draw = b; }
	void setScaleTransform(const glm::vec3 scale, bool isLocal);
	void setRotationTransform(const glm::vec3 angle,bool isLocal);
	void setTranslationTransform(const glm::vec3 translation, bool isLocal);
	void setWorldTranslation(const glm::vec3 translation);
	void setWorldRotation(const glm::vec3 angle);
	void setCube(const Cube c) { this->cube = c; }
	void setDrawCube(const bool b) { this->drawCube = b; }
	void setCenteLines(const std::vector<glm::vec4> c) { this->centerLine = c; }
	void setIsCurrentModel(const bool& b) { this->isCurrentModel = b; }
	void setModelAIntensity(const float &f) { this->modelAIntensity = f; }
	void setModelDIntensity(const float &f) { this->modelDIntensity = f; }
	void setModelSIntensity(const float &f) { this->modelSIntensity = f; }
	void setCentePoint();
	
	

	const bool& getDraw() { return this->draw; }
	const std::string& GetModelName();
	const std::vector<Face>& GetFaces();
	const std::vector<glm::vec3>& GetVertices();
	const std::vector<glm::vec3>& GetNormals();
	const glm::mat4& getTranslationTransform() const;	
	const Cube getCube() const { return this->cube; }
	const bool getDrawCube() { return this->drawCube; }
	const std::vector<glm::vec4> getCenteLines() const { return this->centerLine; }	
	bool getIsCurrentModel() const { return this->isCurrentModel; }
	std::vector<Vertex> getVertexs() const { return this->vertexs; }
	const void setVertexs(const std::vector<Vertex> &v) { this->vertexs = v; } 
	const float getModelAIntensity() const { return this->modelAIntensity; }
	const float getModelDIntensity() const { return this->modelDIntensity; }
	const float getModelSIntensity() const { return this->modelSIntensity; }
	const glm::vec3 getWorldTranslation() const { return glm::vec3(this->worldTranslation[3][0], this->worldTranslation[3][1], this->worldTranslation[3][2]); }
	const std::vector<glm::vec3> getRotation() ;
	const glm::vec3* getScale() const;
	const glm::vec3* getTranslate() const;
	const glm::vec3 getCenter()const {return centerPoint; }
};
