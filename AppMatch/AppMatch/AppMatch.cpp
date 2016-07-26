// AppMatch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMatch.h"
 
#include <sstream>
#include "FEnviroment.h"
#include <iostream>


void teste_1()
{

	auto lst1 = make_list({ make_number(2), make_number(4) });
	auto lst2 = make_list({ make_string("add"), make_number(4), make_number(3) });

	auto q=  equals(lst1, lst2);
	printf("equals ? =%i \n", q);


	  q = equals(make_number(4), make_number(4));
	printf("equals ? =%i \n", q);

}

void teste_2()
{

	auto lst = make_list({ make_number(1), make_string("X" ) ,make_number(3) ,make_number(4),  make_string("Y") ,make_number(6) ,make_number(7) ,make_number(8) ,make_number(9) });
	CList* lst_ptr = dynamic_cast<CList*>(lst.get());

	MTermSetCombinatoriaList  mlist = getCombinatorias(  lst_ptr->asVector(), 3);
	std::string s =  get_repr(mlist);
	printf("Comb:\n %s \n", s.c_str());

}


std::vector<HTerm>  decompose(std::string phase)
{
	std::stringstream test(phase);
	std::string segment;
	std::vector<HTerm> seglist;

	while (std::getline(test, segment, ' '))
	{
		seglist.push_back(make_string(segment));
	}
	return seglist;
}
void teste_match()
{
	
	std::vector<HTerm> lst = { make_string("book"), make_string("is") ,make_string("small"),  make_string("and") , make_string("portable") };
	std::vector<HPred> predList;

	lst = decompose("a book is a thing");
	
	predList.push_back(std::make_shared<CPredAny>("Noum"));
	predList.push_back(std::make_shared<CPredAtom>("Verb", make_string("is")));
	predList.push_back(std::make_shared<CPredAny>("JJ"));
	
	

	MatchResult res =  CMatch(lst, predList);
	std::string s = get_repr(res);
	printf("result:\n %s \n", s.c_str());
	return;


}

 

void teste_kinds()
{

	FEnviroment *env = new FEnviroment();
	auto thing = make_kind(env, "thing");
	auto book = make_derivade_kind(env, "book", thing);
	auto redbook = make_instance(env,"red book",book);

	CValueKindEnum *colors = new  CValueKindEnum("color", HValueKindString,  { make_string_value("red"),make_string_value("blue")});
	HValueKind colorKind = HValueKind(colors);
	CInstanceProperty colorProp = CInstanceProperty("color", redbook, colorKind);
	set_property(env, colorProp);



	auto red_book_color =  get_property(env,   redbook ,"color" );
	HValue red_book_color_value =   get_property_value(env, red_book_color);
	std::cout << toString(red_book_color_value) << std::endl;

	set_property_value(env, red_book_color, make_string_value("blue"));
	  red_book_color_value = get_property_value(env, red_book_color);
	std::cout << toString(red_book_color_value) << std::endl;


	set_property_value(env, red_book_color, make_string_value("green"));
	red_book_color_value = get_property_value(env, red_book_color);
	std::cout << toString(red_book_color_value) << std::endl;

}


int main()
{
	teste_1();
	teste_2();
	teste_match();
	teste_kinds();
    return 0;
}

