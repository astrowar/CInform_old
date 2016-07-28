#include "CInterpreter.h"

namespace Interpreter
{
	OperationResult::OperationResult(ErrorCode status): error_(status)
	{
	}

	bool OperationResult::isSuccessful() const
	{
		return this->error_ == 0;
	}

	ErrorCode OperationResult::errorReason() const
	{
		return this->error_;
	}

	OperationResult Sucess()
	{
		return OperationResult(ErrorCode::SucessStatusError  );
	}

	OperationResult Fail(ErrorCode reason_cs)
	{
		return OperationResult(reason_cs);
	}

	 


	ITermSymbol::ITermSymbol(std::string _symbol):symbol(_symbol)
	{
	}

	ITermCompoundSymbol::ITermCompoundSymbol(ITermSymbol* _prop, ITermSymbol* _base): prop(_prop), base(_base)
	{
	}

	ITermString::ITermString(std::string _str): str(_str)
	{
	}

	ICommandSet::ICommandSet(ITerm* _dst, ITerm* _value): dst(_dst), value(_value)
	{
	}

	ItermAssertion::ItermAssertion(ITerm* _noum, ITerm* _noumkind): noum(_noum), noumkind(_noumkind)
	{

	}


	bool CGenericValueReference::setValue(VM::FEnviroment* env , VM::HGenericValue val)  
	{
		return true;
	}

	CInterpreter::CInterpreter(VM::FEnviroment* _env): env(_env)
	{
		
	}

 

	// All commands !!!


	VM::HGenericValue  CInterpreter::run_set(VM::FEnviroment* env , ICommandSet* cmd)
	{
		
		CGenericValueReference dst = this->getCGenericValueReference( cmd->dst );
		VM::HGenericValue   value =  this->getCGenericValue ( cmd->value) ;

        dst.setValue( env, value );


		return {};
	}

	 


	VM::HGenericValue CInterpreter::run(ICommand* cmd)  
	  {
		  if (this->env == nullptr) return nullptr;
		  return {};
	  }

	CGenericValueReference CInterpreter::getCGenericValueReference(ITerm* term)
	{
		return {};
	}

	VM::HGenericValue CInterpreter::getCGenericValue(ITerm* term)
	{
		return {};
	}

	VM::HObjectKind  CInterpreter::interpret_as_objectkind(ITerm* noumkind)
	{
		return nullptr;
	}
	
	std::string CInterpreter::term_to_string(ITerm* t)
	{
		return "noum";
	}

	void CInterpreter::setAssertion(ItermAssertion* s)
	{
		//Asertion Simples ou nao ...
		
		// o que eh o segundo termo ???
		VM::HObjectKind  kind = interpret_as_objectkind(s->noumkind);
		if (kind != nullptr)
		{
			VM::HInstance inst = make_instance(env,  term_to_string(s->noum), kind);
			return;
		}
		

	}

	VM::HInstance CInterpreter::getInstance(ITermSymbol* s)
	{
		return {};
	}

	VM::HGenericValue CInterpreter::getValue(ITermSymbol* s)
	{
		return {};
	}

	VM::HVariable CInterpreter::getVariableReference(ITermSymbol* s)
	{
		return {};
	}

	VM::HInstanceProperty CInterpreter::getObjectPropertyReference(ITermCompoundSymbol* s)
	{
		return {};
	}
}
