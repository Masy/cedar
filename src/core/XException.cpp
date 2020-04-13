//
// Created by Marcel Schauer on 27.01.20.
//

#include "cedar/XException.hpp"

using namespace cedar;

XException::XException(const std::string &message)
{
	this->m_message = message;
}

const char *XException::what() const noexcept
{
	return this->m_message.c_str();
}

UnsupportedOperationException::UnsupportedOperationException(const std::string &message) : XException(message)
{}
