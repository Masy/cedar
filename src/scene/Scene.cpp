//
// Created by masy on 11.03.20.
//

#include "cedar/Scene.h"

using namespace cedar;

Scene::Scene(const cedar::Vector3f &position)
{
	this->m_models = std::vector<Model*>();
	this->m_position = position;
}

void Scene::update(const unsigned long currentTime, const unsigned long tickCount) {

}

void Scene::render(const unsigned long currentTime, const unsigned long tickCount) {
	for (Model *model : this->m_models)
	{
		model->render();
	}
}

Vector3f Scene::getPosition() const {
	return this->m_position;
}

Vector3f *Scene::getPosition(Vector3f *position) const {
	*position = this->m_position;
	return position;
}

void Scene::setPosition(const Vector3f &newPosition) {
	this->m_position = newPosition;
}

bool Scene::addModel(Model *model) {
	auto it = this->m_models.begin();
	while(it != this->m_models.end())
	{
		if ((*it) == model)
			return false;

		it++;
	}

	this->m_models.push_back(model);
	return true;
}

bool Scene::removeModel(Model *model) {
	auto it = this->m_models.begin();
	while(it != this->m_models.end())
	{
		if ((*it) == model)
		{
			this->m_models.erase(it);
			return true;
		}

		it++;
	}
	return false;
}
