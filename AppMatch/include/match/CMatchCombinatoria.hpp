#pragma once

#include "base/CBase.hpp"
#include "CMatch.hpp"
#include "CMatchListValid.hpp"

using namespace NSTerm;
using namespace NSTerm::NSMatch;

namespace NSTerm {
	namespace NSMatch {
		MatchResult CMatch_combinacao(MTermSetCombinatoria &combinacao, std::vector<CPred *> predicates_ptr);
		void applyCombinatorias_smart_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend, size_t n, std::vector<CPred *> preds, FuncCombinatoria &func);
	}
}