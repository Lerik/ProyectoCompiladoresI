#include "stdafx.h"
#include "ContentReader.h"
#include "Test.h"
#include <string>
#include <iostream>
using namespace std;

int main( int argc, const char* argv[] )
{
	char c='a';
	/*
	Test testingContentReader;
	testingContentReader.ShowMeOutpoutCodeToLexer("var name:Integer32 := 16+1;");
	cout<<"\n\n";
	cout<<"TEST 1 \n\n";
	testingContentReader.ShowMeTokensCreatedWithThisCode("var name:Integer32 := 16+1;");
	cout<<"TEST 2 \n\n";
	testingContentReader.ShowMeTokensCreatedWithThisCode("var name:array[6^5] of char;");
	cout<<"TEST 3 \n\n";
	testingContentReader.ShowMeTokensCreatedWithThisCode("text = \"hello bitch^%$\#@!'''''(*&^%$es!\";");
	cout<<"TEST 4 \n\n";
	testingContentReader.ShowMeTokensCreatedWithThisCode("text = cadena.split().function();");
	cout<<"TEST 5 \n\n";
	testingContentReader.ShowMeTokensCreatedWithThisCode("text = cadena.split().function();\nbegin\nvar name name:Real := 3.294E+04");
	*/

	cout << isalpha(c);

	cin>>c;
	
	return 0;
}