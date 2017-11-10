#include "lang.h"

namespace lang {

	Generator::Generator(Parser *parser) {
		this->parser = parser;
	}


	Generator::~Generator() {
	}

	Str Generator::run() {
		Str s = "";
		int count = parser->nodes.size();
		//s += "//count nodes = " + to_string(count) + "\r\n";
		for (int i = 0; i < count; i++) {
			Node *node = parser->nodes[i];
			s += generate(node);
		}

		return s;
	}

	Str Generator::generate(Node *node, bool isExpNotCR) {
		switch (node->nodeType) {
		case ntNumber: return genNumber(node);
		case ntVarDef: return genVarDef(node);
		case ntVar: return genVar(node);
		case ntFuncDef: return genFuncDef(node);
		case ntFunc: return genFunc(node);
		case ntOperator: return genOperator(node);
		case ntExpOper: return genExpOper(node);
		case ntExpression: return genExpression(node, isExpNotCR);
		case ntCodeBlock: return genCodeBlock(node);
		case ntClass: return genClass(node);
		}

		return "";
	}

	Str Generator::genNumber(Node *node) {
		Str s = "number ";
		Number *num = (Number*)node;
		s += num->value + " ";
		return s;
	}

	Str Generator::genVarDef(Node *node) {
		Str s = "var_def ";
		VarDef *vd = (VarDef*)node;
		s += vd->type + " " + vd->name + ";\r\n";
		return s;
	}

	Str Generator::genVar(Node *node) {
		Str s = "var ";
		Var *var = (Var*)node;

		s += var->def->name + " ";
		return s;
	}

	Str Generator::genFuncDef(Node *node) {
		Str s = "func_def ";
		FuncDef *fd = (FuncDef*)node;
		s += fd->type + " " + fd->name + "(";

		int count = fd->params.size();
		for (int i = 0; i < count; i++) {
			FuncDefParam *fdp = (FuncDefParam*)fd->params[i];
			s += fdp->type + " " + fdp->name;
			if (i + 1 != count) s += ", ";
		}

		s += ")\r\n";

		count = fd->nodes.size();
		for (int i = 0; i < count; i++) {
			Node *nd = fd->nodes[i];
			generate(nd);
		}

		return s;
	}

	Str Generator::genFunc(Node *node) {
		Str s = "func ";
		Func *func = (Func*)node;
		s += func->def->type + " " + func->def->name + "();\r\n";

		return s;
	}
	
	Str Generator::genExpOper(Node *node) {
		Str s = "operator ";
		ExpOper *oper = (ExpOper*)node;
		s += oper->name + " ";
		return s;
	}

	Str Generator::genOperator(Node *node) {
		Str s = "operator ";
		Operator *oper = (Operator*)node;
		s += oper->name + " ";
		return s;
	}

	Str Generator::genExpression(Node *node, bool isExpNotCR) {
		Str s = "expression ";
		Expression *exp = (Expression*)node;

		int count = node->nodes.size();
		s += "/" + (Str)count + "/ ";
		for (int i = 0; i < count; i++) {
			Node *nd = node->nodes[i];
			generate(nd);
		}

		//s += ";\r\n";
		return s;
	}

	Str Generator::genCodeBlock(Node *node) {
		Str s = "code_block {\r\n";

		int count = node->nodes.size();
		for (int i = 0; i < count; i++) {
			Node *nd = node->nodes[i];
			generate(nd);
		}

		s += "}\r\n";
		return s;
	}

	Str Generator::genClass(Node *node) {
		Str s = "class {\r\n";

		int count = node->nodes.size();
		for (int i = 0; i < count; i++) {
			Node *nd = node->nodes[i];
			generate(nd);
		}

		s += "}\r\n";
		return s;
	}

	Str Generator::getTab(int count) {
		Str s = "";
		for (int i = 0; i < count; i++) {
			s += "\t";
		}
		return s;
	}
}