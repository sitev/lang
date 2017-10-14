#include "lang.h"

namespace lang {

	Str oper[] = { "=", "+", "-", "*", "/" };

	Lexer::Lexer() {
		letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
		numerals = "0123456789";
		specials = ";(){}=+-*/%";
		mode = lmNormal;
		isSlesh = isMul = isCR = false;
	}

	Lexer::~Lexer() {
	}

	void Lexer::start(Str s) {
		this->s = s;
		len = s.length();
		pos = 0;
	}

	Str Lexer::step() {
		Str a;
		int len = s.length();
		while (pos < len) {
			uchar c = s[pos];

			if (c == 13) isCR = true; else isCR = false;
			if (c <= 32) c = 32;

			if (mode == lmNormal) {
				if (a.length() > 0 && !isLetter(c) && !isNumeral(c) && !isSlesh && !isMul) return a;
				pos++;
				if (c != 32)
					a = a + (char)c;

				if (c == '\"') {
					mode = lmString;
					continue;
				}
				if (c == '*' && isSlesh) {
					mode = lmRemmark;
					continue;
				}
				if (c == '/' && isSlesh) {
					mode = lmRemmark2;
					continue;
				}
				if (c == '/') isSlesh = true; else isSlesh = false;

				if (a.length() > 0 && !isLetter(c) && !isNumeral(c) && !isSlesh && !isMul) return a;
			}
			else if (mode == lmRemmark) {
				pos++;
				a = a + (char)c;
				if (c == '/' && isMul) {
					mode = lmNormal;
					return a;
				}
				if (c == '*') isMul = true; else isMul = false;
			}
			else if (mode == lmRemmark2) {
				pos++;
				a = a + (char)c;
				if (isCR) {
					mode = lmNormal;
					return a;
				}
				if (c == '*') isMul = true; else isMul = false;
			}
			else if (mode == lmString) {
				pos++;
				a = a + (char)c;
				if (c == '\"') {
					mode = lmNormal;
					return a;
				}
			}
		}
		return a;
	}

	Str Lexer::run(Str s) {
		start(s);
		Str result;
		while (true) {
			Str lex = step();
			result += lex + "\r\n";
			if (pos >= len) break;
		}
		return result;
	}

	bool Lexer::isLetter(char a) {
		for (int i = 0; i < letters.length(); i++) {
			if (letters[i] == a) return true;
		}
		return false;
	}

	bool Lexer::isNumeral(char a) {
		for (int i = 0; i < numerals.length(); i++) {
			if (numerals[i] == a) return true;
		}
		return false;
	}

	bool Lexer::isSpecial(char a) {
		for (int i = 0; i < specials.length(); i++) {
			if (specials[i] == a) return true;
		}
		return false;
	}

	bool Lexer::isIdentifier(Str lexeme) {
		int len = lexeme.length();
		if (len == 0) return false;
		
		if (!isLetter(lexeme[0])) return false;
		
		for (int i = 1; i < len; i++) {
			if (!isLetter(lexeme[i]) && !isNumber(lexeme[i])) return false;
		}

		return true;
	}

	bool Lexer::isNumber(Str lexeme) {
		int len = lexeme.length();
		if (len == 0) return false;

		for (int i = 1; i < len; i++) {
			if (!isNumber(lexeme[i])) return false;
		}
		return true;
	}

	bool Lexer::isSpecial(Str lexeme) {
		int len = lexeme.length();
		if (len == 0) return false;

		for (int i = 1; i < len; i++) {
			if (!isSpecial(lexeme[i])) return false;
		}
		return true;
	}

	LexemeType Lexer::getLexemeType(Str lexeme) {
		if (isIdentifier(lexeme)) return ltIdentifier;
		else if (isNumber(lexeme)) return ltNumber;
		else if (isSpecial(lexeme)) return ltSpecial;
		else if (lexeme == "") return ltEnd;

		return ltError;
	}

	Token Lexer::getToken(Str lexeme) {
		Token token;
		token.lexeme = lexeme;
		token.type = getLexemeType(lexeme);
		return token;
	}

}