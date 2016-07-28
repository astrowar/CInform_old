#pragma once
#ifndef CASSERTDEFINITION_H
#define CASSERTDEFINITION_H
#include "CValueDefinitions.h"
#include "CProperties.h"

namespace VM
{
	class CObjectKindProperty;

	class AssertConstraint
	{
	public:
		AssertConstraint(float lk)
			: LK(lk)
		{
		}

		float LK;
	};

	class HValueAssert //class que define os parametros de contorno de um dado valor em um Kind
	{
	public:
		HValueAssert(const HValue& c_value, float constraint);
		HValue value;
		AssertConstraint constraint;
	};

	HValueAssert Usually_Value(const HValue& c_value);
	HValueAssert Always_Value(const HValue& c_value);
	bool can_set_value(HValueKind vkind, HValue val);

	class CKindPropertyAssert
	{
	public:
		CKindPropertyAssert(CObjectKindProperty property, HValueAssert value);

		CObjectKindProperty property;
		HValueAssert valueAssertion;
	};

	class CInstancePropertyAssert
	{
	public:
		CInstancePropertyAssert(CInstanceProperty property, HValue value)
			: property(property),
			value(value)
		{
		}

		CInstanceProperty property;
		HValue value;
	};


}
#endif
