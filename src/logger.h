/*
 * @file logger.h
 *
 * @Description
 * This file contains logging module;
 * useful for debugging.
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <chrono>
#include <ctime>
#include <typeinfo>
#include "compressor-base.h"

/// If DEBUG_ON is not defined then we define empty macros and no classes
#if !defined(DEBUG_ON)

#define Log(obj, mesg)
#define Log_static(mesg)
#define Log_plain(mesg)

#else

/// Recommended: Use this macro instead of using 'logger' directly
#define Log(obj, mesg)					\
	do {								\
		logger(*obj, __func__, mesg);	\
	} while (false);

#define Log_static(mesg)				\
	do {								\
		logger(__func__, mesg);			\
	} while (false);

#define Log_plain(mesg)					\
	do {								\
		logger(mesg);					\
	} while (false);

// This is functor class used only for generating logs
static class Logger {
public:

	// For functions that belong to a class(class-method or instance-method)
	void operator () (const ClassInfo& obj, const std::string& func_name, const std::string& mesg) {
		// TODO ...
		std::clog << 
				"In " << typeid(obj).name() << "::" <<
				func_name << "(): " << mesg << std::endl;
		
	}
	
	// For non-class function
	void operator () (const std::string& func_name, const std::string& mesg) {
		// TODO ...
		std::clog << 
				"In " << func_name << "(): " << mesg << std::endl;
		
	}
	
	// For displaying plain message
	void operator () (const std::string& mesg) {
		std::clog << mesg << std::endl;
	}
	
} 
logger;

#endif

#endif /* LOGGER_H_ */