//
// Created by masy on 02.03.20.
//

#ifndef TALESOFCATVENTURE_MODEL_H
#define TALESOFCATVENTURE_MODEL_H

#include "cedar/GLConstants.h"
#include "cedar/XException.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Base class for all model related exceptions.
	 */
	class ModelException : public XException
	{
	public:
		/**
		 * Creates a new model exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ModelException(const std::string &message);
	};

	/**
	 * Exception which is thrown when a model could not be uploaded.
	 */
	class ModelUploadException : public ModelException
	{
	public:
		/**
		 * Creates a new model upload exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ModelUploadException(const std::string &message);
	};

	/**
	 * Class representing a graphic model.
	 */
	class Model
	{
	protected:
		/**
		 * The id of the vertex array object on the graphics card.
		 */
		unsigned int m_vaoId;
		/**
		 * The id of the vertex buffer object on the graphics card that stores the indices of the model.
		 */
		unsigned int m_indexVboId;
		/**
		 * The id of the vertex buffer object on the graphics card that stores the vertices of the model.
		 */
		unsigned int m_vertexVboId;
		/**
		 * The drawing mode of the model.
		 */
		unsigned int m_drawingMode;
		/**
		 * The number of indices the model is rendered with.
		 */
		unsigned int m_indexCount;
		/**
		 * The data type of the indices.
		 *
		 * <p>Has to be one of the following data types:
		 */
		unsigned int m_indexType;

	public:
		/**
		 * Creates a new model.
		 *
		 * <p>The <code>drawing mode</code> has to be one of the following:
		 * <ul>
		 *   <li>{@link CEDAR_POINTS}</li>
		 *   <li>{@link CEDAR_LINES}</li>
		 *   <li>{@link CEDAR_LINE_LOOP}</li>
		 *   <li>{@link CEDAR_LINE_STRIP}</li>
		 *   <li>{@link CEDAR_TRIANGLES}</li>
		 *   <li>{@link CEDAR_TRIANGLE_STRIP}</li>
		 *   <li>{@link CEDAR_TRIANGLE_FAN}</li>
		 *   <li>{@link CEDAR_LINES_ADJACENCY}</li>
		 *   <li>{@link CEDAR_LINE_STRIP_ADJACENCY}</li>
		 *   <li>{@link CEDAR_TRIANGLES_ADJACENCY}</li>
		 *   <li>{@link CEDAR_TRIANGLE_STRIP_ADJACENCY}</li>
		 *   <li>{@link CEDAR_PATCHES}</li>
		 * </ul></p>
		 *
		 * @param drawingMode The drawing mode of the model.
		 */
		explicit Model(unsigned int drawingMode = CEDAR_TRIANGLES);
		/**
		 * Destroys the model.
		 *
		 * <p>If data has been uploaded, the vertex array and buffer objects of the model are deleted from the graphics card as well.</p>
		 */
		~Model();

		/**
		 * Uploads the given data to the graphics card.
		 *
		 * <p>The <code>index type</code> has to be one of the following:
		 * <ul>
		 *   <li>{@link CEDAR_UNSIGNED_BYTE}</li>
		 *   <li>{@link CEDAR_UNSIGNED_SHORT}</li>
		 *   <li>{@link CEDAR_UNSIGNED_INT}</li>
		 * </ul></p>
		 *
		 * @param vertexDataSize The size of the vertex data array in bytes.
		 * @param vertexData The vertex data of the model.
		 * @param indexDataSize The size of the index data array in bytes.
		 * @param indexData The indices of the model.
		 * @param indexType The data type of the indices.
		 *
		 * @throws ModelUploadException if <code>indexType</code> is an unsupported type.
		 */
		void upload(unsigned int vertexDataSize, const void *vertexData, unsigned int indexDataSize, const void *indexData,
					unsigned int indexType = CEDAR_UNSIGNED_INT);

		/**
		 * Renders the model if there is vertex data on the graphics card.
		 */
		void render() const;
	};
}

#endif //TALESOFCATVENTURE_MODEL_H
