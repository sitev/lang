#pragma once

#include "core.h"
#include "lexer.h"
#include <vector>

namespace lang {

	enum NodeType { ntNone, ntNumber, ntVarDef, ntVar, ntFuncDef, ntFunc, ntOperator, ntExpOper, ntExpression, ntCodeBlock, ntClass };

	class Node {
	public:
		NodeType nodeType;
		Node *parent = nullptr;
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
		bool isArray = false;
		VarDef();
	};

	class Var : public Node {
	public:
		VarDef *def = nullptr;
		Var();
	};

	class FuncDefParam {
	public:
		Str type;
		Str name;
	};

	class FuncDef : public Node {
	public:
		Str type;
		Str name;
		vector<FuncDefParam*> params;
		FuncDef();
	};

	class Func : public Node {
	public:
		FuncDef *def = nullptr;
		Func();
	};

	class Operator : public Node {
	public:
		Str name;
		Operator();
	};

	class ExpOper : public Node {
	public:
		Str name;
		int count; //count of operands
		ExpOper();
	};

	class Expression : public Node {
	public:
		bool isTZ = false;
		Expression();
	};

	class CodeBlock : public Node {
	public:
		Str source;
		CodeBlock();
	};

	class Class : public Node {
	public:
		Str name;
		Class *parent;
		Class();
	};

	class Parser {
	protected:
		Lexer *lexer;
		int pos, savePos, len;
		vector<Token> tokens;
	public:
		vector<Node*> nodes;
		Parser(Lexer *lexer);
		virtual Str run(Str s);
		virtual bool doMainCodeBlock() = 0;
		virtual Token getToken();
		virtual void savePosition();
		virtual void savePosition(int &savePos);
		virtual void rollback();
		virtual void rollback(int savePos);
		virtual void decPosition();
	};
	

}