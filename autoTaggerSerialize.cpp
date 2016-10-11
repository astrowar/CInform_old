
extern "C" {
#include <clang-c/Index.h>
}

#include <memory>

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

class ClassDefinition
{
public:
    std::string name;
    std::string base;
    std::string contructor;
    std::vector<std::string> fields; //campos da classe
};


std::string toStdString(CXString cxStr)
{
    const char* str =  clang_getCString(cxStr);
    if (str != NULL)
    {
        std::string stdString(str);
        //clang().disposeString(cxStr);
        return stdString;
    }
    else
    {
        return std::string();
    }
}


std::string toStdString(CXCursor cursor)
{
    return toStdString(clang_getCursorSpelling(cursor));
}

std::string toStdString(CXCursorKind kind)
{
    return toStdString(clang_getCursorKindSpelling(kind));
}

std::string toStdString(CXToken token, CXTranslationUnit tu)
{
    return toStdString(clang_getTokenSpelling(tu, token));
}

std::string toStdString(CXType type)
{
    return toStdString(clang_getTypeSpelling(type));
}


enum CXChildVisitResult visit(CXCursor cursor, CXCursor parent, std::vector<ClassDefinition>* cdefs)
{
	CXFile file;
	unsigned int line, column, offset;
	clang_getInstantiationLocation(
		clang_getCursorLocation(cursor),
		&file, &line, &column, &offset);
	CXCursorKind kind = clang_getCursorKind(cursor);


    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);
    CXToken* tokens = 0;
                 unsigned int numTokens;
                 clang_tokenize(tu, range, &tokens, &numTokens);

                 CXCursor cursors[numTokens];
                 clang_annotateTokens(tu, tokens, numTokens, cursors);


	if (kind == CXCursorKind::CXCursor_ClassDecl) {
        CXString s = clang_getCursorDisplayName(cursor);
        const char *c = clang_getCString(s);


        CXType type = clang_getCursorType(cursor);
        CXString str_type = clang_getTypeSpelling(type);
        const char *c_type = clang_getCString(str_type);


        std::size_t found = std::string(c).find("CBlock");
        if (found != std::string::npos) {

            std::cout << "CXX_DECL " << line << " " << std::string(c) << " Type:" << std::string(c_type) << std::endl;
        }
            cdefs->push_back(ClassDefinition());
            cdefs->back().name = std::string(c);

            for (unsigned int idx = 0; idx < numTokens; ++idx) {
                if (cursors[idx].kind == CXCursorKind::CXCursor_CXXBaseSpecifier) {
                    idx++;
                    if (cursors[idx].kind == CXCursorKind::CXCursor_TypeRef) {
                        CXType type = clang_getCursorType(cursors[idx]);
                        std::string cursorSpelling = toStdString(cursors[idx]);
                        std::string tokenSpelling = toStdString(tokens[idx], tu);
                        std::string typeSpelling = toStdString(type);
                        std::cout << "  " << tokenSpelling << std::endl;


                        cdefs->back().base = tokenSpelling;

                        // std::cout << "  " << tokenSpelling << " " << cursorSpelling << " "
                        //          << toStdString(cursors[idx].kind) << "  " << typeSpelling;
                        break;
                    }
                }
            

        }
    }

    if (kind == CXCursorKind::CXCursor_Constructor )
    {
        CXString s =  clang_getCursorDisplayName(cursor);
        const char *c = clang_getCString(s);


        CXType type = clang_getCursorType(cursor);
        CXString str_type = clang_getTypeSpelling(type);
        const char *c_type = clang_getCString(str_type);
        std::size_t found = std::string(c).find("CBlock");
        if (found != std::string::npos) {

            std::cout << "CXX_CONSTR " << line << " " << std::string(c) << " Type:" << std::string(c_type) << std::endl;
        }
    }


	if (kind == CXCursorKind::CXCursor_FieldDecl) {
        CXString s = clang_getCursorDisplayName(cursor);
        const char *c = clang_getCString(s);

        CXType type = clang_getCursorType(cursor);
        CXString str_type = clang_getTypeSpelling(type);
        const char *c_type = clang_getCString(str_type);

        std::size_t found = std::string(c).find("CBlock");
        if (found != std::string::npos) {


            std::cout << "CXX_FIELD " << line << " [" << std::string(c) << " ]" << " Type:" << std::string(c_type)
                      << std::endl;
        }
            if (cdefs->empty() == false) {
                cdefs->back().fields.push_back(std::string(c));
            }

    }

	{
		CXType type = clang_getCursorType(cursor);
		CXString str_type = clang_getTypeSpelling(type);
		CXString s = clang_getCursorDisplayName(cursor);
		const char *c = clang_getCString(s);
		const char *c_type = clang_getCString(str_type);


		//std::cout << kind << "@ " << line << std::string(c) <<" Type:" << std::string(c_type) <<  std::endl;
	}
	return CXChildVisit_Recurse;


}

enum CXChildVisitResult visitorFunction(
	CXCursor cursor,
	CXCursor parent,
	CXClientData clientData)
{
	//IVisitor* visitor = (IVisitor*)clientData;
	//return visitor->visit(cursor, parent);
    std::vector<ClassDefinition>* cdefs = (std::vector<ClassDefinition>*)clientData;
	return visit(cursor, parent,cdefs);
}


int main()
{
	//const char* dbFilename = argv[1];
	//const char* indexFilename = argv[2];

	// _chdir( "C:\\dev\\repositorio\\CMatchIteractiveFic\\AppMatch\\" );

	const char* sourceFilename = "BlockInterpreter.hpp";

	//char* options[] = { "  -std=c++11 -stdlib=libc++   -I\"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\include\""};

	char* options[] = { "  -std=c++11 -stdlib=libc++   -I/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/ "};


	// Set up the clang translation unit
	CXIndex cxindex = clang_createIndex(0, 1);
	CXTranslationUnit tu;
		
	CXErrorCode err =  clang_parseTranslationUnit2(
		cxindex, sourceFilename,
		options,
		0, // Skip over dbFilename and indexFilename
		0, 0,
		CXTranslationUnit_Incomplete , &tu);

	if (!tu) {
		
		fputs("error: failed to compile input\n", stderr);
		exit(EXIT_FAILURE);
	}

    std::vector<ClassDefinition> c_defs   ;


    CXClientData cxdata  =  ( &c_defs ) ;

	clang_visitChildren(
		clang_getTranslationUnitCursor(tu),
		&visitorFunction,
        cxdata);

	std::string k  ;
	//k << std::cin;
    for(auto &c : c_defs)
    {
        std::cout << c.name << "  ";
        for(auto &field : c.fields)
        {
            std::cout << field << "  ";
        }
        std::cout <<   "\n";
    }
	return 0;
}

