#pragma once

namespace lang {

	//Test Generator
	class Generator {
	public:
		Generator(Parser *parser, Str fn);
		~Generator();

		virtual Str run();
		virtual Str generate(Node *node, bool isExpNotCR = false);

	protected:
		Str fn;
		vector<Str> ext;
		Parser *parser;
		Str target;
		vector<Str*> lstTarget; // additional targets

		virtual Str getHeader();
		virtual Str genNumber(Node *node);
		virtual Str genString(Node *node);
		virtual Str genVarDef(Node *node);
		virtual Str genVar(Node *node);
		virtual Str genFuncDef(Node *node);
		virtual Str genFunc(Node *node);
		virtual Str genOperator(Node *node);
		virtual Str genExpOper(Node *node);
		virtual Str genExpression(Node *node, bool isExpNotCR = false);
		virtual Str genCodeBlock(Node *node);
		virtual Str genClass(Node *node);
		virtual Str genConstruct(Node *node);
		virtual Str genCodeInsertion(Node *node);

		virtual Str getTab(int count);

		virtual void saveFiles();

	};

}