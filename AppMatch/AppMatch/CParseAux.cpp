// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Eraldo Rangel on 23/08/16.
//
#include "Parser.hpp"
 
#include <algorithm>
#include <sstream>
#include <cassert>

using namespace CBlocking;
 
using namespace NSTerm;
using namespace NSTerm::NSMatch;


std::string  decompose_bracket(std::string phase, std::string dlm) {

	size_t b = phase.find(dlm);
	if (b != std::string::npos) {
		std::string sa = phase.substr(0, b);
		std::string sb = phase.substr(b + 1, phase.size() - b - 1);
		sb = decompose_bracket(sb, dlm);
		return sa + " " + dlm + " " + sb;
	}
	return phase;
}

std::vector<HTerm> decompose(std::string phase) {
	std::stringstream test(phase);
	std::string segment;
	std::vector<HTerm> seglist;
	while (getline(test, segment, ' ')) 
	{
		if (segment.length() > 0) 
		{
			if (segment[0] != ' ' && segment[0] != '\t' && segment[0] != '\r')
			{
				 
				seglist.push_back(make_string(segment));
			}
		}
	}
	
	return seglist;
}

HPred mk_HPredLiteral(string str) {
    return mkHPredAtom("_", make_string(str));
}

 



string get_repr(std::vector<HPred> plist) {
    string ret = "";
    for (auto p : plist) {
        ret += p->repr();
    }
    return ret;
}

 
string CtoString(CList * lst)
{
	if (lst->lst.empty()) return "";
	if (lst->lst.size() == 1) return CtoString(lst->lst.front());
	std::string vstr = "";
	bool fronti = true;
	for (auto &v : lst->lst)
	{
		if (!fronti) vstr += " ";
		vstr += CtoString(v);
		fronti = false;
	}
	return vstr;

}
string CtoString(HTerm  value)
{
	return CtoString(value.get());
}

string CtoString(CTerm  *value)
{
	if (CString* lstr = asCString(value)) {
		return lstr->s;
	}
	if (CList* lst = asCList(value)) {
		{
			return CtoString(lst);
		}
	}

    assert(false);
    return "";

}


HTerm expandBract(HTerm term) {
    if (CList *clist = asCList(term.get())) {
        if (clist->lst.front()->is_openBracket() && clist->lst.back()->is_closeBracket()) {
            auto vlist = clist->asVector();
            vlist = remove_boundaryListMark(vlist);
            CList *cnew = new CList();
            cnew->lst = std::list<HTerm>(vlist.begin(), vlist.end());
            return std::shared_ptr<CList>(cnew);
        } else {
            return term;
        }
    }
    return term;
}

std::vector<HTerm> get_tail(std::vector<HTerm> &qlist) {
    std::vector<HTerm> v;
    bool front = true;
    for (auto it = qlist.begin(); it != qlist.end(); ++it) {
        if (!front) { v.push_back(*it); }
        front = false;
    }
    return v;
}

HPred mk_HPredLiteral_OR(string _named, std::initializer_list<string> alist) {
    std::list<string> strList(alist);
    std::list<std::shared_ptr<CPred> > predlist;
    for (auto it = strList.begin(); it != strList.end(); ++it) {
        predlist.push_back(mkHPredAtom("_", make_string(*it)));
    }
    return std::make_shared<CPredBooleanOr>(_named, predlist);
}

CList *mk_CList_Literal(std::vector<HTerm> strList) {
    auto clist = new CList();
     
    for (auto it = strList.begin(); it != strList.end(); ++it) {
        clist->push_back(*it);
    }
    return clist;
}

HPred undefinedArticle() {
    return mkHPredBooleanOr("_", mk_HPredLiteral("a"), mk_HPredLiteral("an"));
}

HPred verb_IS() {
    return mkHPredBooleanOr("is", mk_HPredLiteral("are"), mk_HPredLiteral("is"));
}

HPred verb_IS_NOT() {
    return mkHPredBooleanOr("isnot", mkHPredList("isNotList", {mk_HPredLiteral("is"), mk_HPredLiteral("not")}),
                            mk_HPredLiteral("arent"));
}

HPred mk_What_Which() {
    return mkHPredBooleanOr("what_TERM", mk_HPredLiteral("what"), mk_HPredLiteral("which"), mk_HPredLiteral("whether"));
}

std::pair<HBlock, HPred> getVerbAndAux(HTerm term) {

    {
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mkHPredAny("Verb"));
			predList.push_back(mkHPredAny("Aux"));
		}
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList clist = std::make_shared<CBlockList>(std::list<HBlock>());
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr()));
            clist->push_back(std::make_shared<CBlockNoum>(res.matchs["Aux"]->repr()));

            HPred verbMatch = (mkHPredList("VerbMatch", {
                    mk_HPredLiteral(res.matchs["Verb"]->repr()),
                    mk_HPredLiteral(res.matchs["Aux"]->repr()),
            }));
            return std::pair<HBlock, HPred>(clist, verbMatch);
        }
    }

    {
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Verb"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlock clist = std::make_shared<CBlockNoum>(res.matchs["Verb"]->repr());
            HPred verbMatch = mk_HPredLiteral(res.matchs["Verb"]->repr());

            return std::pair<HBlock, HPred>(clist, verbMatch);
        }

    }
    return std::pair<HBlock, HPred>(nullptr, nullptr);
}



HPred convert_to_predicate(CTerm *termo) {

	if (CList *clist = asCList(termo)) {
		auto vlist = clist->asVector();
		vlist = remove_boundaryListMark(vlist);

		auto hpr = mkHPredList("predListing", {});
		CPredList *predList = asPredList (hpr.get());

		for (auto k : vlist) {
			predList->plist.push_back(convert_to_predicate(k.get()));
		}
		return hpr;
	}
	else {
		if (CString *css = asCString(termo)) {

			return mk_HPredLiteral(css->s);
		}

	}

	return mk_HPredLiteral(termo->repr());
}
