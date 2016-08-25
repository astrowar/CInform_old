//
// Created by Eraldo Rangel on 23/08/16.
//
#include "Parser.h"
#include <iostream>
#include <algorithm>

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

HTerm expandBract(HTerm term) {
    if (CList *clist = dynamic_cast<CList *>(term.get())) {
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
    std::list<std::shared_ptr<CPred> > predlist;
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
        std::vector<HPred> predList;
        predList.push_back(mkHPredAny("Verb"));
        predList.push_back(mkHPredAny("Aux"));
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
            HBlockList clist = std::make_shared<CBlockList>();
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

	if (CList *clist = dynamic_cast<CList *>(termo)) {
		auto vlist = clist->asVector();
		vlist = remove_boundaryListMark(vlist);

		auto hpr = mkHPredList("predListing", {});
		CPredList *predList = dynamic_cast<CPredList *>(hpr.get());

		for (auto k : vlist) {
			predList->plist.push_back(convert_to_predicate(k.get()));
		}
		return hpr;
	}
	else {
		if (CString *css = dynamic_cast<CString *>(termo)) {

			return mk_HPredLiteral(css->s);
		}

	}

	return mk_HPredLiteral(termo->repr());
}
