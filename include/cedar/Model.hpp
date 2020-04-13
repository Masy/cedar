//
// Created by masy on 02.03.20.
//

#ifndef CEDAR_MODEL_HPP
#define CEDAR_MODEL_HPP

#include "cedar/GLConstants.hpp"
#include "cedar/XException.hpp"

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
	 * Exception which is thrown when a model could not be created.
	 */
	class ModelCreationException : public ModelException
	{
	public:
		/**
		 * Creates a new model creation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ModelCreationException(const std::string &message);
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
	 * Exception which is thrown when a model could not be updated.
	 */
	class ModelUpdateException : public ModelException
	{
	public:
		/**
		 * Creates a new model update exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit ModelUpdateException(const std::string &message);
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
		/**
		 * The number of vertex attributes.
		 */
		unsigned int m_vertexAttribCount;

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
		 * @param vertexAttribCount The number of vertex attribute arrays.
		 *
		 * @throws ModelCreationException if <code>vertexAttribCount</code> is 0 or greater than the number of supported vertex attribute arrays.
		 */
		explicit Model(unsigned int drawingMode = CEDAR_TRIANGLES, unsigned int vertexAttribCount = 1);
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
		 * Updates the vertex buffer of the model.
		 *
		 * @param offset The offset in bytes of where the new data will be uploaded.
		 * @param vertexDataSize The size of the data that will be uploaded in bytes.
		 * @param vertexData A pointer to the data that will be uploaded.
		 *
		 * @throws ModelUpdateException if the model is not initialized yet.
		 */
		void update(unsigned int offset, unsigned int vertexDataSize, const void *vertexData);

		/**
		 * Renders the model if there is vertex data on the graphics card.
		 */
		void render() const;

		/**
		 * Gets the id of the vertex array object on the graphics card.
		 *
		 * @return The id of the vertex array object on the graphics card.
		 */
		[[nodiscard]] unsigned int getVertexArrayId() const;

		/**
		 * Gets the id of the vertex buffer object on the graphics card.
		 *
		 * @return The id of the vertex buffer object on the graphics card.
		 */
		[[nodiscard]] unsigned int getVertexBufferId() const;

		/**
		 * Gets the id of the index buffer object on the graphics card.
		 *
		 * @return The id of the index buffer object on the graphics card.
		 */
		[[nodiscard]] unsigned int getIndexBufferId() const;

		/**
		 * Gets the number of vertex attributes the vertex array object has.
		 *
		 * @return The number of vertex attributes the vertex array object has.
		 */
		[[nodiscard]] unsigned int getVertexAttribCount() const;

		/**
		 * Set the number of vertex attributes the vertex array object has.
		 *
		 * @param newVertexAttribCount The new number of vertex attributes.
		 *
		 * @throws ModelUpdateException if <code>newVertexAttribCount</code> is 0;
		 */
		void setVertexAttribCount(unsigned int newVertexAttribCount);

		/**
		 * Checks if the model is equal to the other model.
		 *
		 * @param rhs The other model.
		 * @return <code>true</code> if the {@link #m_vaoId vertex array object ids} are the same.
		 */
		bool operator==(const Model &rhs);
	};
}

#endif //CEDAR_MODEL_HPP
