#pragma once
#ifndef _CPROPDEFINITIONS_H
#define _CPROPDEFINITIONS_H
#include <memory>
#include "CObjectDefinitions.h"
#include "CValueDefinitions.h"


class CObjectKindProperty
{
public:
	CObjectKindProperty(const std::string& name, HObjectKind _kind, HValueKind _vkind)
		: name(name),
		  kind(_kind),
		  vkind(_vkind)
	{
	}

	std::string name;
	HObjectKind kind;
	HValueKind vkind;
};

class CInstanceProperty
{
public:
	CInstanceProperty(const std::string& _name, HInstance _inst, HValueKind _vkind)
		: name(_name),
		  inst(_inst),
		  vkind(_vkind)
	{
		if (_vkind == nullptr)
		{
			throw "unable";
		}
	}

	std::string name;
	HInstance inst;
	HValueKind vkind;
};

using HInstanceProperty = std::shared_ptr<CInstanceProperty>;



#endif
