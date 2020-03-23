//
// Created by masy on 12.03.20.
//

#include <cedar/Cedar.h>
#include "cedar/EntityManager.h"

using namespace cedar;

EntityManager::EntityManager()
{
	this->m_entities = std::map<unsigned int, Entity*>();
}

EntityManager::~EntityManager()
{
	for (auto &pair : this->m_entities)
	{
		delete pair.second;
	}
}

bool EntityManager::addEntity(Entity *entity) {
	if (this->m_entities.find(entity->getEntityId()) == this->m_entities.end())
	{
		this->m_entities.insert(std::make_pair(entity->getEntityId(), entity));
		return true;
	}

	return false;
}

Entity *EntityManager::getEntity(const unsigned int entityId) const {
	auto it = this->m_entities.find(entityId);

	if (it != this->m_entities.end())
		return it->second;
	else
		return nullptr;
}

bool EntityManager::removeEntity(Entity *entity) {
	return this->removeEntity(entity->getEntityId());
}

bool EntityManager::removeEntity(const unsigned int entityId) {
	auto it = this->m_entities.find(entityId);

	if (it != this->m_entities.end())
	{
		delete it->second;
		this->m_entities.erase(it);
		return true;
	}

	return false;
}

void EntityManager::update(const unsigned long currentTime, const unsigned long tickCount) {
	for (auto &pair : this->m_entities)
	{
		pair.second->update(currentTime, tickCount);
	}
}

const std::map<unsigned int, Entity*> *EntityManager::getEntities() const {
	return &this->m_entities;
}
