#pragma once

namespace lang {

	class Generator {
	public:
		Generator(Parser *parser);
		~Generator();

		virtual Str run();
		virtual Str generate(Node *node);
	protected:
		Parser *parser;
		virtual Str genNumber(Node *node);
		virtual Str genVarDef(Node *node);
		virtual Str genVar(Node *node);
		virtual Str genFuncDef(Node *node);
		virtual Str genFunc(Node *node);
		virtual Str genOperator(Node *node);
		virtual Str genExpression(Node *node);
		virtual Str genCodeBlock(Node *node);
	};

}