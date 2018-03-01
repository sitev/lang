#pragma once

#include "core.h"
#include "lexer.h"
#include <vector>

namespace lang {

	enum NodeType { ntNone, ntNumber, ntString, ntVarDef, ntVar, ntFuncDef, ntFunc, ntOperator, ntExpOper, ntExpression, ntCodeBlock, ntClass, ntConstruct, ntCodeInsertion };

	static int g_uid = 1;
	class Node {
	public:
		int uid;
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

	class StringNode : public Node {
	public:
		Str value;
		StringNode();
	};

	class Class;
	class VarDef : public Node {
	public:
		Class *owner = nullptr;
		Class *clss = nullptr; // если (clss == nullptr) то переменная имеет стандартный тип, иначе она является объектом класса clss
		bool isRef = false;
		Str type;
		Str name;
		bool isArray = false;
		VarDef();
	};

	class Var : public Node {
	public:
		VarDef *def = nullptr;
		//vector<FuncDefParam*> params;
		Var();
	};

	class FuncDefParam : public VarDef {
	};

	class FuncDef : public Node {
	public:
		Class *owner = nullptr;
		bool isConstruct = false;
		Class *clss = nullptr;
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
		virtual VarDef* findVar(Str s);
	};

	class Construct : public Node {
	public:
		Class *clss = nullptr;
		Construct();
	};

	class CodeInsertion : public Node {
	public:
		CodeInsertion();
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
		virtual void out(Str fn);
		virtual void outSubNodes(Node *node, int level);


		virtual bool doMainCodeBlock() = 0;
		virtual Token getToken();
		virtual void savePosition();
		virtual void savePosition(int &savePos);
		virtual void rollback();
		virtual void rollback(int savePos);
		virtual void decPosition();
	};
	

}