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
	std::shared_ptr<MeshModel> currentModel;
	std::vector<Light> Lights;
	std::vector<Camera> cameras;
	Camera currentCamera;

	int activeCameraIndex;
	int activeModelIndex;
	int width, height;

public:
	Scene();
	~Scene(){}
	void AddModel(const std::shared_ptr<MeshModel>& model);
	void addLight(const Light l) { this->Lights.push_back(l); }
	void addCamera(const Camera& camera);
	
	//setters
	void SetActiveCameraIndex(size_t index);
	void SetActiveModelIndex(size_t index);

	//getters
	const std::shared_ptr<MeshModel> getCurrentModel() const { return this->currentModel; }
	const int getHeight() const { return this->height; }
	const int getWidth() const { return this->width; }
	const int GetModelCount() const;
	const int GetCameraCount() const;
	const int GetActiveCameraIndex() const;
	const int GetActiveModelIndex() const;
	const std::vector<std::shared_ptr<MeshModel>> getModels() const;
	const std::vector<Camera> getCameras() const;
	 std::vector<Light> getLights() const { return this->Lights; }
	const Camera getCurrentCamera() const { return this->currentCamera; }
};
