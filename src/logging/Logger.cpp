//
// Created by masy on 01.02.20.
//

#include "cedar/Logger.hpp"
#include "cedar/LoggerFactory.hpp"

// Normally i wouldn't do this, but i guess in the implementation file of a class its's ok.
using namespace cedar;

LoggerException::LoggerException(const std::string &message) : XException(message)
{}

LoggerCreationException::LoggerCreationException(const std::string &message) : LoggerException(message)
{}

Logger::Logger(const std::string &name, QueueLogAppender *queueLogAppender)
{
	this->m_name = name;
	this->m_queueLogAppender = queueLogAppender;
}

Logger::~Logger()
{
	LoggerFactory::removeLogger(this);
}