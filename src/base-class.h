/*
 * base-class.h
 *
 * This is the base class for all classes and abstract classes.
 */

#ifndef CLASSINFO_H_
#define CLASSINFO_H_

#include <iostream>

/*
 * @class
 * @Description
 * Interface for all classes derived from any of the above bases.
 * And !!!YES!!!, all classes must inherit all the classes declared here.
 * This information is currently used by the logger module.
 */
class ClassInfo {
protected:
	std::string class_name; // Name of the class
public:
	const std::string& className() const {
		return class_name;
	}
};

#endif
