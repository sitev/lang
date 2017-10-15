#include "lang.h"

namespace lang {

	Generator::Generator(Parser *parser) {
		this->parser = parser;
	}


	Generator::~Generator() {
	}

	Str Generator::run() {
		int count = parser->nodes.size();
		cout << "count = " << count << endl;
		for (int i = 0; i < count; i++) {
			Node *node = parser->nodes[i];
			generate(node);
		}

		return "";
	}

	bool Generator::generate(Node *node) {
		switch (node->nodeType) {
		case ntNumber: return genNumber(node);
		case ntVarDef: return genVarDef(node);
		case ntVar: return genVar(node);
		case ntFuncDef: return genFuncDef(node);
		case ntFunc: return genFunc(node);
		case ntOperator: return genOperator(node);
		case ntExpression: return genExpression(node);
		case ntCodeBlock: return genCodeBlock(node);
		}

		return false;
	}

	bool Generator::genNumber(Node *node) {
		cout << "number ";
		Number *num = (Number*)node;
		cout << num->value << "| ";
		return true;
	}

	bool Generator::genVarDef(Node *node) {
		cout << "var_def ";
		VarDef *vd = (VarDef*)node;
		cout << vd->type.to_string() << " " << vd->name.to_string();

		cout << ";" << endl;
		return true;
	}

	bool Generator::genVar(Node *node) {
		cout << "var ";
		Var *var = (Var*)node;

		cout << var->def->name.to_string() << " ";
		return true;
	}

	bool Generator::genFuncDef(Node *node) {
		return true;
	}

	bool Generator::genFunc(Node *node) {
		return true;
	}
	
	bool Generator::genOperator(Node *node) {
		cout << "operator ";
		Operator *oper = (Operator*)node;
		cout << oper->name.to_string() << " " << oper->count << "| ";
		return true;
	}

	bool Generator::genExpression(Node *node) {
		cout << "exspression ";
		Expression *exp = (Expression*)node;

		int count = node->nodes.size();
		cout << "/" << count << "/ ";
		for (int i = 0; i < count; i++) {
			Node *nd = node->nodes[i];
			generate(nd);
		}

		cout << ";" << endl;
		return true;
	}

	bool Generator::genCodeBlock(Node *node) {
		cout << "code_block {" << endl;

		int count = node->nodes.size();
		for (int i = 0; i < count; i++) {
			Node *nd = node->nodes[i];
			generate(nd);
		}

		cout << "}" << endl;
		return true;
	}
}