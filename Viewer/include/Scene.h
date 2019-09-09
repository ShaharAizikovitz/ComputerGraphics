#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"
#include "Light.h"

/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
private:
	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<Light> Lights;
	std::vector<Camera> cameras;

	int activeCameraIndex;
	int activeModelIndex;
	int width, height;

public:
	Scene();
	~Scene(){}
	void AddModel(const std::shared_ptr<MeshModel>& model);
	void addLight(const Light &l) { this->Lights.push_back(l); }
	void AddCamera(const Camera& camera);
	
	//setters
	void SetActiveCameraIndex(int index);
	void SetActiveModelIndex(int index);

	//getters
	const int getHeight() const { return this->height; }
	const int getWidth() const { return this->width; }
	const int GetModelCount() const;
	const int GetCameraCount() const;
	const int GetActiveCameraIndex() const;
	const int GetActiveModelIndex() const;
	const std::vector<std::shared_ptr<MeshModel>> getModels() const;
	const std::vector<Camera> getCameras() const;
	const std::vector<Light> getLights() const { return this->Lights; }
};
