//
// Created by eraldo on 04/02/2018.
//
#include <base/CBase.hpp>
#include <interpreter/CBlockInterpreterRuntime.hpp>
#include <cassert>
 
#include "sharedCast.hpp"
#include "CblockAssertion.hpp"
#include "BlockInterpreter.hpp"
 
 



using namespace std;

using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
using namespace QueryStacking;
 
#include "serialRegister.hpp"

//NSTerm::HTerm Interpreter::CBlockInterpreter::executeAssertion(HBlockAssertionBase b) {
//
//    if (HBlockAssertion_isInstanceOf inst = asHBlockAssertion_isInstanceOf(b)) {
//        instancias.push_back(inst->noum);
//    }
//
//    //assertions.push_back(b);
//    return nullptr;
//}
//
//NSTerm::HTerm Interpreter::CBlockInterpreter::execute(HBlock b) {
//    assert(b != nullptr);
//
//    if (asHBlockAssertion_is(b) != nullptr)
//        return executeAssertion(asHBlockAssertion_is(b));
//
//    return nullptr;
//}