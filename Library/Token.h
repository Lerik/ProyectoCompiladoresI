#pragma once
#include <string>
#include <iostream>

using namespace std;

enum TokenTypes
{
	XdIdentifier,
	XdDigit,
	XdExpDesignator,
	XdString,
	XdAssign,
	XdAddition,
	XdSubstraction,
	XdMultiplication,
	XdDivision,
	XdEqual,
	XdUnequal,
	XdLessThan,
	XdGreaterThan,
	XdLessThanEqual,
	XdGreaterThanEqual,
	XdPl,
	XdPr,
	XdSl,
	XdSr,
	XdBl,
	XdBr,
	XdAndSign,
	XdOrSign,
	XdNotSign,
	XdNumberSign,
	XdPercent,
	XdExclamation,
	XdComma,
	XdPeriod,
	XdSemicolon,
	XdTwoPeriods,
	XdColon,
	XdCaret,
	XdEndOfLine,
	XdReservedWord,
	XdHex,
	XdBinary
};

enum ReservedWords
{
	_and,
	_array,
	_begin,
	_const,
	_div,
	_do,
	_downto,
	_else,
	_end,
	_file,
	_for,
	_forward,
	_function,
	_goto,
	_if,
	_in,
	_label,
	_main,
	_mod,
	_nil,
	_not,
	_of,
	_or,
	_packed,
	_procedure,
	_program,
	_record,
	_repeat,
	_set,
	_shl,
	_shr,
	_then,
	_to,
	_type,
	_until,
	_var,
	_while,
	_with,
	_xor
};

class Token
{

public:
	Token();

	void setLexeme(string newLexeme);
	void setToken(TokenTypes newToken);

	string getLexeme();
	TokenTypes getToken();

private:
	 string lexeme;
	 TokenTypes token;

};