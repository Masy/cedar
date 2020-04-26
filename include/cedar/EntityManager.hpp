//
// Created by masy on 12.03.20.
//

#ifndef CEDAR_ENTITYMANAGER_HPP
#define CEDAR_ENTITYMANAGER_HPP

#include <map>
#include <memory>

#include "cedar/Entity.hpp"

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
		std::map<unsigned int, std::shared_ptr<Entity>> m_entities;

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
		[[nodiscard]] std::shared_ptr<Entity> getEntity(unsigned int entityId) const;

		/**
		 * Removes the given entity from the entity manager.
		 *
		 * @param entity A shared pointer to the entity what will be removed.
		 * @return <code>true</code> if the entity was successfully removed.
		 */
		bool removeEntity(const std::shared_ptr<Entity> &entity);

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

		/**
		 * Gets the entities the entity manager manages.
		 *
		 * @return The entities of the entity manager.
		 */
		[[nodiscard]] const std::map<unsigned int, std::shared_ptr<Entity>> *getEntities() const;

		/**
		 * Clears the entity map.
		 */
		void cleanup();
	};
}

#endif //CEDAR_ENTITYMANAGER_HPP
