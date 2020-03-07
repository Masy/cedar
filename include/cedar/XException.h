//
// Created by masy on 27.01.20.
//

#ifndef CEDAR_XEXCEPTION_H
#define CEDAR_XEXCEPTION_H

#include <exception>
#include <string>

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Base class for exceptions.
	 */
	class XException : public std::exception
	{
	private:
		/**
		 * The message of the exception
		 */
		std::string m_message;

	public:
		/**
		 * Creates a new exception with the given message.
		 *
		 * @param message A reference to the message of the exception.
		 */
		explicit XException(const std::string &message);

		/**
		 * Gets the message of the exception.
		 *
		 * @return A <code>const char*</code> that is pointing to the message of the exception.
		 */
		[[nodiscard]] const char *what() const noexcept override;
	};

	/**
	 * Exception which is thrown when an operation is not supported.
	 */
	class UnsupportedOperationException : public XException
	{
	public:
		/**
		 * Creates a new unsupported operation exception.
		 *
		 * @param message The message of the exception.
		 */
		explicit UnsupportedOperationException(const std::string &message);
	};
}

#endif //CEDAR_XEXCEPTION_H
