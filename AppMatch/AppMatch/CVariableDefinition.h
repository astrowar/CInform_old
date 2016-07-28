#pragma once
#ifndef _CVARIABLEDEFINITIONS_H
#define _CVARIABLEDEFINITIONS_H
#include <memory>
#include <string>
namespace VM
{

	class CVariable
	{
	public:
		CVariable(const std::string& name, HGenericKind  _vkind);
		HGenericKind vkind;
		HGenericValue value;
		std::string name;
	};

	using HVariable = std::shared_ptr<CVariable>;

}
#endif
