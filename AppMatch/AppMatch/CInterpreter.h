#pragma once

#ifndef _CINTEPRETERMAIN_H
#define _CINTEPRETERMAIN_H

#include "CValueDefinitions.h"
#include "FEnviroment.h"


// Aqui tem funcoes mais complexas
// Pois deve-se interpretar o conteudo das Slist, tal como no scheme


namespace Interpreter
{
	enum ErrorCode {SucessStatusError = 0 , UndefinedError = 1, InvalidError = 2,  WrongTypeError = 3 };


	class OperationResult
	{	
	public:
		OperationResult(ErrorCode status);
		bool isSuccessful() const;
		ErrorCode errorReason() const;

		ErrorCode error_;
	};

	OperationResult Sucess();
	OperationResult Fail(ErrorCode  reason_cs );

	//Todos os comandos sao staticos , pois o CODE eh estatico !


	class ITerm  
	{
	public:
		virtual ~ITerm() {};
	};


	class ITermAtom : public  ITerm
	{
	public:
		ITermAtom(){};
		 
	};


	class INIL : public  ITermAtom
	{
	public:
		INIL() {};
	};



	//Classe symbol, define algo que o interpretador ira provir como Referencia 
	class ITermSymbol : public  ITermAtom
	{
	public:
		ITermSymbol(std::string _symbol); 
		std::string symbol;
	};

	class ITermCompoundSymbol : public  ITermAtom
	{
	public:
		ITermCompoundSymbol(ITermSymbol* _prop , ITermSymbol* _base); // name of book -> (name , book )
		ITermSymbol* prop;
		ITermSymbol* base;
	};


	class ITermString : public  ITermAtom
	{
	public:
		ITermString(std::string _str);
		std::string str;
	};








	//================================================================================================

	//Class base que define o cmd 
	class ICommand: public ITerm
	{ 

	};
	class ICommandSet : public  ICommand
	{
	public:
		 
		ICommandSet(ITerm* _dst, ITerm* _value);
		ITerm* dst;
		ITerm* value;
	};


	// Class que acomoda os comandos do tipo 
	// Book is a Thing.
	// Este termo pode ser um comando ou uma questao
	class ItermAssertion  : public  ITerm
	{
	public:
		ItermAssertion(ITerm* _noum, ITerm* _noumkind);
		ITerm* noum;
		ITerm* noumkind;
	};



	//Referencia para um LValue 
	class CGenericValueReference
	{
	public:
		bool setValue(VM::FEnviroment* env, VM::HGenericValue val)  ;
	};


	class CInterpreter
	{
		CInterpreter(VM::FEnviroment* env);
		VM::HGenericValue  run_set(VM::FEnviroment* env, ICommandSet  *cmd);
		VM::HGenericValue run(ICommand* cmd);
		VM::FEnviroment *env;
		CGenericValueReference getCGenericValueReference(ITerm* term);
		VM::HGenericValue  getCGenericValue (ITerm* term);
		VM::HObjectKind interpret_as_objectkind(ITerm* noumkind);
		std::string term_to_string(ITerm* t);
		// inicia pelas coisas mais simples


		void   setAssertion(ItermAssertion  *s);



		VM::HInstance  getInstance(ITermSymbol *s);
		VM::HGenericValue   getValue(ITermSymbol *s);
		
		
		// sao referencias  de objetos mutaveis ?
		VM::HVariable   getVariableReference(ITermSymbol *s);
		VM::HInstanceProperty getObjectPropertyReference(ITermCompoundSymbol *s);



	};

	 



}


#endif
