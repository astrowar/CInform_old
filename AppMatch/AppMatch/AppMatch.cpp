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


	auto book = make_derivade_kind(env, "book", thing); //book is a kind of thing
	auto redbook = make_instance(env,"red book",book); //red book is a book
	 

}


void teste_instances()
{
	
}


void teste_properties1()
{
	FEnviroment *env = new FEnviroment();
	auto thing = make_kind(env, "thing");
	
	// A thing can be hot or cold. A thing is usually cold.
	{
		auto thing_hot_cold = CKindProperty("", thing, makeValueKindEnum(env, "", HValueKindString, { make_string_value("hot"),make_string_value("cold") }));
		auto thing_hot_cold_assertion = CKindPropertyAssert(thing_hot_cold, Usually_Value(make_string_value("cold")));
		assign_property (env, thing_hot_cold_assertion);
	}

	
	{
		// Temperature is a kind of value.The temperatures are cold, warm, and hot.
		auto temp_kind = makeValueKind(env, "Temperature" );

		auto v_cold = makeValueInstance(env, "cold", temp_kind);
		auto v_warm = makeValueInstance(env, "warm", temp_kind);
		auto v_hot = makeValueInstance(env, "hot", temp_kind);

		auto potato = make_instance(env, "potato", thing);
		//The potato has a temperature called the heat. 
		CInstanceProperty heat_potato_prop = CInstanceProperty("heat", potato, temp_kind);


	}
}

void teste_properties2()
{
	FEnviroment *env = new FEnviroment();
	auto thing = make_kind(env, "thing");
	
	auto book = make_derivade_kind(env, "book", thing); //book is a kind of thing
	auto redbook = make_instance(env, "red book", book); //red book is a book
	
	auto colorsKind = makeValueKindEnum(env, "colors", HValueKindString, { make_string_value("red"),make_string_value("blue") }); //Colors is a kind of value. The Colors are red and blue.
	CInstanceProperty colorProp = CInstanceProperty("color", redbook, colorsKind); //  red book has a Colors called color.
	assign_property(env, colorProp);


	auto red_book_color =  get_property(env,   redbook ,"color" );
	HValue red_book_color_value =   get_property_value(env, red_book_color);
	std::cout << toString(red_book_color_value) << std::endl;

	set_property_value(env, red_book_color, make_string_value("blue"));
	  red_book_color_value = get_property_value(env, red_book_color);
	std::cout << toString(red_book_color_value) << std::endl;


	//set_property_value(env, red_book_color, make_string_value("green"));
	//red_book_color_value = get_property_value(env, red_book_color);
	//std::cout << toString(red_book_color_value) << std::endl;
}

void teste_properties3()
{
	

	FEnviroment *env = new FEnviroment();
	auto thing = make_kind(env, "thing");
	{
		auto umbrella = make_instance(env, "umbrella", thing); //umbrella is a thing

		//The umbrella can be openable.  
		auto umbrella_openable = CInstanceProperty("openable", umbrella, HValueKindBoolean);
		assign_property(env, umbrella_openable);

		auto umbrella_openable_prop = get_property(env, umbrella, "openable");
		set_property_value(env, umbrella_openable_prop, make_bool_value(true));//The umbrella is openable.


		auto umbrella_openable_value = get_property_value(env, umbrella_openable_prop);
		std::cout << "umbrella is openable ?  " << toString(umbrella_openable_value) << std::endl;

	}
	//Same but now for Kinds

	// A dead end has a property called river sound.The river sound of a dead end is usually "a faint whispering of	running water".
	// The Tortuous Alcove has river sound "a gurgle of running water".

	{
		auto room = make_kind(env, "room");
		auto deadEnd = make_derivade_kind(env, "dead end", room); //umbrella is a thing

		//A dead end has a property called river sound
		auto deadEnd_riverSong = CKindProperty("river sound", deadEnd, HValueKindText);

		//The river sound of a dead end is usually "a faint whispering of running water".

		auto deadEnd_riverSong_text = CKindPropertyAssert(deadEnd_riverSong, Usually_Value(make_text_value("a faint whispering of running water")));
		assign_property(env, deadEnd_riverSong_text);

		// Tortuous Alcove is a dead end.
		auto TortuousAlcove = make_instance(env, "Tortuous Alcove", deadEnd); 

		auto TortuousAlcove_riverSong = get_property(env, TortuousAlcove, "river sound");

		//Testa com o default 
		auto TortuousAlcove_riverSong_value = get_property_value(env, TortuousAlcove_riverSong);
		std::cout << "river Song == " << toString(TortuousAlcove_riverSong_value) << std::endl;

		//Seta o novo valor 
		//The Tortuous Alcove has river sound "a gurgle of running water".
		set_property_value(env, TortuousAlcove_riverSong, make_text_value("a gurgle of running water"));


		//Verifica a mudanca
		TortuousAlcove_riverSong_value = get_property_value(env, TortuousAlcove_riverSong);
		std::cout << "river Song == " << toString(TortuousAlcove_riverSong_value) << std::endl;
	}
}


void teste_kindValue1()
{
	FEnviroment *env = new FEnviroment(); 
	auto thing = make_kind(env, "thing");

	//The lantern has a number called the brightness level.
	auto lantern = make_instance(env, "lantern", thing);
	auto lantern_brightnessLevel = CInstanceProperty("brightness level", lantern, HValueKindNumber);	 
	assign_property(env, lantern_brightnessLevel);


	//Brightness is a kind of value. The brightnesses are guttering, weak, radiant and blazing.
	HValueKind  BrightnessKind = makeValueKindEnum(env, "Brightness", HValueKindString, { make_string_value("guttering"),make_string_value("weak") ,make_string_value("radiant") ,make_string_value("blazing")  });


	//The lantern has a brightness called the flame strength. 
	auto lantern_flameStrength = CInstanceProperty("flame strength", lantern, BrightnessKind);
	assign_property(env, lantern_flameStrength);


	//The flame strength of the lantern is blazing.
	auto lantern_flameStrength_prop = get_property(env, lantern, "flame strength");
	set_property_value(env, lantern_flameStrength_prop, make_string_value("blazing"));


	HValue lantern_flameStrength_value = get_property_value(env, lantern_flameStrength_prop);
	std::cout << "lantern flame strength == " << toString(lantern_flameStrength_value) << std::endl;

	auto lantern_brightnessLevel_prop = get_property(env, lantern, "brightness level");
	set_property_value (env, lantern_brightnessLevel_prop , make_number_value( 1));
	HValue lantern_brightnessLevel_value = get_property_value(env, lantern_brightnessLevel_prop);
	std::cout << "lantern brightness level == " << toString(lantern_brightnessLevel_value) << std::endl;

}

int main()
{
	 teste_1();
	teste_2();
	teste_match();
	teste_kinds();
	teste_instances();
	teste_properties1();
	teste_properties2();
	teste_properties3(); 


	teste_kindValue1();

    return 0;
}

