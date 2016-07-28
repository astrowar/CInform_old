#pragma once
#pragma once
#ifndef COBJECTDEF_H
#define COBJECTDEF_H

#include <string>
 
#include <memory>

//Classes concretas

class CObjectKind;
using HObjectKind = std::shared_ptr<CObjectKind>;


class CObjectKind: public  CGenericKind
{	 
public:
	HObjectKind previous;
	std::string name;
	CObjectKind(std::string named, HObjectKind prev);
};

using HObjectKind = std::shared_ptr<CObjectKind>;

class CObjectInstance: public  CGenericValue
{
public:
	CObjectInstance(HObjectKind kind, const std::string& name)
		: kind(kind),
		  name(name)
	{
	}

	HObjectKind kind;
	std::string name;
};

using HInstance = std::shared_ptr<CObjectInstance>;








#endif
