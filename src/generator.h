#pragma once

namespace lang {

	class Generator {
	public:
		Generator(Parser *parser);
		~Generator();

		virtual Str run();
		virtual bool generate(Node *node);
	protected:
		Parser *parser;
		virtual bool genNumber(Node *node);
		virtual bool genVarDef(Node *node);
		virtual bool genVar(Node *node);
		virtual bool genFuncDef(Node *node);
		virtual bool genFunc(Node *node);
		virtual bool genOperator(Node *node);
		virtual bool genExpression(Node *node);
		virtual bool genCodeBlock(Node *node);
	};

}