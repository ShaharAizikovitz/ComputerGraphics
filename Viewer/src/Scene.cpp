#include "Scene.h"
#include "MeshModel.h"
#include "Utils.h"
#include <string>

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{
	Utils::createGrid();
	AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel("../Data/obj_examples/grid.obj")));
}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	int i = GetActiveModelIndex();
	if (models.size()) {
		models[i]->SetColor({ 0,0,0,0 });
	}
	//last model to enter is the current one
	this->currentModel = model;
	models.push_back(model);
	activeModelIndex = models.size() - 1;
	models[activeModelIndex]->SetColor({ 1,1,0,0 });

}

const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::addCamera(const Camera& camera)
{
	cameras.push_back(camera);
	this->currentCamera = camera;
	this->currentCamera.setCameraNum(cameras.size() - 1);
	for each (Camera c in cameras)
		c.setCurrent(false);

	this->currentCamera.setCurrent(true);
}

const int Scene::GetCameraCount() const
{
	return cameras.size();
}

void Scene::SetActiveCameraIndex(size_t index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

void Scene::SetActiveModelIndex(size_t index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		int i = GetActiveModelIndex();
		models[i]->SetColor({ 0,0,0,0 });
		activeModelIndex = index;
		models[index]->SetColor({ 1,1,0,0 });
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}
const std::shared_ptr<MeshModel> Scene::getActiveModel() const
{
	return models.at(activeModelIndex);
}
const std::vector<std::shared_ptr<MeshModel>> Scene::getModels() const{
	return this->models;
}

const std::vector<Camera> Scene::getCameras() const {
	return this->cameras;
}