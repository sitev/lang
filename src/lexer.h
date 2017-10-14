#pragma once

namespace lang {

	enum LexerMode { lmNormal, lmRemmark, lmRemmark2, lmString };
	enum LexemeType { ltIdentifier, ltNumber, ltSpecial, ltError, ltEnd };

	class Token {
	public:
		Str lexeme;
		LexemeType type;
	};

	class Lexer {
	protected:
		Str s;
		int len = 0, pos = 0;
		Str letters, numerals, specials;
		
		LexerMode mode;
		bool isSlesh, isMul, isCR;
	public:
		Lexer();
		~Lexer();

		virtual void start(Str s);
		virtual Str step();

		virtual Str run(Str s);

		virtual bool isLetter(char a);
		virtual bool isNumeral(char a);
		virtual bool isSpecial(char a);

		virtual bool isIdentifier(Str lexema);
		virtual bool isNumber(Str lexema);
		virtual bool isSpecial(Str lexema);
		virtual LexemeType getLexemeType(Str lexema);

		virtual Token getToken(Str lexema);
	};
}
