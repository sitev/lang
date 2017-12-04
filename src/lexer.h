#pragma once

namespace lang {

	enum LexerMode { lmNormal, lmRemmark, lmRemmark2, lmString, lmCodeInsertion };
	enum LexemeType { ltNone, ltIdentifier, ltNumber, ltSpecial, ltString, ltCodeInsertion, ltError, ltEof };

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
		int tmp;
		Lexer();
		~Lexer();

		virtual void start(Str s);
		virtual Str step(LexemeType &type);

		virtual Str run(Str s);

		virtual bool isLetter(char a);
		virtual bool isNumeral(char a);
		virtual bool isSpecial(char a);

		virtual bool isIdentifier(Str lexeme);
		virtual bool isNumber(Str lexeme);
		virtual bool isSpecial(Str lexeme);
		virtual bool isString(Str lexeme);
		virtual LexemeType getLexemeType(Str lexeme);

		virtual Token getToken(Str lexeme);
	};
}
