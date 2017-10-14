#include "lang.h"

namespace lang {

	Generator::Generator(Parser *parser) {
		this->parser = parser;
	}


	Generator::~Generator() {
	}

	Str Generator::run() {
		int count = parser->nodes.size();
		for (int i = 0; i < count; i++) {
			Node *node = parser->nodes[i];
			generate(node);
		}

		return "";
	}

	void Generator::generate(Node *node) {
		if (node->type == ntCodeBlock) {
			cout << "{" << endl;
			
			int count = node->nodes.size();
			for (int i = 0; i < count; i++) {
				Node *node = parser->nodes[i];
				generate(node);
			}

			cout << "}" << endl;
		}
	}
}