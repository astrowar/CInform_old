#ifndef VERBENG
#define VERBENG

typedef struct VERBTENSE
{
	const char* tense;
	const char* world;
	VERBTENSE(const char* t, const char* w) : tense(t), world(w) {}
}
VERBTENSE;

typedef struct VERBDEF
{
	const char* verb;
	const std::vector<VERBTENSE>  tenses;
	VERBDEF(const char* v, const std::vector<VERBTENSE> vv) : verb(v), tenses(vv) {}
}
VERBDEF;

typedef struct VERBTABLE
{
	VERBDEF* verbs;
	long numEntries;
}VERBTABLE;

VERBTABLE verb_table();


#endif