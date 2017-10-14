#include "lang.h"

namespace lang {

	//----------   Node   --------------------------------------------------
	Node::Node() {
		nt = ntNone;
	}

	//----------   Number   --------------------------------------------------
	Number::Number() {
		nt = ntNumber;
	}

	//----------   VarDef   -----------------------------------------------------
	VarDef::VarDef() {
		nt = ntVarDef;
	}

	//----------   Var   -----------------------------------------------------
	Var::Var() {
		nt = ntVar;
	}

	//----------   FuncDefParamItem   -------------------------------------------
	FuncDefParamItem::FuncDefParamItem() {
	}

	//----------   FuncDefParams   ----------------------------------------------
	FuncDefParams::FuncDefParams() {
	}

	//----------   FuncDefBody   ------------------------------------------------
	FuncDefBody::FuncDefBody() {
	}

	//----------   FuncDef   ----------------------------------------------------
	FuncDef::FuncDef() {
		nt = ntFuncDef;
	}

	//----------   Func   ----------------------------------------------------
	Func::Func() {
		nt = ntFunc;
	}

	//----------   Oper   ----------------------------------------------------
	Oper::Oper() {
		nt = ntOper;
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
			return token;
		}

		Str lexeme = lexer->step();
		Token token = lexer->getToken(lexeme);
		tokens.push_back(token);
		pos++;
		len++;
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
}