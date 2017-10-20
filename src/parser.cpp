#include <iostream>
using namespace std; 

#include "lang.h"

namespace lang {

	//----------   Node   --------------------------------------------------
	Node::Node() {
		nodeType = ntNone;
	}

	//----------   Number   --------------------------------------------------
	Number::Number() {
		nodeType = ntNumber;
	}

	//----------   VarDef   -----------------------------------------------------
	VarDef::VarDef() {
		nodeType = ntVarDef;
	}

	//----------   Var   -----------------------------------------------------
	Var::Var() {
		nodeType = ntVar;
	}

	//----------   FuncDef   ----------------------------------------------------
	FuncDef::FuncDef() {
		nodeType = ntFuncDef;
	}

	//----------   Func   ----------------------------------------------------
	Func::Func() {
		nodeType = ntFunc;
	}

	//----------   ExpOper   ----------------------------------------------------
	ExpOper::ExpOper() {
		nodeType = ntExpOper;
	}

	//----------   Operator   ----------------------------------------------------
	Operator::Operator() {
		nodeType = ntOperator;
	}

	//----------   Expression   ----------------------------------------------------
	Expression::Expression() {
		nodeType = ntExpression;
	}

	//----------   CodeBlock   ----------------------------------------------------
	CodeBlock::CodeBlock() {
		nodeType = ntCodeBlock;
	}

	//----------   Parser   -----------------------------------------------------
	Parser::Parser(Lexer *lexer) {
		this->lexer = lexer;
		pos = savePos = len = 0;
	}

	Str Parser::run(Str s) {
		lexer->start(s);
		Str result = "";
		pos = savePos = len = 0;
		tokens.clear();
		nodes.clear();

		bool flag = doMainCodeBlock();

		return result;
	}

	Token Parser::getToken() {
		if (pos < len) {
			Token token = tokens[pos];
			pos++;

			//cout << token.lexeme.to_string() << endl;
			return token;
		}

		Str lexeme = lexer->step();
		Token token = lexer->getToken(lexeme);
		tokens.push_back(token);
		pos++;
		len++;
		//cout << token.lexeme.to_string() << " " << token.type << endl;
		return token;
	}

	void Parser::savePosition() {
		savePos = pos;
	}
	void Parser::savePosition(int &savePos) {
		savePos = pos;
	}
	void Parser::rollback() {
		pos = savePos;
	}
	void Parser::rollback(int savePos) {
		pos = savePos;
	}

	void Parser::decPosition() {
		if (pos > 0) pos--;
	}
}