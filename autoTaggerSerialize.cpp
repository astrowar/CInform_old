
extern "C" {
#include <clang-c/Index.h>
}

#include <memory>
#include "stdafx.h"
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <direct.h>

enum CXChildVisitResult visit(CXCursor cursor, CXCursor parent)
{
	CXFile file;
	unsigned int line, column, offset;
	clang_getInstantiationLocation(
		clang_getCursorLocation(cursor),
		&file, &line, &column, &offset);
	CXCursorKind kind = clang_getCursorKind(cursor);

	if (kind == CXCursorKind::CXCursor_ClassDecl)
	{
		CXString s =  clang_getCursorDisplayName(cursor);
		const char *c = clang_getCString(s);
		

		CXType type = clang_getCursorType(cursor);
		CXString str_type = clang_getTypeSpelling(type);
		const char *c_type = clang_getCString(str_type);


		std::cout << "CXX_DECL " << line << std::string(c) << " Type:" << std::string(c_type) << std::endl;
	}

	if (kind == CXCursorKind::CXCursor_FieldDecl)
	{
		CXString s = clang_getCursorDisplayName(cursor);
		const char *c = clang_getCString(s);
		 
		CXType type = clang_getCursorType(cursor);
		CXString str_type = clang_getTypeSpelling(type);
		const char *c_type = clang_getCString(str_type);

		std::cout << "CXX_FIELD " << line << " [" << std::string(c) << " ]" << " Type:" << std::string(c_type) << std::endl;
	}

	{
		CXType type = clang_getCursorType(cursor);
		CXString str_type = clang_getTypeSpelling(type);
		CXString s = clang_getCursorDisplayName(cursor);
		const char *c = clang_getCString(s);
		const char *c_type = clang_getCString(str_type);
		//std::cout <<"@ " << line << std::string(c) <<" Type:" << std::string(c_type) <<  std::endl;
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
	return visit(cursor, parent);
}


int main()
{
	//const char* dbFilename = argv[1];
	//const char* indexFilename = argv[2];

	// _chdir( "C:\\dev\\repositorio\\CMatchIteractiveFic\\AppMatch\\" );

	const char* sourceFilename = "BlockInterpreter.hpp";

	char* options[] = { "  -std=c++11 -stdlib=libc++   -I\"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\include\""};

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

	clang_visitChildren(
		clang_getTranslationUnitCursor(tu),
		&visitorFunction,
		nullptr);

	std::string k  ;
	//k << std::cin;
	return 0;
}

