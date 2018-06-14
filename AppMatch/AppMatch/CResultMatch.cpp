// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "CResultMatch.hpp"

using namespace CBlocking;
 

CResultMatch::CResultMatch(string s, HBlock b) : hasMatch(true)
{
	maptch[s] = b;
}

CResultMatch::CResultMatch(bool r) :hasMatch(r)
{

}

void CResultMatch::append(const CResultMatch & r)
{
	for(auto &kv: r.maptch)
	{
		maptch[kv.first] = kv.second;
	}
};
