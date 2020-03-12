//
// Created by masy on 12.03.20.
//

#ifndef CEDAR_ENTITYMANAGER_H
#define CEDAR_ENTITYMANAGER_H

#include <map>

#include "cedar/Entity.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class for managing entities.
	 */
	class EntityManager
	{
	private:
		/**
		 * The map storing all entities of the manager.
		 */
		std::map<unsigned int, Entity *> m_entities;

	public:
		/**
		 * Creates a new entity manager.
		 */
		EntityManager();

		/**
		 * Deletes the entity manager.
		 */
		~EntityManager();

		/**
		 * Adds the given entity to the entity manager.
		 *
		 * @param entity A pointer to the entity that will be added.
		 * @return <code>true</code> if the entity was successfully added.
		 */
		bool addEntity(Entity *entity);

		/**
		 * Gets the entity with the given id.
		 *
		 * @param entityId The id of the entity that will be gotten.
		 * @return A pointer to the entity with the given id or <code>nullptr</code> if there is no entity with that id in this entity manager.
		 */
		[[nodiscard]] Entity *getEntity(unsigned int entityId) const;

		/**
		 * Removes the given entity from the entity manager.
		 *
		 * @param entity A pointer to the entity what will be removed.
		 * @return <code>true</code> if the entity was successfully removed.
		 */
		bool removeEntity(Entity *entity);

		/**
		 * Removes the entity with the given id from the entity manager.
		 *
		 * @param entityId The id of the entity that will be removed.
		 * @return <code>true</code> if the entity was successfully removed.
		 */
		bool removeEntity(unsigned int entityId);

		/**
		 * Updates all entities of the entity manager.
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick count.
		 */
		void update(unsigned long currentTime, unsigned long tickCount);
	};
}

#endif //CEDAR_ENTITYMANAGER_H
