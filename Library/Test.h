#pragma once

#include <iostream>
#include <iterator>
#include <list>
#include <string>

#include "ContentReader.h"
#include "Lexer.h"
#include "Token.h"

using namespace std;

class Test
{
public:
	Test();
	~Test();

	//ContentReader Test

	void ShowMeOutpoutCodeToLexer(string code);

	//Lexer Test

	void ShowMeTokensCreatedWithThisCode(string code);

private:
	ContentReader *_codeReader;
	Token *_token;
	Lexer *_lexer;
};

