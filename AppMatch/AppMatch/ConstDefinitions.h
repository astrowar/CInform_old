#pragma once
#ifndef _CDEFINITIONS_H
#define _CDEFINITIONS_H
#include <memory>
#include <string>
 

namespace VM
{
	// Classes  abstradas .. que servem como protocolos
	class CGenericKind abstract
	{
	public:
		virtual ~CGenericKind()
		{
		}

		virtual void some() {};

	};

	using HGenericKind = std::shared_ptr<CGenericKind>;

	class CGenericValue abstract
	{
	public:
		virtual ~CGenericValue()
		{
		}

		virtual void some() {};
	};
	using HGenericValue = std::shared_ptr<CGenericValue>;



}





#endif
