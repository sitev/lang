#pragma once

#include "core.h"
#include "lexer.h"
#include <vector>

namespace lang {

	enum NodeType { ntNone, ntNumber, ntVarDef, ntVar, ntFuncDef, ntFunc, ntOper };

	class Node {
	public:
		NodeType nt;
		vector<Node*> nodes;
		Node();
	};

	class Number : public Node {
	public:
		int value;
		Number();
	};


	class VarDef : public Node {
	public:
		Str type;
		Str name;
		VarDef();
	};

	class Var : public Node {
	public:
		VarDef *def = nullptr;
		Var();
	};

	class FuncDefParamItem {
	public:
		Str type;
		Str name;
		FuncDefParamItem();
	};

	class FuncDefParams {
	protected:
		vector<FuncDefParamItem*> items;
	public:
		FuncDefParams();
	};

	class FuncDefBody {
	public:
		FuncDefBody();
	};

	class FuncDef : public Node {
	public:
		Str type;
		Str name;
		FuncDefParams *params = nullptr;
		FuncDefBody *body = nullptr;
		FuncDef();
	};

	class Func : public Node {
	public:
		FuncDef *def = nullptr;
		Func();
	};

	class Oper : public Node {
	public:
		Str name;
		int count;
		Oper();
	};

	class Parser {
	protected:
		Lexer *lexer;
		int pos, savePos, len;
		vector<Token> tokens;
		vector<Node*> nodes;
	public:
		Parser(Lexer *lexer);
		virtual Str run(Str s);
		virtual bool step() = 0;
		virtual Token getToken();
		virtual void savePosition();
		virtual void savePosition(int &savePos);
		virtual void rollback();
		virtual void rollback(int savePos);
	};
	

}