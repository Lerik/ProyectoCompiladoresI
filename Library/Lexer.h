#pragma once

#include <string>
#include <cctype>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>

#include "ContentReader.h"
#include "Token.h"

using namespace std;

class Lexer
{
public:
	Lexer();
	Lexer(string code);
	~Lexer();

	void setCode(string code);
	void setStatus(string message, char character, bool error);

	bool createTokens();
	string getStatus();

	list<Token> getTokens();

private:
	map<string,ReservedWords> _listOfReservedWords;
	string _status;

	list<Token> _listTokens;
	ContentReader *_codeReader;

	void setReservedWords();

	bool isEndOfLine(char value);
};