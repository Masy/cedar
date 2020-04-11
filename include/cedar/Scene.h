//
// Created by masy on 11.03.20.
//

#ifndef CEDAR_SCENE_H
#define CEDAR_SCENE_H

#include <vector>

#include "cedar/Model.h"
#include "cedar/Vector3f.h"
#include "cedar/EntityManager.h"
#include "cedar/ShaderProgram.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Class representing a scene.
	 *
	 * <p>A scene has a position that determines the translation of the models that are stored inside the scene.</p>
	 */
	class Scene
	{
	protected:
		/**
		 * A pointer to the entity manager of the scene.
		 */
		 EntityManager *m_entityManager;
		/**
		 * A list of models that are in the scene.
		 */
		std::vector<Model*> m_models;
		/**
		 * The position of the scene.
		 */
		Vector3f m_position;

	public:
		/**
		 * Creates a new scene.
		 *
		 * @param position The position of the scene.
		 */
		explicit Scene(const Vector3f &position);

		/**
		 * Destroys the scene.
		 */
		virtual ~Scene();

		/**
		 * Updates the scene.
		 *
		 * <p>This method is called 20 times per second from the engine thread.</p>
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick count.
		 */
		virtual void update(unsigned long currentTime, unsigned long tickCount);

		/**
		 * Renders all models inside the scene.
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick count.
		 * @param shader A pointer to the shader that is currently bound.
		 */
		virtual void render(unsigned long currentTime, unsigned long tickCount, const ShaderProgram *shader);

		/**
		 * Gets the position of the scene.
		 *
		 * @return The position of the scene.
		 */
		[[nodiscard]] Vector3f getPosition() const;

		/**
		 * Gets the position of the scene.
		 *
		 * @param position A pointer to a vector where the position will be stored.
		 * @return The pointer to <code>position</code>.
		 */
		[[nodiscard]] Vector3f *getPosition(Vector3f *position) const;

		/**
		 * Sets the position of the scene.
		 *
		 * @param newPosition The new position of the scene.
		 */
		void setPosition(const Vector3f &newPosition);

		/**
		 * Adds a model to the scene.
		 *
		 * @param model A pointer to the model that will be added.
		 * @return <code>true</code> if the model was successfully added.
		 */
		virtual bool addModel(Model *model);

		/**
		 * Removes a model from the scene.
		 *
		 * @param model A pointer to the model tha will be removed.
		 * @return <code>true</code> if the model was successfully removed.
		 */
		virtual bool removeModel(Model *model);

		/**
		 * Gets the entity manager of the scene.
		 *
		 * @return A pointer to the entity manager of the scene.
		 */
		[[nodiscard]] EntityManager *getEntityManager() const;
	};
}

#endif //CEDAR_SCENE_H
