#include "stdafx.h"
#include "Token.h"

Token::Token()
{
}

void Token::setLexeme(string newLexeme)
{
	lexeme = newLexeme;
}

void Token::setToken(TokenTypes newToken)
{
	token = newToken;
}

string Token::getLexeme()
{
	return lexeme;
}

TokenTypes Token::getToken()
{
	return token;
}