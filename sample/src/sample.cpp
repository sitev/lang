// sample.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

#include "core.h"
using namespace core;

#include "lang.h"
using namespace lang;

#pragma comment( lib, "core.lib" )
#pragma comment( lib, "lang" )

const char* src = R"(Str Lexer::run(Str s) {
		start(s);
	Str result;
	while (true) {
		Str lex = step();
		result += lex + "\r\n";
		if (pos >= len) break;
	}
	return result;
})";

int main()
{
	Lexer lexer;
	Str lexemes = lexer.run(src);
	cout << lexemes.to_string();
	getchar();

    return 0;
}

