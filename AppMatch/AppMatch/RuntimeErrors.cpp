

#include "CBlockInterpreterRuntime.hpp"

using namespace CBlocking;
using namespace Interpreter;


PhaseResult Interpreter::CBlockInterpreter::raise_runtime_error(std::string message )
{
	logError(message);
	return PhaseResult("false");
}
