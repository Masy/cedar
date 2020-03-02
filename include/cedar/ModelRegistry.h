//
// Created by masy on 02.03.20.
//

#ifndef TALESOFCATVENTURE_MODELREGISTRY_H
#define TALESOFCATVENTURE_MODELREGISTRY_H

#include <map>

#include "cedar/Model.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Exception which is thrown when a model could not be loaded.
	 */
	class ModelLoadException : public ModelException
	{
	public:
		/**
		 * Creates a new model load exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ModelLoadException(const std::string &message);
	};

	/**
	 * Class for creating and handling models.
	 */
	class ModelRegistry
	{
	public:
		/**
		 * Loads a model from the given file.
		 *
		 * @param name The unique name of the model.
		 * @param path The path to the file.
		 * @param drawingMode The drawing mode of the model.
		 * @return A pointer to the loaded model.
		 *
		 * @throws ModelLoadException when the model could not be loaded.
		 */
		static Model *loadModel(const std::string &name, const std::string &path, unsigned int drawingMode = CEDAR_TRIANGLES);

		/**
		 * Gets the loaded model with the given name.
		 *
		 * @param name The name of the model.
		 * @return A pointer to the model or <code>nullptr</code> if no model with that name is loaded.
		 */
		static Model *getModel(const std::string &name);

		/**
		 * Deletes all loaded models.
		 */
		static void cleanup();

		/**
		 * Deletes the model with the given name.
		 *
		 * @param name The name of the model that will be deleted.
		 */
		static void cleanup(const std::string &name);
	};
}

#endif //TALESOFCATVENTURE_MODELREGISTRY_H
