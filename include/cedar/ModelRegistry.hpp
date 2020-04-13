//
// Created by masy on 02.03.20.
//

#ifndef CEDAR_MODELREGISTRY_HPP
#define CEDAR_MODELREGISTRY_HPP

#include <map>

#include "cedar/Model.hpp"

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
		static bool registerModel(const std::string &name, Model* model);
		/**
		 * Loads a model from the given file.
		 *
		 * @param name The unique name of the model.
		 * @param path The path to the file.
		 * @param drawingMode The drawing mode of the model.
		 * @param bitMask A pointer to an unsigned char where the bit mask of the bmf model will be stored.
		 * @return A pointer to the loaded model.
		 *
		 * @throws ModelLoadException when the model could not be loaded.
		 */
		static Model *loadBMFModel(const std::string &name, const std::string &path, unsigned char *bitMask);

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

#endif //CEDAR_MODELREGISTRY_HPP
