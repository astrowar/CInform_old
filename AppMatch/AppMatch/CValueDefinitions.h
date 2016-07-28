#pragma once
#ifndef CVALUEDEF_H
#define CVALUEDEF_H
#include <memory>
#include "ConstDefinitions.h"
#include <list>

namespace VM
{
	class CValueKind :public CGenericKind
	{
	public:
		std::string name;
		CValueKind(std::string _name);


	};

	using HValueKind = std::shared_ptr<CValueKind>;



	class CValue;
	using  HValue = std::shared_ptr<CValue>;
	class CValue : public CGenericValue
	{
	public:
		CValue(HValueKind vkind)
			: vkind(vkind)
		{
		}
		HValueKind vkind;
		virtual HValue  clone() = 0;
	};


	extern HValueKind HValueKindBoolean;
	extern HValueKind HValueKindString;
	extern HValueKind HValueKindText;
	extern HValueKind HValueKindList;
	extern HValueKind HValueKindNumber;

	extern HValueKind HValueKindObjectInstance;
	extern HValueKind HValueKindObjectKind;

	class CValueKindEnum : public CValueKind
	{
	public:
		CValueKindEnum(const std::string& _name, HValueKind _valuesKind, const std::list<HValue>& posiblesValues)
			: CValueKind(_name),
			values(posiblesValues),
			valuesKind(_valuesKind)
		{
		}

		std::list<HValue> values;
		HValueKind valuesKind;
	};





	class CValueBoolean : public CValue
	{
	public:
		HValue clone() override;

		CValueBoolean(bool v)
			: CValue(HValueKindBoolean),
			val(v)
		{
		}
		bool val;
	};



	class CValueText : public CValue
	{
	public:
		HValue clone() override;

		CValueText(const std::string& cs)
			: CValue(HValueKindText),
			_text(cs)
		{
		}

		std::string _text;
	};

	class CValueString : public CValue
	{
	public:
		HValue clone() override;

		CValueString(const std::string& cs)
			: CValue(HValueKindString),
			_text(cs)
		{
		}

		std::string _text;
	};

	class CValueList : public CValue
	{
	public:
		HValue clone() override;

		CValueList(std::list<HGenericValue>  c_values)
			: CValue(HValueKindList),
			values(c_values)
		{
		}

		std::list<HGenericValue> values;
	};






	class CValueNumber : public CValue
	{
	public:
		HValue clone() override;

		CValueNumber(int c_value)
			: CValue(HValueKindNumber),
			value(c_value)
		{
		}

		int value;
	};




	class CValueInstance : public CValue // Value instance eh o valor dos HValueKind customizados
	{
	public:
		HValue clone() override;
		CValueInstance(const std::string& _named, HValueKind vkind);
		std::string named;
	};
	using HValueInstance = std::shared_ptr<CValueInstance>;

}

#endif
