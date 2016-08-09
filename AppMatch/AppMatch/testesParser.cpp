#include "Parser.h"
#include <iostream>
std::vector<HTerm> decompose(std::string phase);;
std::string  decompose_bracket(std::string phase, std::string dlm);
CList*  mk_CList_Literal(std::vector<HTerm> strList);

void testeParser_1()
{
	std::string phase_1 = "(red  book)    is a kind of    thing  ";
	phase_1 = "( book,  stone and  ( metal bird))  are  some things ";
	phase_1 = decompose_bracket(phase_1, "(");
	phase_1 = decompose_bracket(phase_1, ")");
	std::cout << phase_1 << std::endl;

	std::vector<HTerm>  lst = decompose(phase_1);
	CList* lst_ptr = mk_CList_Literal(lst);
	std::cout << lst_ptr->repr() << std::endl;
	//MTermSetCombinatoriaList mlist = getCombinatorias(lst_ptr->asVector(), 3);

	auto vecList = lst_ptr->asVector();
	FuncCombinatoria f_disp = [](MTermSetCombinatoria& x) { std::cout << get_repr(x) << std::endl; return false; };
	applyCombinatorias(vecList, 3 , f_disp );

	  std::cout << "..." << std::endl;
}

void testeParser_2()
{
	CBlockInterpreter *interpreter = new CBlockInterpreter();

	{
		CParser parse;
		std::string phase_1 = "a diary are a book ";
		interpreter->execute(parse.parser("  book is a thing "));
		interpreter->execute(parse.parser("diary are an book "));
		interpreter->execute(parse.parser("book is small "));
		parse.parser("book is small ")->dump("");
 
		 //res->dump("");
		 //std::cout << std::endl;
	 

		CBlock* query = parse.parser_only("the diary is small");
		if ( interpreter->query(  static_cast<CBlockAssertion_is*>(query)))
		{
			std::cout <<"OK" << std::endl;
		}
	}

	 

	{
		CParser parse;
		std::string phase_1 = "( iron, silver, chopper)  are kinds of metal  ";
		 auto res = parse.parser(phase_1);
		 if (res == nullptr) throw "parse error";
		 res->dump("");
		 std::cout << std::endl;
	}

	{
		CParser parse;
		std::string phase_1 = "metal  is a kind   ";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		//res->dump("");
		//std::cout << std::endl;
	}

	return;
}

void testeParser_3()
{
	CParser parse;
	{
		std::string phase_1 = "eat  is (an action  applying to (one thing ))";
	 	auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		//res->dump("");
	}
	{
		std::string           phase_1 = "(cut ) is    an action   applying to (one thing) and (a Cutter)   ";
		auto  res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		//res->dump("");
	}
	return;
}

void testeParser_4()
{
	CParser parse;
	{
		std::string phase_1 = "A thing can be discovered or secret";
		 auto res = parse.parser(phase_1);
		 if (res == nullptr) throw "parse error";
		// res->dump("");
	}

	{
		std::string phase_1 = "(size of Book ) can be normal , huge or  small";
		 auto res = parse.parser(phase_1);
		 if (res == nullptr) throw "parse error";
		// res->dump("");
		 //std::cout << std::endl;
	}

	{
		std::string phase_1 = "(A person) has a (table-name) called (the opinion-table)";		
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		 res->dump("");
		 std::cout << std::endl;
	}

	{
		std::string phase_1 = "The (singing action) has a (text) called the lyric sung";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		//res->dump("");
		//std::cout << std::endl;
	}

	//"Brightness is a kind of value";
	//"The brightnesses are guttering, weak, radiant and blazing";
	//"The torch has a brightness";
	//	"The torch	is blazing";
	//"The torch is lit";
	//std::cout << std::endl;
	return;
}


void testeParser_5()
{
	CParser parse;
	{
		std::string phase_1 = "to decide what (room) is (the safest location) : (decide on) ";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		 res->dump("");
	}
	{
		std::string phase_1 = "to decide what (person) is the (brother to/of (sibling - a person)) : (decide on) ";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}

	{
		std::string phase_1 = "to decide what (indexed text) is ((T - text) doubled) : (decide on) ";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}
}


void testeParser_6()//kind of value
{
	CParser parse;
	{
		std::string phase_1 = "A limb is a kind of value";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}
	{
		std::string phase_1 = "color is a kind of value  ";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}

	{
		std::string phase_1 = "An aspect ratio is a kind of value";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}
	 

	{
		std::string phase_1 = "  color  are blue, green, yellow  and red ";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}

	{
		std::string phase_1 = "  black  specifies an color ";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}
}

void testeParser_20() //custrom rlacions
{
	 
	CParser parse;
	{
		std::string phase_1 = "Fanciness relates a ( thing called X ) to ( some money called Y ) when ( (the price of X) > (the price of Y ))";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}
	
	{
		std::string phase_1 = "let L be the (list of ( things fancier than/of/in/on 20 ) ) )";
		auto res = parse.parser(phase_1);
		if (res == nullptr) throw "parse error";
		res->dump("");
	}
}

void testeParser ()
{
	 // testeParser_1();
	  
	//for (int k = 0; k < 400; ++k)
	{
		 testeParser_2();
		//testeParser_3();
		//testeParser_4();
		// testeParser_6();
		std::cout << ".";
	}
	std::cout << std::endl;
}