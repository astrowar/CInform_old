//
// Created by eraldo on 04/02/2018.
//

#include <cassert>
#include "dynamicCast.hpp"
#include "sharedCast.hpp"
#include "CblockAssertion.hpp"
#include "BlockInterpreter.hpp"
#include "CInterpreterRuntimeExecute.hpp"
#include "serialRegister.hpp"


using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;
using namespace CBlocking::VariableSloting;


NSTerm::HTerm Interpreter::CBlockInterpreter::executeAssertion(HBlockAssertionBase b) {

    if (HBlockAssertion_isInstanceOf inst = asHBlockAssertion_isInstanceOf(b)) {
        instancias.push_back(inst->noum);
    }

    //assertions.push_back(b);
    return nullptr;
}

NSTerm::HTerm Interpreter::CBlockInterpreter::execute(HBlock b) {
    assert(b != nullptr);

    if (asHBlockAssertion_is(b) != nullptr)
        return executeAssertion(asHBlockAssertion_is(b));

    return nullptr;
}