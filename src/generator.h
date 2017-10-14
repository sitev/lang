#pragma once

namespace lang {

	class Generator {
	public:
		Generator(Parser *parser);
		~Generator();

		virtual Str run();
		virtual void generate(Node *node);
	protected:
		Parser *parser;
	};

}