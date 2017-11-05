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
		virtual HBlockKindAction get_base() = 0;
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
		virtual HBlockKindAction get_base() override  { return base_kind; }
	};
	using HBlockActionInstance = std::shared_ptr<CBlockActionInstance>;



	class CBlockActionNamed : public CBlockAction  // unresolved Action
	{
	public:
		std::string named;
		HBlockKindAction actionKind;
		CBlockActionNamed(std::string _named) : named(_named) { actionKind = nullptr; }
		CBlockActionNamed(std::string _named, HBlockKindAction _act) :actionKind(_act), named(_named)  {}

		virtual HBlockKindAction get_base() override  { return actionKind ; }
		virtual void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockActionNamed; }
	};
	using HBlockActionNamed = std::shared_ptr<CBlockActionNamed>;



 
	class CBlockTryCall : public CBlock 
	{
		public:
			CBlocking::HBlock sentence;		 
			CBlockTryCall(CBlocking::HBlock _sentence) : sentence(_sentence){}
			virtual void dump(string ident) override;
			virtual BlockType type() override { return BlockType::BlockTryCall; }
	};

	using HBlockTryCall = std::shared_ptr<CBlockTryCall>;





	class CBlockActionCall : public CBlock {
	public:
 
		CBlocking::HBlock noum1;
		CBlocking::HBlock noum2;

		CBlockActionCall(  CBlocking::HBlock _noum1, CBlocking::HBlock _noum2) :  noum1(_noum1),
			noum2(_noum2) {}

	 
		virtual BlockType type() override { return BlockType::BlockActionCall; }
	};

	using HBlockActionCall = std::shared_ptr<CBlockActionCall>;



	class CBlockActionCallNamed : public CBlockActionCall {
	public:
		HBlockActionNamed action;  //named , porque ha mais de uma forma de executar uma acao, com argumentos diferentes
 

		CBlockActionCallNamed(HBlockActionNamed _action, CBlocking::HBlock _noum1, CBlocking::HBlock _noum2) : CBlockActionCall(_noum1,_noum2), action(_action) {}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockActionCallNamed; }
	};

	using HBlockActionCallNamed = std::shared_ptr<CBlockActionCallNamed>;


	 


	class CBlockStaticDispatch : public CBlockActionCall {
	public:
		int staticEntryTable; 
		CBlockStaticDispatch(int _staticEntryTable, CBlocking::HBlock _noum1, CBlocking::HBlock _noum2) :CBlockActionCall(_noum1, _noum2),
			staticEntryTable(_staticEntryTable)    {}

		void dump(string ident) override;
		virtual BlockType type() override { return BlockType::BlockStaticDispatch; }


	};

	using HBlockStaticDispatch = std::shared_ptr<CBlockStaticDispatch>;







#endif
};
