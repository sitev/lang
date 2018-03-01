#include "lang.h"

namespace lang {

	Generator::Generator(Parser *parser, Str fn) {
		this->parser = parser;
		this->fn = fn;
	}


	Generator::~Generator() {
	}

	Str Generator::run() {
		target = getHeader();
		int count = parser->nodes.size();
		//s += "//count nodes = " + to_string(count) + "\r\n";
		for (int i = 0; i < count; i++) {
			Node *node = parser->nodes[i];
			target += generate(node);
		}
		target += getFooter();

		saveFiles();

		return "";
	}

	Str Generator::generate(Node *node, bool isExpNotCR) {
		switch (node->nodeType) {
		case ntNumber: return genNumber(node);
		case ntString: return genString(node);
		case ntVarDef: return genVarDef(node);
		case ntVar: return genVar(node);
		case ntFuncDef: return genFuncDef(node);
		case ntFunc: return genFunc(node);
		case ntOperator: return genOperator(node);
		case ntExpOper: return genExpOper(node);
		case ntExpression: return genExpression(node, isExpNotCR);
		case ntCodeBlock: return genCodeBlock(node);
		case ntClass: return genClass(node);
		case ntConstruct: return genConstruct(node);
		case ntCodeInsertion: return genCodeInsertion(node);
		}

		return "";
	}

	Str Generator::getHeader() {
		return "";
	}

	Str Generator::getFooter() {
		return "";
	}

	Str Generator::genNumber(Node *node) {
		Str s = "number ";
		Number *num = (Number*)node;
		s += num->value + " ";
		return s;
	}

	Str Generator::genString(Node *node) {
		Str s = "string ";
		StringNode *sn = (StringNode*)node;
		s += sn->value;
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

	Str Generator::genConstruct(Node *node) {
		return "construct ";
	}

	Str Generator::genCodeInsertion(Node *node) {
		return "// CodeInsertion\n";
	}

	Str Generator::getTab(int count, int value) {
		Str s;// = "/*" + to_string(value) + "*/";
		for (int i = 0; i < count; i++) {
			s += "\t";
		}
		return s;
	}

	void Generator::saveFiles() {
		int count = ext.size();
		if (count < 1) return;
		int count2 = lstTarget.size();
		if (count != count2 + 1) return;

		File *f = new File((fn + "." + ext[0]).to_string());
		f->write((void*)target.to_string().c_str(), target.length());
		delete f;

		for (int i = 0; i < count2; i++) {
			Str *t = lstTarget[i];
			File *f = new File((fn + "." + ext[i + 1]).to_string());
			f->write((void*)t->to_string().c_str(), t->length());
			delete f;
		}
	}
}