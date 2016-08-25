// AppMatch.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "CMatch.h"
#include <sstream>
#include "FEnviroment.h"
#include <iostream>

using namespace VM;

void teste_1() {
    auto lst1 = make_list({make_number(2), make_number(4)});
    auto lst2 = make_list({make_string("add"), make_number(4), make_number(3)});
    auto q = equals(lst1, lst2);
    printf("equals ? =%i \n", q);
    q = equals(make_number(4), make_number(4));
    printf("equals ? =%i \n", q);
}

void teste_2() {
    auto lst = make_list(
            {make_number(1), make_string("X"), make_number(3), make_number(4), make_string("Y"), make_number(6),
             make_number(7), make_number(8), make_number(9)});
    CList *lst_ptr = dynamic_cast<CList *>(lst.get());
    auto asVector = lst_ptr->asVector();

    MTermSetCombinatoriaList mlist = getCombinatorias(asVector, 3);
    std::string s = get_repr(mlist);
    printf("Comb:\n %s \n", s.c_str());
}


std::string decompose_bracket(std::string phase, std::string dlm) {

    size_t b = phase.find(dlm);
    if (b != std::string::npos) {
        std::string sa = phase.substr(0, b);
        std::string sb = phase.substr(b + 1, phase.size() - b - 1);
        sb = decompose_bracket(sb, dlm);
        return sa + " " + dlm + " " + sb;
    }
    return phase;
}

std::vector<HTerm> decompose(std::string phase) {
    std::stringstream test(phase);
    std::string segment;
    std::vector<HTerm> seglist;
    while (getline(test, segment, ' ')) {

        if (segment.length() > 0) {
            if (segment[0] != ' ') {
                seglist.push_back(make_string(segment));
            }
        }
    }
    return seglist;
}

void teste_match() {
    std::vector<HTerm> lst = {make_string("book"), make_string("is"), make_string("small"), make_string("and"),
                              make_string("portable")};
    std::vector<HPred> predList;
    lst = decompose("a book is a thing");
    predList.push_back(std::make_shared<CPredAny>("Noum"));
    predList.push_back(std::make_shared<CPredAtom>("Verb", make_string("is")));
    predList.push_back(std::make_shared<CPredAny>("JJ"));
    MatchResult res = CMatch(lst, predList);
    std::string s = get_repr(res);
    printf("result:\n %s \n", s.c_str());
    return;
}

void teste_kinds() {
    FEnviromentBase *env = new FEnviromentBase();
    auto thing = make_kind(env, "thing");
    auto book = make_derivade_kind(env, "book", thing); //book is a kind of thing
    auto redbook = make_instance(env, "red book", book); //red book is a book
}

void teste_instances() {
}

void teste_properties1() {
    FEnviromentBase *env = new FEnviromentBase();
    auto thing = make_kind(env, "thing");
    // A thing can be hot or cold. A thing is usually cold.
    {
        auto thing_hot_cold = CObjectKindProperty("", thing, makeValueKindEnum(env, "", HValueKindString,
                                                                               {make_string_value("hot"),
                                                                                make_string_value("cold")}));
        auto thing_hot_cold_assertion = CKindPropertyAssert(thing_hot_cold, Usually_Value(make_string_value("cold")));
        assign_property(env, thing_hot_cold_assertion);
    }
    {
        // Temperature is a kind of value.The temperatures are cold, warm, and hot.
        auto temp_kind = makeValueKind(env, "Temperature");
        auto v_cold = makeValueInstance(env, "cold", temp_kind);
        auto v_warm = makeValueInstance(env, "warm", temp_kind);
        auto v_hot = makeValueInstance(env, "hot", temp_kind);
        auto potato = make_instance(env, "potato", thing);
        //The potato has a temperature called the heat.
        CInstanceProperty heat_potato_prop = CInstanceProperty("heat", potato, temp_kind);
    }
}

void teste_properties2() {
    FEnviromentBase *env = new FEnviromentBase();
    auto thing = make_kind(env, "thing");
    auto book = make_derivade_kind(env, "book", thing); //book is a kind of thing
    auto redbook = make_instance(env, "red book", book); //red book is a book
    auto colorsKind = makeValueKindEnum(env, "colors", HValueKindString, {make_string_value("red"), make_string_value(
            "blue")}); //Colors is a kind of value. The Colors are red and blue.
    CInstanceProperty colorProp = CInstanceProperty("color", redbook,
                                                    colorsKind); //  red book has a Colors called color.
    assign_property(env, colorProp);
    auto red_book_color = get_property(env, redbook, "color");
    HValue red_book_color_value = get_property_value(env, red_book_color);
    std::cout << toString(red_book_color_value) << std::endl;
    set_property_value(env, red_book_color, make_string_value("blue"));
    red_book_color_value = get_property_value(env, red_book_color);
    std::cout << toString(red_book_color_value) << std::endl;
    //set_property_value(env, red_book_color, make_string_value("green"));
    //red_book_color_value = get_property_value(env, red_book_color);
    //std::cout << toString(red_book_color_value) << std::endl;
}

void teste_properties3() {
    FEnviromentBase *env = new FEnviromentBase();
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
        auto deadEnd_riverSong = CObjectKindProperty("river sound", deadEnd, HValueKindText);
        //The river sound of a dead end is usually "a faint whispering of running water".
        auto deadEnd_riverSong_text = CKindPropertyAssert(deadEnd_riverSong, Usually_Value(
                make_text_value("a faint whispering of running water")));
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


void teste_properties4() {
    //Testa as codicoes de heranca de valores
    FEnviromentBase *env = new FEnviromentBase();
    auto thing = make_kind(env, "thing");
    auto book_kind = make_derivade_kind(env, "book", thing); //book  is a kind of thing
    auto book = make_instance(env, "red book", thing); //red book  is a book


    auto thing_color = CObjectKindProperty("color", thing, HValueKindString);
    auto thing_color_prop = CKindPropertyAssert(thing_color, Usually_Value(make_string_value("white")));
    assign_property(env, thing_color_prop);

    auto book_instance_color = get_property(env, book, "color");
    std::cout << "book color  : " << toString(get_property_value(env, book_instance_color)) << std::endl;
    set_property_value(env, book_instance_color, make_string_value("red"));
    std::cout << "book color  : " << toString(get_property_value(env, book_instance_color)) << std::endl;

}


void teste_kindValue1() {
    FEnviromentBase *env = new FEnviromentBase();
    auto thing = make_kind(env, "thing");
    //The lantern has a number called the brightness level.
    auto lantern = make_instance(env, "lantern", thing);
    auto lantern_brightnessLevel = CInstanceProperty("brightness level", lantern, HValueKindNumber);
    assign_property(env, lantern_brightnessLevel);
    //Brightness is a kind of value. The brightnesses are guttering, weak, radiant and blazing.
    HValueKind BrightnessKind = makeValueKindEnum(env, "Brightness", HValueKindString,
                                                  {make_string_value("guttering"), make_string_value("weak"),
                                                   make_string_value("radiant"), make_string_value("blazing")});
    //The lantern has a brightness called the flame strength.
    auto lantern_flameStrength = CInstanceProperty("flame strength", lantern, BrightnessKind);
    assign_property(env, lantern_flameStrength);
    //The flame strength of the lantern is blazing.
    auto lantern_flameStrength_prop = get_property(env, lantern, "flame strength");
    set_property_value(env, lantern_flameStrength_prop, make_string_value("blazing"));
    HValue lantern_flameStrength_value = get_property_value(env, lantern_flameStrength_prop);
    std::cout << "lantern flame strength == " << toString(lantern_flameStrength_value) << std::endl;
    auto lantern_brightnessLevel_prop = get_property(env, lantern, "brightness level");
    set_property_value(env, lantern_brightnessLevel_prop, make_number_value(1));
    HValue lantern_brightnessLevel_value = get_property_value(env, lantern_brightnessLevel_prop);
    std::cout << "lantern brightness level == " << toString(lantern_brightnessLevel_value) << std::endl;
}

void teste_variables1() {
    //The target is a number variable. The target is 23.
    FEnviromentBase *env = new FEnviromentBase();
    //The target is a number variable. The target is 23.
    auto target = make_variable(env, "target", HValueKindNumber);
    set_variable_value(env, target, make_number_value(23));
    HGenericValue val = get_variable_value(env, target);
    std::cout << "target is  == " << toString(val) << std::endl;
    //============================================================
    //Colour is a kind of value.The fashionable shade is a colour that varies.
    HValueKind Colour = makeValueKind(env, "Colour");
    auto fashionable_shade = make_variable(env, "fashionable_shade", Colour);
}

void teste_relations1() {
    FEnviromentBase *env = new FEnviromentBase();
    HObjectKind thing = make_kind(env, "thing");
    HObjectKind Person = make_kind(env, "person");
    //A door is a kind of thing.
    HObjectKind Door = make_derivade_kind(env, "door", thing);
    //A room is a kind.
    HObjectKind Room = make_kind(env, "room");
    //Meeting relates people to each other.
    auto Meeting = CRelationDescription("Meeting", make_relation_node("", Person), make_relation_node("", Person),
                                        true);
    add_relation_description(env, Meeting);
    // Marriage relates one person to another(called the spouse).
    auto Marriage = CRelationDescription("Marriage", make_relation_node("", Person),
                                         make_relation_node("spouse", Person));
    //Connection relates one thing to another (called the other party).
    auto Connection = CRelationDescription("Connection", make_relation_node("", thing),
                                           make_relation_node("other party", thing));
    auto LeadingThrough = CRelationDescription("Leading through", make_relation_node("other side", Room),
                                               make_relation_node_various("", Door), false);
    add_relation_description(env, LeadingThrough);

    {
        // Bob is a Person
        // John is a Person
        // Bob meeting John.
        HInstance bob = make_instance(env, "bob", Person);
        HInstance john = make_instance(env, "John", Person);
        HInstance paul = make_instance(env, "Paul", Person);
        auto Meeting_desc = get_relation_description(env, "Meeting");

        set_relation(env, Meeting_desc, bob, john);
        auto rel_instance = get_relation_to(env, Meeting_desc, bob);
        std::cout << " bob Meeting : " << toString(rel_instance) << std::endl;

        std::cout << " Now bob will   Meeting paul  " << std::endl;
        set_relation(env, Meeting_desc, bob, paul);

        auto rel_instance_2 = get_relation_from(env, Meeting_desc, john);
        std::cout << " john is Meeting by : " << toString(rel_instance_2) << " [ Nil ] " << std::endl;
    }
}

void teste_relations2() {

    // Testa relacoes multiplas

    FEnviromentBase *env = new FEnviromentBase();
    HObjectKind thing = make_kind(env, "thing");
    HObjectKind Person = make_kind(env, "person");

    auto Meeting = CRelationDescription("Meeting", make_relation_node_various("", Person),
                                        make_relation_node_various("", Person), true);
    add_relation_description(env, Meeting);

    HInstance bob = make_instance(env, "bob", Person);
    HInstance john = make_instance(env, "John", Person);
    HInstance paul = make_instance(env, "Paul", Person);
    HInstance mary = make_instance(env, "Mary", Person);
    auto Meeting_desc = get_relation_description(env, "Meeting");


    // testa relacoes simetricas

    set_relation(env, Meeting_desc, bob, john);
    set_relation(env, Meeting_desc, bob, paul);
    set_relation(env, Meeting_desc, bob, mary);
    set_relation(env, Meeting_desc, paul, mary);
    auto rel_instance_bob = get_relation_to(env, Meeting_desc, bob);
    std::cout << " Bob Meeting : " << toString(rel_instance_bob) << "[ john paul mary ]" << std::endl;

    auto rel_instance_mary = get_relation_to(env, Meeting_desc, mary);
    std::cout << " Mary Meeting : " << toString(rel_instance_mary) << "[ bob  paul  ]" << std::endl;

}

void teste_relations3() {
    FEnviromentBase *env = new FEnviromentBase();
    // A memory is a kind of thing.
    HObjectKind thing = make_kind(env, "thing");
    HObjectKind memory = make_derivade_kind(env, "memory", thing);
    // A memory can be retrieved or buried.A memory is usually buried.
    auto memory_prop = CObjectKindProperty("", memory, makeValueKindEnum(env, "", HValueKindString,
                                                                         {make_string_value("retrieved"),
                                                                          make_string_value("buried")}));
    auto memory_prop_assertion = CKindPropertyAssert(memory_prop, Usually_Value(make_string_value("buried")));
    assign_property(env, memory_prop_assertion);


    //Suggestion relates various things to one memory.
    auto Suggestion = CRelationDescription("Suggestion", make_relation_node_various("", thing),
                                           make_relation_node("", memory));
    add_relation_description(env, Suggestion);

    //The last day of high school is a memory.It is suggested by the tumbleweed.
    HInstance last_day_of_high_school = make_instance(env, "last day of high school", memory);
    HInstance tumbleweed = make_instance(env, "tumbleweed", thing);

    auto Suggestion_desc = get_relation_description(env, "Suggestion");
    set_relation(env, Suggestion_desc, tumbleweed, last_day_of_high_school);

    //Who sugest last_day_of_high_school ??

    auto thigs_to_sugest = get_relation_from(env, Suggestion_desc, last_day_of_high_school);
    std::cout << "Who sugest: " << toString(thigs_to_sugest) << " " << std::endl;
}

void testeParser();


int main() {
    testeParser();
    return 0;
    teste_1();
    teste_2();
    teste_match();
    teste_kinds();
    teste_instances();
    teste_properties1();
    teste_properties2();
    teste_properties3();
    teste_properties4();
    teste_kindValue1();
    teste_variables1();
    teste_relations1();
    teste_relations2();
    teste_relations3();
    return 0;
}

