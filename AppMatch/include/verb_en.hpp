#ifndef VERBENG
#define VERBENG

typedef struct VERBTENSE
{
	const char* tense;
	const char* world;
	constexpr VERBTENSE(const char* t, const char* w) : tense(t), world(w) {}
}
VERBTENSE;

typedef struct VERBDEF
{
	const char* verb;
	const int n ;
	const VERBTENSE*  tenses;
	constexpr VERBDEF(const char* v,int _n , const VERBTENSE* vv) : verb(v), n(_n), tenses(vv) {}
}
VERBDEF;

typedef struct VERBTABLE
{
	const VERBDEF* verbs;
	long numEntries;
    constexpr VERBTABLE(long _numEntries ,const VERBDEF* _verbs): numEntries(_numEntries),verbs(_verbs){}
}VERBTABLE;

VERBTABLE verb_table();


#endif