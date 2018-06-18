#include <iostream>
using namespace std; 

#include "lang.h"

namespace lang {

	//----------   Node   --------------------------------------------------
	Node::Node() {
		nodeType = ntNone;
		uid = g_uid++;
		nodeCount = 0;
	}

	//----------   Number   --------------------------------------------------
	Number::Number() {
		nodeType = ntNumber;
	}

	//----------   StringNode   --------------------------------------------------
	StringNode::StringNode() {
		nodeType = ntString;
	}

	//----------   VarDef   -----------------------------------------------------
	VarDef::VarDef() {
		nodeType = ntVarDef;
	}
	
	bool VarDef::compare(Node *node) {
		if (node == nullptr) return false;
		VarDef *vd = (VarDef*)node;
		if (name != vd->name) return false;
		if (clss == nullptr) {
			if (type != vd->type) return false;
		}

		return true;
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

	//----------   Class   ----------------------------------------------------
	Class::Class() {
		nodeType = ntClass;
		parent = nullptr;
	}

	VarDef* Class::findVar(Str s) {
		int count = this->nodes.size();
		for (int i = 0; i < count; i++) {
			Node *nd = this->nodes[i];
			if (nd->nodeType == ntVarDef) {
				VarDef *vd = (VarDef*)nd;
				if (vd->name == s) return vd;
			}
		}
		return nullptr;
	}

	//----------   Construct   ----------------------------------------------------
	Construct::Construct() {
		nodeType = ntConstruct;
	}

	//----------   CodeInsertion   --------------------------------------------
	CodeInsertion::CodeInsertion() {
		nodeType = ntCodeInsertion;
	}

	//----------   Parser   -----------------------------------------------------
	Parser::Parser(Lexer *lexer, int nPass) {
		this->lexer = lexer;
		pos = savePos = len = 0;
		this->nPass = nPass;
	}

	Str Parser::run(Str s) {
		lexer->start(s);
		Str result = "";
		pos = savePos = len = 0;
		tokens.clear();
		nodes.clear();
		nodeCount = 0;

		for (int i = nPass; i > 0; i--) {
			if (nPass == 1) iPass = ptSingle;
			else iPass = (PassType)i;
			bool flag = doMainCodeBlock();
			pos = 0;
		}

		return result;
	}

	string nts[] = { "None", "Number", "String", "VarDef", "Var", "FuncDef", "Func", "Operator", "ExpOper", "Expression", "CodeBlock", "Class", "Construct", "CodeInsertion" };
	void Parser::out(Str fn) {
		//File *f = new File(fn.to_string(), "wb");

		cout << "Syntax tree" << endl;
		int count = nodes.size();
		for (int i = 0; i < count; i++) {
			Node *node = nodes[i];
			string ntName = nts[node->nodeType];
			cout << ntName;

			if (node->nodeType == ntClass) {
				Class *clss = (Class*)node;
				cout << " " << clss->name.to_string();
			}

			cout << endl;

			outSubNodes(node, 1);
		}
		//delete f;
	}

	void Parser::outSubNodes(Node *node, int level) {
		int count = node->nodes.size();
		for (int i = 0; i < count; i++) {
			Node *subNode = node->nodes[i];
			string ntName = nts[subNode->nodeType];

			for (int j = 0; j < level; j++) cout << " ";
			cout << ntName;

			if (subNode->nodeType == ntClass) {
				Class *clss = (Class*)subNode;
				cout << " " << clss->name.to_string();
			}
			else if (subNode->nodeType == ntVarDef) {
				VarDef *vd = (VarDef*)subNode;
				cout << " " << vd->name.to_string();
			}
			else if (subNode->nodeType == ntFuncDef) {
				FuncDef *fd = (FuncDef*)subNode;
				cout << " " << fd->name.to_string();
			}

			cout << endl;

			outSubNodes(subNode, level + 1);
		}
	}

	Token Parser::getToken() {
		if (pos < len) {
			Token token = tokens[pos];
			pos++;

			//cout << token.lexeme.to_string() << endl;
			return token;
		}

		LexemeType type = ltNone;
		Str lexeme = lexer->step(type);
		Token token;
		if (type == ltNone) token = lexer->getToken(lexeme);
		else {
			token.lexeme = lexeme;
			token.type = type;
		}
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