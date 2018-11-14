//
// Created by eraldo on 14/11/2018.
//

#include "interpreter/CBlockInterpreterRuntime.hpp"
#include "BlockInterpreter.hpp"
#include "PhaseResult_init.h"

Interpreter::PhaseResult::PhaseResult(bool _hasExecuted): hasExecuted(_hasExecuted)
{
	result = nullptr;
}

Interpreter::PhaseResult::PhaseResult(HBlock _result) : hasExecuted(true)
{
	result = _result;
}