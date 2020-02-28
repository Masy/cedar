//
// Created by Marcel Schauer on 27.01.20.
//

#include "cedar/XException.h"

// Normally i wouldn't do this, but i guess in the implementation file of a class that's ok.
using namespace cedar;

XException::XException(const std::string &message)
{
	this->m_message = message;
}

const char *XException::what() const noexcept
{
	return this->m_message.c_str();
}