#pragma once
#include "Scene.h"
#include "Vertex.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <cmath>
#include "Camera.h"
#include "Light.h"
#include "Edge.h"
#include "Definitions.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Camera.h"


/*
 * Renderer class.
 */
class Renderer
{
private:		//members
	float *colorBuffer;
	float *zBuffer;
	float **viewport;
	int viewportWidth;
	int viewportHeight;
	int viewportX;
	int viewportY;
	float scaleNumber;
	float reflection;
	float diffusive;
	float ambient;
	float ambientIntensity;
	float ambientK;
	float fov;
	bool drawLines;
	bool fillTriangles;
	bool projection; 
	bool hasModel;
	bool tooDrawaCube, toDrawFaceNormals, toDrawLineNormals, toDrawVertexNormals;
	bool isProjPerspective, isProjOrthographic;
	glm::vec3 ambientColor;
	glm::vec3 diffusivePos;
	glm::mat4x4 worldToCameraTransformation;
	glm::mat4x4 proj;		//delete later
	std::shared_ptr<MeshModel> currentModel;
	std::vector< std::shared_ptr<MeshModel>> models;
	std::vector<Light> lights;
	Camera currentCamera;
	Scene scene;
	GLuint glScreenTex;
	GLuint glScreenVtc;

	//class methods
	void putPixel(int i, int j, const glm::vec3 & color);
	void putPixel(int x, int y, const glm::vec3& color, const float &z);
	void createBuffers(int viewportWidth, int viewportHeight);
	float zDepth(glm::vec3, std::vector<Vertex>);
	glm::vec3 baryCentric(std::vector<glm::vec3> &polygon, glm::vec3 &point);
	float Fab(glm::vec3 &a, glm::vec3 &b, glm::vec3 &point);
	void createOpenGLBuffer();
	void initOpenGLRendering();

	//drawing routings
	float CalculateColor(glm::vec3 &n1, glm::vec3 &n2, glm::vec3 &n);
	void DrawLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 color, bool scale);
	void DrawLine1(glm::vec3 p1, glm::vec3 p2, glm::vec3 color, bool scale);
	void DrawLine(Vertex p1, Vertex p2, glm::vec3 color, bool scale);
	void drawCube(); 
	void drawTriangle(std::vector<Vertex>&points, glm::vec3 &color);
	void drawBetween2Edges(std::vector<Vertex> &points, Edge &e1, Edge &e2, const glm::vec3 &color);
	void scanLine(std::vector<Vertex>&, int &e1, int &e2, int &y, const glm::vec3 &color);
	void scanLine1(std::vector<Vertex>&, int &e1, int &e2, int &y, const glm::vec3 &color);
	void fillTriangle2(std::vector<Vertex> points, const glm::vec3 & color);
	void fillTriangle1(std::vector<Vertex> points, const glm::vec3 &color);
	void fillTriangle(std::vector<Vertex> points, const glm::vec3 &color);
	void Barycentric(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c, float &u, float &v, float &w);
	glm::vec3 Barycentric1(glm::vec3 point, glm::vec3 a, glm::vec3 b, glm::vec3 c);
	glm::vec3 Barycentric2(glm::vec3 point, glm::vec3 a, glm::vec3 b, glm::vec3 c);


	std::vector<std::string> ExcludeModels;
	static bool sort_dec_y(const Vertex &x, const Vertex &y) { return x.getPoint().y > y.getPoint().y; }

public:
	Renderer();
	Renderer(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	~Renderer();
	bool isHasModel();
	void setHasModel();
	void render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);	
	void rotateLocalX(float x);
	void rotateLocalY(float y);
	void rotateLocalZ(float z);
	void rotateWorldX(float x);
	void rotateWorldY(float y);
	void rotateWorldZ(float z);
	void translate(float x, float y, float z);
	void addLight(const Light &l) { this->lights.push_back(l); }
	void init();
	
	//getters\setters
	//---------------
	//getters
	const glm::mat4x4 getProj() const { return this->proj; }		//delete later
	const std::vector<std::string> getExcludeModels() const { return this->ExcludeModels; }
	const bool getProjection();
	bool getToDrawaCube() const { return this->tooDrawaCube; }
	bool getToDrawFaceNormals() const { return this->toDrawFaceNormals; }
	const bool getToDrawVertexNormals() { return this->toDrawVertexNormals; }
	const int& getViewPortWidth() const { return this->viewportWidth; }
	const int& getViewPortHeight() const { return this->viewportHeight; }
	const bool & getFillTriangles() const { return this->fillTriangles; }
	const std::vector<Light> getLights() const { return this->lights; }
	const bool& getdrawLines() const { return this->drawLines; }
	std::shared_ptr<MeshModel> getCurrentModel() const { return this->currentModel; }
	std::vector<std::shared_ptr<MeshModel>> getModels() const { return this->models; }

	//setters
	void setProj( float & fovy,  float & aspectRatio,  int & _near,  int & _far); 
	void setdrawLines(const bool &b) { this->drawLines = b; }
	void setFillTriangles(const bool &b) { this->fillTriangles = b; }
	void setToDrawVertexNormals(const bool &b) { this->toDrawVertexNormals = b; }
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	void setExcludeModels(std::vector<std::string> v) { this->ExcludeModels = v; }
	void setScaleNumber(float f);
	void setEyeX(float eyex);
	void setFov(float f);
	void setProjection(bool p);
	void setPerspective(float f, float ar, int n, int fa);
	void setWorldTranslation(float x, float y, float z);
	void setToDrawaCube(const bool b) { this->tooDrawaCube = b; }
	void setToDrawFaceNormals(bool b) { this->toDrawFaceNormals = b; }
	void setCurrentModel(std::shared_ptr<MeshModel> m) { this->currentModel = m; this->currentModel->setIsCurrentModel(true); }
	void setViewPortWidth(const int& w) { this->viewportWidth = w; }
	void setViewPortHeight(const int& h) { this->viewportHeight = h; }
	void setViewPortWidth( int w) { this->viewportWidth = w; }
	void setViewPortHeight( int h) { this->viewportHeight = h; }
	void setAmbientIntensity(const float &c) { this->ambient = this->ambientK  * c; }
	void setAmbientCoefficient(const float &c) { this->ambient = this->ambientIntensity * c; }
	void setAmbientColor(const glm::vec3 &color) { this->ambientColor = color; }
	void setIsProjPerspective(const bool &t) { this->isProjPerspective = t; }
	void setIsProjOrthographic(const bool &t) { this->isProjOrthographic = t; }
	void setReflection(const float &r) { this->reflection = r; }
};
