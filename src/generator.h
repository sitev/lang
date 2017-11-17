#pragma once

namespace lang {

	//Test Generator
	class Generator {
	public:
		Generator(Parser *parser);
		~Generator();

		virtual Str run();
		virtual Str generate(Node *node, bool isExpNotCR = false);
	protected:
		Parser *parser;
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

		virtual Str getTab(int count);
	};

}