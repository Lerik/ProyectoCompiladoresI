#include "stdafx.h"
#include "Lexer.h"

Lexer::Lexer()
{
	_status = "Virgin";

	_codeReader = new ContentReader();

	setReservedWords();
}

Lexer::Lexer(string code)
{
	_status = "Raped";

	_codeReader = new ContentReader(code);

	setReservedWords();
}

Lexer::~Lexer()
{
	delete _codeReader;
}

void Lexer::setCode(string code)
{
	_codeReader = new ContentReader(code);
}

bool Lexer::createTokens()
{
	char currentCharacter = _codeReader->nextCharacter();
	int currentState = 1;

	ofstream myfile;
	myfile.open ("example.txt");

	string charactersCollected = "";
	string specialSymbols = "+-*/#&|~%!;^,.[](){}>";

	while(true)
	{
		switch(currentState)
		{
		case 1:
			myfile<<"1-"<<currentCharacter<<"\n";
			if(currentCharacter==' ' || currentCharacter=='\t' || currentCharacter=='\r')
			{
				currentCharacter = _codeReader->nextCharacter();
				break;
			}
			else if(isalpha(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 2;
				break;
			}
			else if(isdigit(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 3;
				break;
			}
			else if(currentCharacter == ':')
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 11;
				break;
			}
			else if(currentCharacter == '<')
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 12;
				break;
			}
			else if(currentCharacter == '=')
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 13;
				break;
			}
			else if(specialSymbols.find(currentCharacter)>=0 && specialSymbols.find(currentCharacter)<specialSymbols.length())
			{
				charactersCollected += currentCharacter;
				currentState = 14;
				break;
			}
			else if(currentCharacter=='\'')
			{
				currentCharacter = _codeReader->nextCharacter();
				currentState = 10;
				break;
			}
			else if(currentCharacter=='\"')
			{
				currentCharacter = _codeReader->nextCharacter();
				currentState = 9;
				break;
			}
			else if(currentCharacter=='{')
			{
				currentCharacter = _codeReader->nextCharacter();
				currentState = 15;
				break;
			}
			else if(currentCharacter=='(')
			{
				currentCharacter = _codeReader->nextCharacter();
				currentState = 16;
				break;
			}
			else if(currentCharacter == '_')
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 18;
				break;
			}
			else if(currentCharacter == '%')
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 19;
				break;
			}
			else if(currentCharacter == '$')
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 20;
				break;
			}
			else if(currentCharacter=='\n')
			{
				Token newToken;
				newToken.setLexeme("\n");
				newToken.setToken(TokenTypes::XdEndOfLine);
				_listTokens.push_back(newToken);
				setStatus("Succesful Lexer Analysis",currentCharacter,false);
				return true;
			}
			else
			{
				setStatus("Error L101: Found unacceptable characters",currentCharacter,true);
				return false;
			}

		case 2:
			myfile<<"2-"<<currentCharacter<<"\n";
			if(isalpha(currentCharacter)!=0 || isdigit(currentCharacter)!=0)
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);

				if(_listOfReservedWords.find(charactersCollected) != _listOfReservedWords.end())
					newToken.setToken(TokenTypes::XdReservedWord);
				else
					newToken.setToken(TokenTypes::XdIdentifier);

				_listTokens.push_back(newToken);
				charactersCollected = "";
				currentState=1;
				break;
			}

		case 3:
			myfile<<"3-"<<currentCharacter<<"\n";
			if(isdigit(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdDigit);
				_listTokens.push_back(newToken);

				if(currentCharacter == '.')
				{
					currentState = 4;
					charactersCollected = currentCharacter;
					currentCharacter = _codeReader->nextCharacter();
					break;
				}
				else
				{
					currentState = 1;
					charactersCollected = "";
					break;
				}
			}

		case 4:
			myfile<<"4-"<<currentCharacter<<"\n";
			if(isdigit(currentCharacter))
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdPeriod);
				_listTokens.push_back(newToken);

				charactersCollected = currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 5;
				break;
			}
			else
			{
				setStatus("Error L401: There must be a digit after this period.",currentCharacter, true);
				return false;
				break;
			}

		case 5:
			myfile<<"5-"<<currentCharacter<<"\n";
			if(isdigit(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				break;
			}
			else if(currentCharacter=='e')
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdDigit);
				_listTokens.push_back(newToken);

				charactersCollected = currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 6;
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdDigit);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentState = 1;
				break;
			}

		case 6:
			myfile<<"6-"<<currentCharacter<<"\n";
			if(currentCharacter == '+')
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdExpDesignator);
				_listTokens.push_back(newToken);

				Token newTokenPlus;
				newTokenPlus.setLexeme("+");
				newTokenPlus.setToken(TokenTypes::XdAddition);
				_listTokens.push_back(newTokenPlus);

				currentCharacter = _codeReader->nextCharacter();
				charactersCollected = currentCharacter;
				currentState = 7;
				break;
			}
			else if(currentCharacter = '-')
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdExpDesignator);
				_listTokens.push_back(newToken);

				Token newTokenMinus;
				newTokenMinus.setLexeme("-");
				newTokenMinus.setToken(TokenTypes::XdSubstraction);
				_listTokens.push_back(newTokenMinus);

				currentCharacter = _codeReader->nextCharacter();
				charactersCollected = currentCharacter;
				currentState = 7;
				break;
			}
			else if(isdigit(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 8;
				break;
			}
			else
			{
				setStatus("Error L601: There must be digits after Exp Designator.",currentCharacter, true);
				return false;
				break;
			}

		case 7:
			myfile<<"7-"<<currentCharacter<<"\n";
			if(isdigit(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				currentState = 8;
				break;
			}
			else
			{
				setStatus("Error L701: There must be digits after Exp Designator and positive/negative symbol.",currentCharacter, true);
				return false;
				break;
			}

		case 8:
			myfile<<"8-"<<currentCharacter<<"\n";
			if(isdigit(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdDigit);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentState = 1;
				break;
			}

		case 9:
			myfile<<"9-"<<currentCharacter<<"\n";
			if(currentCharacter == '\"')
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdString);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}
			else
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				break;
			}

		case 10:
			myfile<<"10-"<<currentCharacter<<"\n";
			if(currentCharacter == '\'')
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdString);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}
			else
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				break;
			}

		case 11:
			myfile<<"11-"<<currentCharacter<<"\n";
			if(currentCharacter == '=')
			{
				charactersCollected += currentCharacter;

				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdAssign);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdColon);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentState = 1;
				break;
			}

		case 12:
			myfile<<"12-"<<currentCharacter<<"\n";
			if(currentCharacter == '=')
			{
				charactersCollected += currentCharacter;

				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdLessThanEqual);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdLessThan);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentState = 1;
				break;
			}

		case 13:
			myfile<<"13-"<<currentCharacter<<"\n";
			if(currentCharacter == '>')
			{
				charactersCollected += currentCharacter;

				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdGreaterThanEqual);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdEqual);
				_listTokens.push_back(newToken);

				charactersCollected = "";
				currentState = 1;
				break;
			}

		case 14:
			myfile<<"14-"<<currentCharacter<<"\n";
			if(specialSymbols.find(currentCharacter)>=0 && specialSymbols.find(currentCharacter)<specialSymbols.length())
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);

				if(currentCharacter=='+')
					newToken.setToken(TokenTypes::XdAddition);
				else if(currentCharacter=='-')
					newToken.setToken(TokenTypes::XdSubstraction);
				else if(currentCharacter=='*')
					newToken.setToken(TokenTypes::XdMultiplication);
				else if(currentCharacter=='/')
					newToken.setToken(TokenTypes::XdDivision);
				else if(currentCharacter=='#')
					newToken.setToken(TokenTypes::XdNumberSign);
				else if(currentCharacter=='&')
					newToken.setToken(TokenTypes::XdAndSign);
				else if(currentCharacter=='|')
					newToken.setToken(TokenTypes::XdOrSign);
				else if(currentCharacter=='~')
					newToken.setToken(TokenTypes::XdNotSign);
				else if(currentCharacter=='%')
					newToken.setToken(TokenTypes::XdPercent);
				else if(currentCharacter=='!')
					newToken.setToken(TokenTypes::XdExclamation);
				else if(currentCharacter==';')
					newToken.setToken(TokenTypes::XdSemicolon);
				else if(currentCharacter=='^')
					newToken.setToken(TokenTypes::XdCaret);
				else if(currentCharacter==',')
					newToken.setToken(TokenTypes::XdComma);
				else if(currentCharacter=='.')
					newToken.setToken(TokenTypes::XdPeriod);
				else if(currentCharacter=='[')
					newToken.setToken(TokenTypes::XdSl);
				else if(currentCharacter==']')
					newToken.setToken(TokenTypes::XdSr);
				else if(currentCharacter==')')
					newToken.setToken(TokenTypes::XdPr);
				else
					newToken.setToken(TokenTypes::XdGreaterThan);

				_listTokens.push_back(newToken);
				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}
			else
			{
				currentState = 1;
				break;
			}

		case 15:
			if(currentCharacter == '}')
			{
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}
			else if(currentCharacter == '{')
			{
				setStatus("Error L1501: You may not have an initial bracket inside a comment that starts with another initial bracket. Use another comment delimiter.",currentCharacter, true);
				return false;
				break;
			}
			else
			{
				currentCharacter = _codeReader->nextCharacter();
				break;
			}

		case 16:
			if(currentCharacter == '*')
			{
				currentCharacter = _codeReader->nextCharacter();
				currentState = 17;
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme("(");
				newToken.setToken(TokenTypes::XdPl);
				_listTokens.push_back(newToken);
				currentState = 1;
				break;
			}

		case 17:
			if(currentCharacter == '*')
			{
				currentCharacter = _codeReader->nextCharacter();

				if(currentCharacter == ')')
				{
					currentCharacter = _codeReader->nextCharacter();
					currentState = 1;
					break;
				}
				else
				{
					break;
				}
			}
			else if(currentCharacter == '(')
			{
				currentCharacter = _codeReader->nextCharacter();
				
				if(currentCharacter == '*')
				{
					setStatus("Error L1701: You may not have an initial '(*' inside a comment that starts with another initial '(*'. Use another comment delimiter.",currentCharacter, true);
					return false;
					break;
				}
				else
				{
					break;
				}
			}
			else
			{
				currentCharacter = _codeReader->nextCharacter();
				break;
			}

		case 18:
			if(isalpha(currentCharacter))
			{
				currentState = 2;
				break;
			}
			else
			{
				setStatus("Error L1801: Underscore it is used for identifiers, and it has to be followed by an alphabetic character.",'_', true);
				return false;
				break;
			}
			break;

		case 19:
			if(isdigit(currentCharacter))
			{
				currentState = 20;
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdPercent);
				_listTokens.push_back(newToken);
				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}

		case 20:
			if(isdigit(currentCharacter))
			{
				charactersCollected += currentCharacter;
				currentCharacter = _codeReader->nextCharacter();
				break;
			}
			else
			{
				Token newToken;
				newToken.setLexeme(charactersCollected);
				newToken.setToken(TokenTypes::XdBinary);
				_listTokens.push_back(newToken);
				charactersCollected = "";
				currentCharacter = _codeReader->nextCharacter();
				currentState = 1;
				break;
			}

		case 21:
			charactersCollected += _codeReader->nextCharacter();
			charactersCollected += _codeReader->nextCharacter();
			charactersCollected += _codeReader->nextCharacter();
			charactersCollected += _codeReader->nextCharacter();

			Token newToken;
			newToken.setLexeme(charactersCollected);
			newToken.setToken(TokenTypes::XdHex);
			_listTokens.push_back(newToken);
			charactersCollected = "";
			currentCharacter = _codeReader->nextCharacter();
			currentState = 1;
			break;
		}
	}
}

string Lexer::getStatus()
{
	return _status;
}

void Lexer::setStatus(string message, char character, bool error)
{
	if(error)
	{
		_status = message+" (";
		_status += character;
		_status += ") Line:" + to_string(_codeReader->getLine())+" Column: "+to_string(_codeReader->getColumn());
		
	}
	else
	{
		_status = message;
	}
}

list<Token> Lexer::getTokens()
{
	return _listTokens;
}

void Lexer::setReservedWords()
{
	_listOfReservedWords["and"] = ReservedWords::_and;
	_listOfReservedWords["array"] = ReservedWords::_array;
	_listOfReservedWords["begin"] = ReservedWords::_begin;
	_listOfReservedWords["const"] = ReservedWords::_const;
	_listOfReservedWords["div"] = ReservedWords::_div;
	_listOfReservedWords["do"] = ReservedWords::_do;
	_listOfReservedWords["downto"] = ReservedWords::_downto;
	_listOfReservedWords["else"] = ReservedWords::_else;
	_listOfReservedWords["end"] = ReservedWords::_end;
	_listOfReservedWords["file"] = ReservedWords::_file;
	_listOfReservedWords["for"] = ReservedWords::_for;
	_listOfReservedWords["forward"] = ReservedWords::_forward;
	_listOfReservedWords["function"] = ReservedWords::_function;
	_listOfReservedWords["goto"] = ReservedWords::_goto;
	_listOfReservedWords["if"] = ReservedWords::_if;
	_listOfReservedWords["in"] = ReservedWords::_in;
	_listOfReservedWords["label"] = ReservedWords::_label;
	_listOfReservedWords["main"] = ReservedWords::_main;
	_listOfReservedWords["mod"] = ReservedWords::_mod;
	_listOfReservedWords["nil"] = ReservedWords::_nil;
	_listOfReservedWords["not"] = ReservedWords::_not;
	_listOfReservedWords["of"] = ReservedWords::_of;
	_listOfReservedWords["or"] = ReservedWords::_or;
	_listOfReservedWords["packed"] = ReservedWords::_packed;
	_listOfReservedWords["procedure"] = ReservedWords::_procedure;
	_listOfReservedWords["program"] = ReservedWords::_program;
	_listOfReservedWords["record"] = ReservedWords::_record;
	_listOfReservedWords["repeat"] = ReservedWords::_repeat;
	_listOfReservedWords["set"] = ReservedWords::_set;
	_listOfReservedWords["shl"] = ReservedWords::_shl;
	_listOfReservedWords["shr"] = ReservedWords::_shr;
	_listOfReservedWords["then"] = ReservedWords::_then;
	_listOfReservedWords["to"] = ReservedWords::_to;
	_listOfReservedWords["type"] = ReservedWords::_type;
	_listOfReservedWords["until"] = ReservedWords::_until;
	_listOfReservedWords["var"] = ReservedWords::_var;
	_listOfReservedWords["while"] = ReservedWords::_while;
	_listOfReservedWords["with"] = ReservedWords::_with;
	_listOfReservedWords["xor"] = ReservedWords::_xor;
}

bool Lexer::isEndOfLine(char value)
{
	string str = "";
	str += value;

	if(str.compare("\n")==0)
		return true;
	else
		return false;
}