#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



//augmented ctor
MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<Vertex>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	localTransform(glm::mat4(1)),
	worldTransform(glm::mat4(1)),
	worldTranslation(glm::mat4(1)),
	worldRotation(glm::mat4(1)),
	scaleTransform(glm::mat4(1500)),
	rotationTransform(glm::mat4(1)),
	translationTransform(glm::mat4(1)),
	faces(faces),
	vertexs(vertices),
	normals(normals),
	wRotation( 0.0, 0.0, 0.0 ),
	lRotation( 0.0, 0.0, 0.0 )
{
	this->drawCube = false;
	this->isCurrentModel = false;
	this->createCube();
	this->createCenterLines();
	this->setCentePoint();
	setScaleTransform(glm::vec3(1500, 1500, 1500));
}
// ctor being used right now 12.11.2019
MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<Vertex>& vertices, const std::vector<glm::vec3>& normals, const std::string & modelName, const bool & isCurrent) : 
	modelName(modelName),
	localTransform(glm::mat4(1)),
	worldTransform(glm::mat4(1)),
	worldTranslation(glm::mat4(1)),
	worldRotation(glm::mat4(1)),
	scaleTransform(glm::mat4(1500)),
	rotationTransform(glm::mat4(1)),
	translationTransform(glm::mat4(1)),
	faces(faces),
	vertexs(vertices),
	normals(normals),
	isCurrentModel(isCurrent),
	wRotation(0.0, 0.0, 0.0),
	lRotation(0.0, 0.0, 0.0)
{
	this->modelAIntensity = 0.2f;
	this->modelDIntensity = 0.2f;
	this->modelSIntensity = 0.2f;
	this->drawCube = false;
	this->isCurrentModel = false;
	this->createCube();
	this->createCenterLines();
	this->setCentePoint();
	setScaleTransform(glm::vec3(1500, 1500, 1500));
}
//ctor
MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	localTransform(glm::mat4(1)),
	worldTransform(glm::mat4(1)),
	worldTranslation(glm::mat4(1)),
	worldRotation(glm::mat4(1)),
	scaleTransform(glm::mat4(1500)),
	rotationTransform(glm::mat4(1)),
	translationTransform(glm::mat4(1)),
	faces(faces),
	vertices(vertices),
	normals(normals),
	wRotation(0.0, 0.0, 0.0),
	lRotation(0.0, 0.0, 0.0)
{
	this->drawCube = false;
	this->isCurrentModel = false;
	this->createCube();
	this->createCenterLines();
	this->setCentePoint();
	setScaleTransform(glm::vec3(500, 500, 500));
}

// constractor for primitives 
MeshModel::MeshModel(const int type)
{
	this->localTransform = glm::mat4(1);
	this->worldTransform=glm::mat4(1);
	this->worldTranslation=glm::mat4(1);
	this->worldRotation=glm::mat4(1);
	this->scaleTransform=glm::mat4(1);
	this->rotationTransform=glm::mat4();
	this->translationTransform=glm::mat4(1);
	this->drawCube = false;
	this->isCurrentModel = false;
	this->modelAIntensity = 0.2f;
	this->modelDIntensity = 0.2f;
	this->modelSIntensity = 0.2f;
	setScaleTransform(glm::vec3(500, 500, 500));
	this->wRotation = { 0.0, 0.0, 0.0 };
	this->lRotation = { 0.0, 0.0, 0.0 };
	switch (type)
	{
	case 0: {
		this->modelName = "poligon.obj";
		glm::vec3 v0 = { 123.0f,122.0f,-30.0f };
		glm::vec3 v1 = { 61.0f,0.0f,-5.0f };
		glm::vec3 v2 = { 1.0f,122.0f,-10.0f };
		this->vertices.push_back(v0);
		this->vertices.push_back(v1);
		this->vertices.push_back(v2);
		glm::vec3 color(0, 0, 0);
		this->vertexs.push_back(Vertex(v0, color, INT32_MAX));
		this->vertexs.push_back(Vertex(v1, color, INT32_MAX));
		this->vertexs.push_back(Vertex(v2, color, INT32_MAX));
		Face f = Face({ 1, 2, 3 });
		this->faces.push_back(f);
	}
	default:
		break;
	}
	this->setCentePoint();
	this->createCube();
	this->createCenterLines();
	setScaleTransform(glm::vec3(500, 500, 500));
}


MeshModel::~MeshModel()
{

}

void MeshModel::createCenterLines()
{
	for (std::vector<Face>::iterator f = this->faces.begin(); f != this->faces.end(); f++)
	{ 
		glm::vec3 point1 = this->vertexs.at((*f).getVertexIndex(0) - 1).getPoint(); 
		glm::vec3 point2 = this->vertexs.at((*f).getVertexIndex(1) - 1).getPoint();
		glm::vec3 point3 = this->vertexs.at((*f).getVertexIndex(2) - 1).getPoint();
		glm::vec3 center = glm::vec3((point1.x + point2.x + point3.x)/3, (point1.y + point2.y + point3.y)/3, (point1.z + point2.z + point3.z)/3); 
			
		f->setCenter(center);
	}
}

void MeshModel::createCube()
{
	std::cout << "cube created" << std::endl;
	this->cube.back = this->cube.front = this->cube.right = this->cube.left = this->cube.top = this->cube.bottom = 0; 
	this->cube.color = glm::vec4(1, 0, 0, 1); 

	//find minimums and maximums of the cube faces
	for (std::vector<Vertex>::iterator it = this->vertexs.begin(); it != this->vertexs.end(); it++)
	{
		if (this->cube.back >= (*it).getPoint().z)  this->cube.back = (*it).getPoint().z;
		if (this->cube.front < (*it).getPoint().z)  this->cube.front = (*it).getPoint().z;

		if (this->cube.right <= (*it).getPoint().x) this->cube.right = (*it).getPoint().x;
		if (this->cube.left > (*it).getPoint().x) this->cube.left = (*it).getPoint().x;

		if (this->cube.bottom >= (*it).getPoint().y) this->cube.bottom = (*it).getPoint().y;
		if (this->cube.top < (*it).getPoint().y) this->cube.top = (*it).getPoint().y;
	}

	//calculate the cube corners verices
	this->cube.cPoints[0] = glm::vec4(this->getCube().left, this->getCube().bottom, this->getCube().front, 1);
	this->cube.cPoints[1] = glm::vec4(this->getCube().right, this->getCube().bottom, this->getCube().front, 1);
	this->cube.cPoints[2] = glm::vec4(this->getCube().left, this->getCube().top, this->getCube().front, 1);
	this->cube.cPoints[3] = glm::vec4(this->getCube().right, this->getCube().top, this->getCube().front, 1);
	this->cube.cPoints[4] = glm::vec4(this->getCube().left, this->getCube().bottom, this->getCube().back, 1);
	this->cube.cPoints[5] = glm::vec4(this->getCube().right, this->getCube().bottom, this->getCube().back, 1);
	this->cube.cPoints[6] = glm::vec4(this->getCube().left, this->getCube().top, this->getCube().back, 1);
	this->cube.cPoints[7] = glm::vec4(this->getCube().right, this->getCube().top, this->getCube().back, 1);
	
}

void MeshModel::createNormals()
{
	glm::vec3 lines[2];
	for (std::vector<glm::vec3>::iterator it = this->vertices.begin(); it != this->normals.end(); it++)
	{

	}
}

void MeshModel::SetWorldTransformation(const glm::mat4& worldTransform)
{
	this->worldTransform = worldTransform;
}

const glm::mat4& MeshModel::getTranslationTransform() const {
	return this->translationTransform;
}


const std::vector<glm::vec3> MeshModel::getRotation()
{
	std::vector<glm::vec3> r;
	r.push_back(wRotation);
	r.push_back(lRotation);
	return r;
}

const glm::vec3 * MeshModel::getScale() const
{
	return nullptr;
}

const glm::vec3 * MeshModel::getTranslate() const
{
	return nullptr;
}


const glm::mat4& MeshModel::GetWorldTransformation() const
{
	return worldTransform;
}

const glm::mat4& MeshModel::GetLocalTransform() const
{
	return this->localTransform;
}
void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}

const glm::vec4& MeshModel::GetColor() const
{
	return color;
}

void MeshModel::setCentePoint()
{
	float x = 0;
	float y = 0;
	float z = 0;
	size_t size = vertexs.size();
	std::vector<Vertex>::iterator it = vertexs.begin();
	for (;it != vertexs.end(); it++)
	{
		x += (*it).getPoint().x;
		y += (*it).getPoint().y;
		z += (*it).getPoint().z;
	}

	this->centerPoint = glm::vec3((x / size), (y / size), (z / size));
}




const std::string& MeshModel::GetModelName()
{
	return modelName;
}

const std::vector<Face>& MeshModel::GetFaces() {
	return this->faces;
}

const std::vector<glm::vec3>& MeshModel::GetVertices() {
	return this->vertices;
}

const std::vector<glm::vec3>& MeshModel::GetNormals() {
	return this->normals;
}

const glm::mat4& MeshModel::GetRotationTransform() const {
	return this->rotationTransform;
}
const glm::mat4& MeshModel::GetTranslationTransform() const {
	return this->translationTransform;
}

const glm::mat4& MeshModel::GetWorldTranslate() const {
	return this->worldTranslation;
}
const glm::mat4& MeshModel::GetWorldRotation() const {
	return this->worldRotation;
}

void MeshModel::setScaleTransform(const glm::vec3 scale) {
	
	scaleTransform = Utils::scaleMat(scale);
	
}
void MeshModel::setTranslationTransform(const glm::vec3 translation, bool isLocal) {
	/*if (isLocal)
		this->localTransform = Utils::TranslationMatrix(translation);
	else
		this->worldTransform = Utils::TranslationMatrix(translation);*/
	glm::vec4 xVec = translationTransform[0];
	glm::vec4 yVec = translationTransform[1];
	glm::vec4 zVec = translationTransform[2];
	glm::vec4 lVec(translation.x, translation.y, translation.z, 1);
	if (isLocal)
		this->localTransform = glm::mat4(xVec, yVec, zVec, lVec);
	else
		this->worldTransform = glm::mat4(xVec, yVec, zVec, lVec);
}

void MeshModel::setWorldTranslation(const glm::vec3 translation) {
	
	worldTranslation = Utils::TranslationMatrix(translation);
	
}

void MeshModel::setRotationTransform(const glm::vec3 angle, bool isLocal) {
	
	glm::mat4 x = glm::mat4(1, 0, 0, 0, 0, cosf(angle.x), -sinf(angle.x), 0, 0, sinf(angle.x), cosf(angle.x), 0, 0, 0, 0, 1);
	glm::mat4 y = glm::mat4(cosf(angle.y), 0, sinf(angle.y), 0, 0, 1, 0, 0, -sinf(angle.y), 0, cosf(angle.y), 0, 0, 0, 0, 1);
	glm::mat4 z = glm::mat4(cosf(angle.z), -sinf(angle.z), 0, 0, sinf(angle.z), cosf(angle.z), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	if (isLocal)
	//	localTransform = (x * y * z);
		this->localTransform = Utils::TranslationMatrix(-centerPoint)*(x * y * z)*Utils::TranslationMatrix(centerPoint);
	else
		this->worldTransform = (x * y * z);


		
}

void MeshModel::setWorldRotation(const glm::vec3 angle) {
	
		this->worldRotation = Utils::rotateMat(angle);
		
	
}
const glm::mat4& MeshModel::GetScaleTransform() const {
	return this->scaleTransform;
}
MeshModel::MeshModel() {
}
