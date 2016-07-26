// AppMatch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMatch.h"


 
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


int main()
{
	teste_1();
	teste_2();
    return 0;
}

