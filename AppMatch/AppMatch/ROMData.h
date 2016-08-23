#pragma once
#include <string>
#include <map>
#include <fstream>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp> 
#include <cereal/access.hpp> 

class CBlock;

#include "CBase.h"

 


class ROMData
{
 
public:
	
	std::vector<int> data;
	int slot;
	int32_t id;
	HTerm cs1;

	ROMData(int fields );
	virtual ~ROMData();
	 

	template <class Archive>
	void save(Archive& ar) const;

	template <class Archive>
	void load(Archive& ar);

	void aStore();

	void aLoad();
};

template <class Archive>
void ROMData::save(Archive& ar) const
{
	ar(cs1);
	ar(data);
}

template <class Archive>
void ROMData::load(Archive& ar)
{
	static int32_t idGen = 0;
	id = idGen++;		
	ar(cs1);
	ar(data);
}

namespace cereal
{
	template <> struct LoadAndConstruct<ROMData>
	{
		// load_and_construct will be passed the archive that you will be loading
		// from as well as a special construct object that can be used to invoke
		// the constructor for your class.
		//
		// More advanced functionality is available using construct, such as accessing
		// class members, which is detailed in the doxygen docs.
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<ROMData> & construct)
		{
			int x;
			ar(x);
			construct(x); // calls MyType( x )
		}
	};
}




template<class Archive>
void serialize(Archive & archive, CString & m)
{
	archive(m.s);
}

template<class Archive>
void serialize(Archive & archive, CNumber & m)
{
	archive(m.val);
}


#include <cereal/types/polymorphic.hpp>


CEREAL_REGISTER_TYPE(CNumber);
CEREAL_REGISTER_TYPE(CString);

CEREAL_REGISTER_POLYMORPHIC_RELATION(CTerm, CNumber)
CEREAL_REGISTER_POLYMORPHIC_RELATION(CTerm, CString)



namespace cereal
{
	template <> struct LoadAndConstruct<CNumber>
	{ 
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<CNumber> & construct)
		{
			int x;
			ar(x);
			construct(x);  
		}
	};

	template <> struct LoadAndConstruct<CString>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<CString> & construct)
		{
			std::string x;
			ar(x);
			construct(x);
		}
	};
}