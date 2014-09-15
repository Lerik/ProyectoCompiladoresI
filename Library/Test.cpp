#include "stdafx.h"
#include "Test.h"


Test::Test()
{
}


Test::~Test()
{
}

void Test::ShowMeOutpoutCodeToLexer(string code)
{
	_codeReader = new ContentReader(code);

	char currentC = _codeReader->nextCharacter();

	while(currentC != '\n')
	{
		cout<<currentC;
		currentC = _codeReader->nextCharacter();
	}

}

void Test::ShowMeTokensCreatedWithThisCode(string code)
{
	_lexer = new Lexer(code);
	
	if(!_lexer->createTokens())
	{
		cout << _lexer->getStatus() << endl;
	}
	else
	{
		cout <<endl<<endl<< _lexer->getStatus()<<endl;

		list<Token> createdTokens = _lexer->getTokens();
		list<Token>::iterator iter;

		for(iter = createdTokens.begin(); iter != createdTokens.end(); iter++)
		{
			Token _t = (*iter);
			cout<<_t.getLexeme()<<" - "<<_t.getToken();
			cout<<"\n";
		}
		
		cout<<"\n";
	}
}
