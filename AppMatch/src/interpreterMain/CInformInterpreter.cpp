//
// Created by eraldo on 19/06/2018.
//
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include <store_tp.hpp>
#include <interpreter/CBlockInterpreterRuntime.hpp>
#include "sharedCast.hpp"
#include "save_ctx.hpp"


using namespace std;

using namespace CBlocking;


std::string load_file_i(string filename)
{
    FILE *f = fopen(filename.c_str(), "rb");
    if (f == nullptr)
    {
        printf("Error , file not found \n");
        return std::string("");
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);

    char *a = (char*)malloc(fsize + 1);
    fread(a, fsize, 1, f);
    fclose(f);

    a[fsize] = 0;
    return std::string(a);
}




class InterpreterFlags
{
public:
    std::map<std::string,bool> flags;
    std::map<std::string, string> options;
    std::map<std::string, string> flags_desc;
    std::map<std::string, string> options_desc;

    std::vector<std::string> files;
    InterpreterFlags()
    {
        options_desc["output"] = "Place output in file ";
        flags_desc["v"] = "Print the commands executed to run the interpreter";
        options["output"] = "output.txt";
    }

    void setFlag(string name, bool value)
    {
        flags[name] = value;
    }

    void setOption(string name, string value)
    {
        options[name] = value;
    }

    void printDesc()
    {
        for (auto kv : flags_desc)	printf("-%s  : %s \n", kv.first.c_str(), kv.second.c_str());
        for (auto kv : options_desc)	printf("-%s  : %s \n", kv.first.c_str(), kv.second.c_str());
    }
};


InterpreterFlags process_options(std::vector<std::string> va)
{
    InterpreterFlags iflags;
    std::vector<std::string> ret;
    size_t n = va.size();

    for(int i =0 ; i< n;++i)
    {
        if( va[i][0] != '-')
        {
            iflags.files.push_back(va[i]);
        }
        if (va[i] == "-o")
        {
            if (i < n - 1)
            {
                iflags.setOption("output", va[i + 1]);
                i++;
            }
            else
            {
                fprintf(stderr, "missing output argument\n");
                return InterpreterFlags();
            }
        }
    }
    return iflags;

}


string get_user_input(string prompt)
{

	char c;

	printf("%s", prompt.c_str());
	char tmp[1024];
	scanf("%[^\n]", tmp);
	string str = tmp;
    while ((c = fgetc(stdin)) != '\n' && c != EOF); /* Flush stdin */
	return str;

}

 


int main(int argc, char **argv)
{
    if (argc < 1 )
    {
        printf("no input files \n"); return 0;
    }

    std::vector<std::string> vargs;
    for(int i = 1 ; i< argc ;++i)
    {
        vargs.push_back(std::string(argv[i]));
        printf("%s.\n", vargs.back().c_str());
    }

    //remove as opcoes .. deve restar apenas os filenames
    InterpreterFlags iflags = process_options(vargs);



    if (!iflags.files.empty())
    {
        printf("begin Loading\n");
        auto bytecodeContents = load_file_i(iflags.files.front());
        printf("end Loading\n");

        LoadContext lx= LoadContext(bytecodeContents);
        printf("begin Parse\n");
        auto h = load_file(&lx);
		
        printf("end Parse\n");
		if (h == nullptr)
		{
			printf("Error on load file\n");
			return 2;
		}
		
       h->dump(" ");

		LanguageEn english_proxy ; //define basic interpreter functions to english language
        Interpreter::HBlockInterpreter interpreter = std::make_shared<Interpreter::CBlockInterpreter>(&english_proxy);

        interpreter->execute_init(h);
        interpreter->start();
		while (true)
		{
			if (interpreter->is_runnig() ==false ) break;
			string prompt = interpreter->prompt();

			string user_typed = get_user_input(prompt);
			interpreter->feed(user_typed);
		}
    }
    return 0;
}
