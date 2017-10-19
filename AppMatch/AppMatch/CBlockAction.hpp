#pragma once
#ifndef APPMATCH_BLOCKACTION_H
#define APPMATCH_BLOCKACTION_H


#include "BlockInterpreter.hpp"
#include "CBlockNamedVariable.hpp"
#include <string>

namespace CBlocking
{
	class CBlockAction : public CBlock  // um bloco que representa uma atividade
	{
	public:		 
		CBlockAction( )  {		} 
		virtual HBlockKindAction get_base() =0;
	};
	using HBlockAction = std::shared_ptr<CBlockAction>;



	class CBlockActionInstance : public CBlockAction  // um bloco que representa uma atividade
	{
	public:
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockAction; }
		CBlockActionInstance(HBlockKindAction _base_kind) : base_kind(_base_kind) 	{		}
		void newNamedVariable(HBlockNoum called, HBlockKind kind);
		HVariableNamed get_property(string pnamed);
		void set_property(string pnamed, CBlocking::HBlock value);
		std::vector<HVariableNamed> namedSlots;
		HBlockKindAction base_kind;
		virtual HBlockKindAction get_base() { return base_kind; }
	};
	using HBlockActionInstance = std::shared_ptr<CBlockActionInstance>;



	class CBlockActionNamed : public CBlockAction  // unresolved Action
	{
	public:
		std::string named;
		HBlockAction action;
		CBlockActionNamed(std::string _named) : named(_named) { action = nullptr; }
		CBlockActionNamed(std::string _named, HBlockAction _act) :action(_act), named(_named)  {}

		virtual HBlockKindAction get_base() { return action->get_base(); }
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockActionNamed; }
	};
	using HBlockActionNamed = std::shared_ptr<CBlockActionNamed>;





	class CBlockActionCall : public CBlock {
	public:
		HBlockActionNamed action;  //named , porque ha mais de uma forma de executar uma acao, com argumentos diferentes
		CBlocking::HBlock noum1;
		CBlocking::HBlock noum2;

		CBlockActionCall(HBlockActionNamed _action, CBlocking::HBlock _noum1, CBlocking::HBlock _noum2) : action(_action), noum1(_noum1),
			noum2(_noum2) {}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockActionCall; }
	};

	using HBlockActionCall = std::shared_ptr<CBlockActionCall>;






	class CBlockStaticDispatch : public CBlockAction {
	public:
		int staticEntryTable;
		CBlocking::HBlock noum1;
		CBlocking::HBlock noum2;

		CBlockStaticDispatch(int _staticEntryTable, CBlocking::HBlock _noum1, CBlocking::HBlock _noum2) :CBlockAction(),
			staticEntryTable(_staticEntryTable), noum1(_noum1), noum2(_noum2) {}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockStaticDispatch; }


	};

	using HBlockStaticDispatch = std::shared_ptr<CBlockStaticDispatch>;







#endif
};