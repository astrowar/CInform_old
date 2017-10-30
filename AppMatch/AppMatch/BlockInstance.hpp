//
// Created by Eraldo Rangel on 19/08/16.
//

 

#ifndef APPMATCH_BLOCKINSTANCE_H
#define APPMATCH_BLOCKINSTANCE_H

#include "BlockInterpreter.hpp"
#include <string>
#include "CBlockNamedVariable.hpp"
namespace CBlocking
{

	class CBlockInstance : public CBlock //retorna um valor generico
	{
	public:
		void dump_contents(string ident);
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockInstance; }

		CBlockInstance(  int id, HBlockKind base);

		void newEnumVariableSlot(HBlockEnums definition);

		void newBoolVariableSlot(HBlockNoum value);

		void newNamedVariable(HBlockNoum called, HBlockKind kind);

		void set(HBlockNoum c_block);

		void unset(HBlockNoum c_block);

		bool has_slot(HBlockNoum value);

		HVariableNamed get_property(string named);

		void set_property(string cs, CBlocking::HBlock value);

		QueryResul is_set(HBlockNoum value);

		 
		int id;  // id unico para cada instancia .. serve para saber se estamos a falar da mesma instancia
		HBlockKind baseKind;

		 

		std::vector<HVariableSlot> anomimousSlots;
		std::vector<HVariableNamed> namedSlots;

	};

	using HBlockInstance = std::shared_ptr<CBlockInstance>;



	class CBlockInstanceNamed : public CBlockInstance
	{
		public:
			virtual void dump(string ident) override;
			virtual BlockType type() override { return BlockType::BlockInstanceNamed; }

		string named;
		CBlockInstanceNamed(string _named, int _id, HBlockKind _base) : CBlockInstance(_id,_base), named(_named){}
	};
	using HBlockInstanceNamed = std::shared_ptr<CBlockInstanceNamed>;



	//Values Instances .. Text , Number , DateTime 




	class CBlockText : public CBlock //retorna um valor generico
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockText; }
		std::string contents;
		CBlockText(std::string _contents) : contents(_contents) {}
	};
	using HBlockText = std::shared_ptr<CBlockText>;



}

#endif //APPMATCH_BLOCKINSTANCE_H
